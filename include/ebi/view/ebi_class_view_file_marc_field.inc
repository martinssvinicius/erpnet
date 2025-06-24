<?php

namespace Ebi\View;

/**
 * Description of ebi_class_view_file_marc_field
 *
 * @author marti
 */
class ViewFileMarcField extends ViewFileMarcList {
    
    // {{{ properties
    /**
     * The tag name of the Field
     * @var string
     */
    protected $tag;
    // }}}

    // {{{ Constructor: function __construct()
    /**
     * File_MARC_Field constructor
     *
     * Create a new {@link File_MARC_Field} object from passed arguments. We
     * define placeholders for the arguments required by child classes.
     *
     * @param string $tag       tag
     * @param string $subfields placeholder for subfields or control data
     * @param string $ind1      placeholder for first indicator
     * @param string $ind2      placeholder for second indicator
     */
    function __construct($tag, $subfields = null, $ind1 = null, $ind2 = null) 
    {
        $this->tag = $tag;

        // Check if valid tag
        if (!preg_match("/^[0-9A-Za-z]{3}$/", $tag)) {
             $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_TAG], array("tag" => $tag));
             throw new ViewFileMarcException($errorMessage, ViewFileMarcException::ERROR_INVALID_TAG);
        }

    }
    // }}}

    // {{{ Destructor: function __destruct()
    /**
     * Destroys the data field
     */
    function __destruct()
    {
        $this->tag = null;
    }
    // }}}

    // {{{ getTag()
    /**
     * Returns the tag for this {@link File_MARC_Field} object
     *
     * @return string returns the tag number of the field
     */
    function getTag()
    {
        return (string)$this->tag;
    }
    // }}}

    // {{{ setTag()
    /**
     * Sets the tag for this {@link File_MARC_Field} object
     *
     * @param string $tag new value for the tag
     *
     * @return string returns the tag number of the field
     */
    function setTag($tag)
    {
        $this->tag = $tag;
        return $this->getTag();
    }
    // }}}

    // {{{ isEmpty()
    /**
     * Is empty
     *
     * Checks if the field is empty.
     *
     * @return bool Returns true if the field is empty, otherwise false
     */
    function isEmpty()
    {
        if ($this->getTag()) {
            return false;
        }
        // It is empty
        return true;
    }
    // }}}

    // {{{ isControlField()
    /**
     * Is control field
     *
     * Checks if the field is a control field.
     *
     * @return bool Returns true if the field is a control field, otherwise false
     */
    function isControlField()
    {
        if (get_class($this) == 'File_MARC_Control_Field') {
            return true;
        }
        return false;
    }
    // }}}

    // {{{ isDataField()
    /**
     * Is data field
     *
     * Checks if the field is a data field.
     *
     * @return bool Returns true if the field is a data field, otherwise false
     */
    function isDataField()
    {
        if (get_class($this) == 'File_MARC_Data_Field') {
            return true;
        }
        return false;
    }
    // }}}


    /**
     * ========== OUTPUT METHODS ==========
     */

    // {{{ __toString()
    /**
     * Return Field formatted
     *
     * Return Field as a formatted string.
     *
     * @return string Formatted output of Field
     */
    function __toString()
    {
        return (string)$this->getTag();
    }
    // }}}

    // {{{ toRaw()
    /**
     * Return field in raw MARC format (stub)
     *
     * Return the field formatted in raw MARC for saving into MARC files. This
     * stub method is extended by the child classes.
     *
     * @return bool Raw MARC
     */
    function toRaw()
    {
        return false;
    }
    // }}}

    // {{{ formatField()
    /**
     * Pretty print a MARC_Field object without tags, indicators, etc.
     *
     * @param array $exclude Subfields to exclude from formatted output
     * 
     * @return string Returns the formatted field data
     */

    function formatField($exclude = array('2'))
    {
        if ($this->isControlField()) {
            return $this->getData();
        } else {
            $out = '';
            foreach ($this->getSubfields() as $subfield) {
                if (substr($this->getTag(), 0, 1) == '6' and (in_array($subfield->getCode(), array('v','x','y','z')))) {
                    $out .= ' -- ' . $subfield->getData();
                } elseif (!in_array($subfield->getCode(), $exclude)) {
                    $out .= ' ' . $subfield->getData();
                }
            }
            return trim($out);
        }
    }
    
}
