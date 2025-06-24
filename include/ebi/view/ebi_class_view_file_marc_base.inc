<?php

namespace Ebi\View;

use XMLWriter;

/**
 * Description of ebi_class_view_file_marc_base
 *
 * @author marti
 */
class ViewFileMarcBase {
    
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
     * Read in MARCXML records
     *
     * This function reads in files or strings that
     * contain one or more MARCXML records.
     *
     * <code>
     * <?php
     * // Retrieve MARC records from a file
     * $journals = new File_MARC('journals.mrc', SOURCE_FILE);
     *
     * // Retrieve MARC records from a string (e.g. Z39 query results)
     * $monographs = new File_MARC($raw_marc, SOURCE_STRING);
     * ?>
     * </code>
     *
     * @param string $source       Name of the file, or a raw MARC string
     * @param int    $type         Source of the input: SOURCE_FILE or SOURCE_STRING
     * @param string $record_class Record class, defaults to ViewFileMarcRecord
     */
    function __construct($source, $type, $record_class)
    {
        $this->xmlwriter = new XMLWriter();
        $this->xmlwriter->openMemory();
        $this->xmlwriter->startDocument('1.0', 'UTF-8');

        $this->record_class = $record_class ?: ViewFileMarcRecord::class;
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
    function toXMLHeader()
    {
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
    function getXMLWriter()
    {
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
    function toXMLFooter()
    {
        $this->xmlwriter->endElement(); // end collection
        $this->xmlwriter->endDocument();
        return $this->xmlwriter->outputMemory();
    }
    
}
