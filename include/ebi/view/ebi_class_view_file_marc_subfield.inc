<?php

namespace Ebi\View;

/**
 * Description of ebi_class_view_file_marc_subfield
 *
 * @author marti
 */
class ViewFileMarcSubfield {
    
    /**
     * Subfield code, e.g. _a, _b
     * @var string
     */
    protected $code;

    /**
     * Data contained by the subfield
     * @var string
     */
    protected $data;

    /**
     * Position of the subfield
     * @var int
     */
    protected $position;

    // }}}

    // {{{ Constructor: function __construct()
    /**
     * File_MARC_Subfield constructor
     *
     * Create a new subfield to represent the code and data
     *
     * @param string $code Subfield code
     * @param string $data Subfield data
     */
    function __construct($code, $data)
    {
        $this->code = $code;
        $this->data = $data;
    }
    // }}}

    // {{{ Destructor: function __destruct()
    /**
     * Destroys the subfield
     */
    function __destruct()
    {
        $this->code = null;
        $this->data = null;
        $this->position = null;
    }
    // }}}

    // {{{ Explicit destructor: function delete()
    /**
     * Destroys the subfield
     *
     * @return true
     */
    function delete()
    {
        $this->__destruct();
    }
    // }}}

    // {{{ getCode()
    /**
     * Return code of the subfield
     *
     * @return string Tag name
     */
    function getCode()
    {
        return (string)$this->code;
    }
    // }}}

    // {{{ getData()
    /**
     * Return data of the subfield
     *
     * @return string data
     */
    function getData()
    {
        return (string)$this->data;
    }
    // }}}

    // {{{ getPosition()
    /**
     * Return position of the subfield
     *
     * @return int data
     */
    function getPosition()
    {
        return $this->position;
    }
    // }}}

    // {{{ __toString()
    /**
     * Return string representation of subfield
     *
     * @return string String representation
     */
    public function __toString()
    {
        $pretty = '[' . $this->getCode() . ']: ' . $this->getData();
        return $pretty;
    }
    // }}}

    // {{{ toRaw()
    /**
     * Return the USMARC representation of the subfield
     *
     * @return string USMARC representation
     */
    function toRaw()
    {
        $result = ViewFileMarc::SUBFIELD_INDICATOR.$this->code.$this->data;
        return (string)$result;
    }
    // }}}

    // {{{ setCode()
    /**
     * Sets code of the subfield
     *
     * @param string $code new code for the subfield
     *
     * @return string code 
     */
    function setCode($code)
    {
        if ($code) {
            // could check more stringently; m/[a-Z]/ or the likes
            $this->code = $code;
        } else {
            // code must be _something_; raise error
            return false;
        }
        return true;
    }
    // }}}

    // {{{ setData()
    /**
     * Sets data of the subfield
     *
     * @param string $data new data for the subfield
     *
     * @return string data
     */
    function setData($data)
    {
        $this->data = $data;
        return true;
    }
    // }}}

    // {{{ setPosition()
    /**
     * Sets position of the subfield
     *
     * @param string $pos new position of the subfield
     *
     * @return void
     */
    function setPosition($pos)
    {
        $this->position = $pos;
    }
    // }}}

    // {{{ isEmpty()
    /**
     * Checks whether the subfield is empty or not
     *
     * @return bool True or false
     */
    function isEmpty()
    {
        // There is data
        if (strlen($this->data)) {
            return false;
        }

        // There is no data
        return true;
    }
    
}
