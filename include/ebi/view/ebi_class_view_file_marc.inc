<?php

namespace Ebi\View;

use Exception;
use XMLWriter;

/**
 * Description of ebi_class_view_file_marc_base
 *
 * @author marti
 */
class ViewFileMarc {

    /**
     * MARC records retrieved from a file
     */
    const SOURCE_FILE = 1;

    /**
     * MARC records retrieved from a binary string 
     */
    const SOURCE_STRING = 2;

    /**
     * Hexadecimal value for Subfield indicator
     */
    const SUBFIELD_INDICATOR = "\x1F";

    /**
     * Hexadecimal value for End of Field
     */
    const END_OF_FIELD = "\x1E";

    /**
     * Hexadecimal value for End of Record
     */
    const END_OF_RECORD = "\x1D";

    /**
     * Length of the Directory
     */
    const DIRECTORY_ENTRY_LEN = 12;

    /**
     * Length of the Leader
     */
    const LEADER_LEN = 24;

    /**
     * Maximum record length
     */
    const MAX_RECORD_LENGTH = 99999;

    /**
     * Source containing raw records
     * 
     * @var resource
     */
    protected $source;

    /**
     * Source type (SOURCE_FILE or SOURCE_STRING)
     * 
     * @var int
     */
    protected $type;

    /**
     * XMLWriter for writing collections
     * 
     * @var XMLWriter
     */
    protected $xmlwriter;

    /**
     * Record class
     *
     * @var string
     */
    protected $record_class;

    /**
     * Read in MARC records
     *
     * This function reads in MARC record files or strings that
     * contain one or more MARC records.
     *
     * <code>
     * <?php
     * // Retrieve MARC records from a file
     * $journals = new ViewFileMarc('journals.mrc', SOURCE_FILE);
     *
     * // Retrieve MARC records from a string (e.g. Z39 query results)
     * $monographs = new ViewFileMarc($raw_marc, SOURCE_STRING);
     * ?>
     * </code>
     *
     * @param string $source        Name of the file, or a raw MARC string
     * @param int    $type          Source of the input, either SOURCE_FILE or SOURCE_STRING
     * @param string $record_class  Record class, defaults to ViewFileMarc_Record
     */
    function __construct($source, $type = self::SOURCE_FILE, $record_class = null) {

        $this->xmlwriter = new XMLWriter();
        $this->xmlwriter->openMemory();
        $this->xmlwriter->startDocument('1.0', 'UTF-8');

        $this->record_class = $record_class ?: ViewFileMarcRecord::class;

        switch ($type) {

            case self::SOURCE_FILE:
                $this->type = self::SOURCE_FILE;
                $this->source = fopen($source, 'rb');
                if (!$this->source) {
                    $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_FILE], array('filename' => $source));
                    throw new ViewFileMarcException($errorMessage, ViewFileMarcException::ERROR_INVALID_FILE);
                }
                break;

            case self::SOURCE_STRING:
                $this->type = self::SOURCE_STRING;
                $this->source = explode(ViewFileMarc::END_OF_RECORD, $source);
                break;

