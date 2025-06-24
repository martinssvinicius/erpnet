<?php

namespace Ebi\View;

/**
 * Description of ebi_class_file_marc_control_field
 *
 * @author marti
 */
class ViewFileMarcControlField extends ViewFileMarcField {
    
    /**
     * Value of field, if field is a Control field
     * @var string
     */
    protected $data;

    /**
     * Field init function
     *
     * Create a new {@link File_MARC_Control_Field} object from passed arguments
     *
     * @param string $tag  tag
     * @param string $data control field data
     * @param string $ind1 placeholder for class strictness
     * @param string $ind2 placeholder for class strictness
     */
    function __construct($tag, $data, $ind1 = null, $ind2 = null) 
    {
        $this->data = $data;
        parent::__construct($tag);

    }

    /**
     * Destroys the control field
     */
    function __destruct()
    {
        $this->data = null;
        parent::__destruct();
    }

    /**
     * Destroys the control field
     *
     * @return true
     */
    function delete()
    {
        $this->__destruct();
    }

    /**
     * Get control field data
     *
     * @return string returns data in control field
     */
    function getData()
    {
        return (string)$this->data;
    }

    /**
     * Is empty
     *
     * Checks if the field contains data
     *
     * @return bool Returns true if the field is empty, otherwise false
     */
    function isEmpty()
    {
        return ($this->data) ? false : true;
    }

    /**
     * Set control field data
     *
     * @param string $data data for the control field
     *
     * @return bool returns the new data in the control field
     */
    function setData($data)
    {
        $this->data = $data;
        return $this->getData();
    }

    /**
     * Return as a formatted string
     *
     * Return the control field as a formatted string for pretty printing
     *
     * @return string Formatted output of control Field
     */
    function __toString()
    {
        return sprintf("%3s     %s", $this->tag, $this->data);
    }

    /**
     * Return as raw MARC
     *
     * Return the control field formatted in Raw MARC for saving into MARC files
     *
     * @return string Raw MARC
     */
    function toRaw()
    {
        return (string)$this->data.ViewFileMarc::END_OF_FIELD;
    }
    
}
