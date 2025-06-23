<?php

namespace Ebi\View;

/**
 * Description of ebi_class_view_file_marc_base
 *
 * @author marti
 */
class ViewFileMarc {
    
    const END_OF_RECORD = "\x1D";
    
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
     * Source containing raw records
     * 
     * @var resource
     */
    protected $source;
    
    function __construct($source, $type, $record_class)
    {
        $this->xmlwriter = new XMLWriter();
        $this->xmlwriter->openMemory();
        $this->xmlwriter->startDocument('1.0', 'UTF-8');

        $this->record_class = $record_class ?: File_MARC_Record::class;
        
        $this->source = fopen($source, 'rb');
        if (!$this->source) {
             $errorMessage = File_MARC_Exception::formatError(File_MARC_Exception::$messages[File_MARC_Exception::ERROR_INVALID_FILE], array('filename' => $source));
             throw new File_MARC_Exception($errorMessage, File_MARC_Exception::ERROR_INVALID_FILE);
        }
    }
    
    public function next()
    {
        $raw = $this->nextRaw();
        if ($raw) {
            return $this->_decode($raw);
        } else {
            return false;
        }
    }
    
    function nextRaw()
    {
//        if ($this->type == self::SOURCE_FILE) {
            $record = stream_get_line($this->source, File_MARC::MAX_RECORD_LENGTH, File_MARC::END_OF_RECORD);

            // Remove illegal stuff that sometimes occurs between records
            $record = preg_replace('/^[\\x0a\\x0d\\x00]+/', "", $record);

//        } elseif ($this->type == self::SOURCE_STRING) {
//            $record = array_shift($this->source);
//        }

        // Exit if we are at the end of the file
        if (!$record) {
            return false;
        }

        // Append the end of record we lost during stream_get_line() or explode()
        $record .= ViewFileMarc::END_OF_RECORD;
        return $record;
    }
    
}