            default:
                throw new ViewFileMarcException(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_SOURCE], ViewFileMarcException::ERROR_INVALID_SOURCE);
        }
    }

    /**
     * Return the next raw MARC record
     *
     * Returns the next raw MARC record, unless all records already have
     * been read.
     *
     * @return string Either a raw record or false
     */
    function nextRaw() {
        if ($this->type == self::SOURCE_FILE) {
            $record = stream_get_line($this->source, ViewFileMarc::MAX_RECORD_LENGTH, ViewFileMarc::END_OF_RECORD);

            // Remove illegal stuff that sometimes occurs between records
            $record = preg_replace('/^[\\x0a\\x0d\\x00]+/', "", $record);
        } elseif ($this->type == self::SOURCE_STRING) {
            $record = array_shift($this->source);
        }

        // Exit if we are at the end of the file
        if (!$record) {
            return false;
        }

        // Append the end of record we lost during stream_get_line() or explode()
        $record .= ViewFileMarc::END_OF_RECORD;
        return $record;
    }

    /**
     * Return next {@link ViewFileMarc_Record} object
     *
     * Decodes the next raw MARC record and returns the {@link ViewFileMarc_Record}
     * object.
     * <code>
     * <?php
     * // Retrieve a set of MARC records from a file
     * $journals = new ViewFileMarc('journals.mrc', SOURCE_FILE);
     *
     * // Iterate through the retrieved records
     * while ($record = $journals->next()) {
     *     print $record;
     *     print "\n";
     * }
     *
     * ?>
     * </code>
     *
     * @return ViewFileMarc_Record next record, or false if there are
     * no more records
     */
    function next() {
        $raw = $this->nextRaw();
        if ($raw) {
            return $this->_decode($raw);
        } else {
            return false;
        }
    }

    /**
     * Decode a given raw MARC record
     *
     * Port of Andy Lesters MARC::File::USMARC->decode() Perl function into PHP.
     *
     * @param string $text Raw MARC record
     *
     * @return ViewFileMarc_Record Decoded ViewFileMarc_Record object
     */
    private function _decode($text) {
        $marc = new $this->record_class($this);

        // fallback on the actual byte length
        $record_length = strlen($text);

        $matches = array();
        if (preg_match("/^(\d{5})/", $text, $matches)) {
            // Store record length
            $record_length = $matches[1];
            if ($record_length != strlen($text)) {
                $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INCORRECT_LENGTH], array("record_length" => $record_length, "actual" => strlen($text))));
                // Real beats declared byte length
                $record_length = strlen($text);
            }
        } else {
            $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_NONNUMERIC_LENGTH], array("record_length" => substr($text, 0, 5))));
        }

        if (substr($text, -1, 1) != ViewFileMarc::END_OF_RECORD)
            throw new ViewFileMarcException(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_TERMINATOR], ViewFileMarcException::ERROR_INVALID_TERMINATOR);

        // Store leader
        $marc->setLeader(substr($text, 0, ViewFileMarc::LEADER_LEN));

        // bytes 12 - 16 of leader give offset to the body of the record
        $data_start = 0 + substr($text, 12, 5);

        // immediately after the leader comes the directory (no separator)
        $dir = substr($text, ViewFileMarc::LEADER_LEN, $data_start - ViewFileMarc::LEADER_LEN - 1);  // -1 to allow for \x1e at end of directory
        // character after the directory must be \x1e
        if (substr($text, $data_start - 1, 1) != ViewFileMarc::END_OF_FIELD) {
            $marc->addWarning(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_NO_DIRECTORY]);
        }

        // All directory entries 12 bytes long, so length % 12 must be 0
        if (strlen($dir) % ViewFileMarc::DIRECTORY_ENTRY_LEN != 0) {
            $marc->addWarning(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_DIRECTORY_LENGTH]);
        }

        // go through all the fields
        $nfields = strlen($dir) / ViewFileMarc::DIRECTORY_ENTRY_LEN;
        for ($n = 0; $n < $nfields; $n++) {
            // As pack returns to key 1, leave place 0 in list empty
            list(, $tag) = unpack("A3", substr($dir, $n * ViewFileMarc::DIRECTORY_ENTRY_LEN, ViewFileMarc::DIRECTORY_ENTRY_LEN));
            list(, $len) = unpack("A3/A4", substr($dir, $n * ViewFileMarc::DIRECTORY_ENTRY_LEN, ViewFileMarc::DIRECTORY_ENTRY_LEN));
            list(, $offset) = unpack("A3/A4/A5", substr($dir, $n * ViewFileMarc::DIRECTORY_ENTRY_LEN, ViewFileMarc::DIRECTORY_ENTRY_LEN));

            // Check directory validity
            if (!preg_match("/^[0-9A-Za-z]{3}$/", $tag)) {
                $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_DIRECTORY_TAG], array("tag" => $tag)));
            }
            if (!preg_match("/^\d{4}$/", $len)) {
                $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_DIRECTORY_TAG_LENGTH], array("tag" => $tag, "len" => $len)));
            }
            if (!preg_match("/^\d{5}$/", $offset)) {
                $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_DIRECTORY_OFFSET], array("tag" => $tag, "offset" => $offset)));
            }
            if ($offset + $len > $record_length) {
                $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_DIRECTORY], array("tag" => $tag)));
            }

            $tag_data = substr($text, $data_start + $offset, $len);

            if (substr($tag_data, -1, 1) == ViewFileMarc::END_OF_FIELD) {
                /* get rid of the end-of-tag character */
                $tag_data = substr($tag_data, 0, -1);
                $len--;
            } else {
                $marc->addWarning(ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_FIELD_EOF], array("tag" => $tag)));
            }

            if (preg_match("/^\d+$/", $tag) and ($tag < 10)) {
                $marc->appendField(new ViewFileMarcControlField($tag, $tag_data));
            } else {
                $subfields = explode(ViewFileMarc::SUBFIELD_INDICATOR, $tag_data);
                $indicators = array_shift($subfields);

                if (strlen($indicators) != 2) {
                    $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_INDICATORS], array("tag" => $tag, "indicators" => $indicators));
                    $marc->addWarning($errorMessage);
                    // Do the best with the indicators we've got
                    if (strlen($indicators) == 1) {
                        $ind1 = $indicators;
                        $ind2 = " ";
                    } else {
                        list($ind1, $ind2) = array(" ", " ");
                    }
                } else {
                    $ind1 = substr($indicators, 0, 1);
                    $ind2 = substr($indicators, 1, 1);
                }

                // Split the subfield data into subfield name and data pairs
                $subfield_data = array();
                foreach ($subfields as $subfield) {
                    if (strlen($subfield) > 0) {
                        $subfield_data[] = new ViewFileMarcSubfield(substr($subfield, 0, 1), substr($subfield, 1));
                    } else {
                        $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_EMPTY_SUBFIELD], array("tag" => $tag));
                        $marc->addWarning($errorMessage);
                    }
                }

                if (!isset($subfield_data)) {
                    $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_EMPTY_SUBFIELD], array("tag" => $tag));
                    $marc->addWarning($errorMessage);
                }


                // If the data is invalid, let's just ignore the one field
                try {
                    $new_field = new ViewFileMarcDataField($tag, $subfield_data, $ind1, $ind2);
                    $marc->appendField($new_field);
                } catch (Exception $e) {
                    $marc->addWarning($e->getMessage());
                }
            }
        }

        return $marc;
    }

    /**
     * Initializes the MARCXML output of a record or collection of records 
     *
     * This method produces an XML representation of a MARC record that
     * attempts to adhere to the MARCXML standard documented at
     * http://www.loc.gov/standards/marcxml/
     *
     * @return bool true if successful
     */
    function toXMLHeader() {
        $this->xmlwriter->startElement("collection");
        $this->xmlwriter->writeAttribute("xmlns", "http://www.loc.gov/MARC21/slim");
        return true;
    }

    /**
     * Returns the XMLWriter object
     *
     * This method produces an XML representation of a MARC record that
     * attempts to adhere to the MARCXML standard documented at
     * http://www.loc.gov/standards/marcxml/
     *
     * @return XMLWriter XMLWriter instance
     */
    function getXMLWriter() {
        return $this->xmlwriter;
    }

    /**
     * Returns the MARCXML collection footer
     *
     * This method produces an XML representation of a MARC record that
     * attempts to adhere to the MARCXML standard documented at
     * http://www.loc.gov/standards/marcxml/
     *
     * @return string           representation of MARC record in MARCXML format
     */
    function toXMLFooter() {
        $this->xmlwriter->endElement(); // end collection
        $this->xmlwriter->endDocument();
        return $this->xmlwriter->outputMemory();
    }
}
