<?php

namespace Ebi\View;

/**
 * Description of ebi_class_view_file_marc_data_field
 *
 * @author marti
 */
class ViewFileMarcDataField extends ViewFileMarcField {
    
    /**
     * Value of the first indicator
     * @var string
     */
    protected $ind1;

    /**
     * Value of the second indicator
     * @var string
     */
    protected $ind2;

    /**
     * Linked list of subfields
     * @var ViewFileMarcList
     */
    protected $subfields;


    /**
     * {@link File_MARC_Data_Field} constructor
     *
     * Create a new {@link File_MARC_Data_Field} object. The only required
     * parameter is a tag. This enables programs to build up new fields
     * programmatically.
     *
     * <code>
     * // Example: Create a new data field
     *
     * // We can optionally create an array of subfields first
     * $subfields[] = new ViewFileMarcSubfield('a', 'Scott, Daniel.');
     *
     * // Create the new 100 field complete with a _a subfield and an indicator
     * $new_field = new File_MARC_Data_Field('100', $subfields, 0, null);
     * </code>
     *
     * @param string $tag       tag
     * @param array  $subfields array of {@link ViewFileMarcSubfield} objects
     * @param string $ind1      first indicator
     * @param string $ind2      second indicator
     */
    function __construct($tag, array $subfields = null, $ind1 = null, $ind2 = null)
    {
        $this->subfields = new ViewFileMarcList();

        parent::__construct($tag);

        $this->ind1 = $this->_validateIndicator($ind1);
        $this->ind2 = $this->_validateIndicator($ind2);

        // we'll let users add subfields after if they so desire
        if ($subfields) {
            $this->addSubfields($subfields);
        }
    }

    /**
     * Destroys the data field
     */
    function __destruct()
    {
        $this->subfields = null;
        $this->ind1 = null;
        $this->ind2 = null;
        parent::__destruct();
    }

    /**
     * Destroys the data field
     *
     * @return true
     */
    function delete()
    {
        $this->__destruct();
    }

    /**
     * Validates an indicator field
     *
     * Validates the value passed in for an indicator. This routine ensures
     * that an indicator is a single character. If the indicator value is null,
     * then this method returns a single character.
     *
     * If the indicator value contains more than a single character, this
     * throws an exception.
     *
     * @param string $indicator Value of the indicator to be validated
     *
     * @return string Returns the indicator, or space if the indicator was null
     */
    private function _validateIndicator($indicator)
    {
        if ($indicator == null) {
            $indicator = ' ';
        } elseif (strlen($indicator) > 1) {
            $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_INDICATOR], array("tag" => $this->getTag(), "indicator" => $indicator));
            throw new ViewFileMarcException($errorMessage, ViewFileMarcException::ERROR_INVALID_INDICATOR);
        }
        return $indicator;
    }

    /**
     * Appends subfield to subfield list
     *
     * Adds a ViewFileMarcSubfield object to the end of the existing list
     * of subfields.
     *
     * @param ViewFileMarcSubfield $new_subfield The subfield to add
     *
     * @return ViewFileMarcSubfield the new ViewFileMarcSubfield object
     */
    function appendSubfield(ViewFileMarcSubfield $new_subfield)
    {
        /* Append as the last subfield in the field */
        $this->subfields->appendNode($new_subfield);
    }

    /**
     * Prepends subfield to subfield list
     *
     * Adds a ViewFileMarcSubfield object to the  start of the existing list
     * of subfields.
     *
     * @param ViewFileMarcSubfield $new_subfield The subfield to add
     *
     * @return ViewFileMarcSubfield the new ViewFileMarcSubfield object
     */
    function prependSubfield(ViewFileMarcSubfield $new_subfield)
    {
        $this->subfields->unshift($new_subfield);
        return $new_subfield;
    }

    /**
     * Inserts a field in the MARC record relative to an existing field
     *
     * Inserts a {@link ViewFileMarcSubfield} object before or after an existing
     * subfield.
     *
     * @param ViewFileMarcSubfield $new_field      The subfield to add
     * @param ViewFileMarcSubfield $existing_field The target subfield
     * @param bool               $before         Insert the subfield before the existing subfield if true; after the existing subfield if false
     *
     * @return ViewFileMarcSubfield                The new subfield
     */
    function insertSubfield(ViewFileMarcSubfield $new_field, ViewFileMarcSubfield $existing_field, $before = false)
    {
        $this->subfields->insertNode($new_field, $existing_field, $before);
        return $new_field;
    }

    /**
     * Adds an array of subfields to a {@link File_MARC_Data_Field} object
     *
     * Appends subfields to existing subfields in the order in which
     * they appear in the array. For finer grained control of the subfield
     * order, use {@link appendSubfield()}, {@link prependSubfield()},
     * or {@link insertSubfield()} to add each subfield individually.
     *
     * @param array $subfields array of {@link ViewFileMarcSubfield} objects
     *
     * @return int returns the number of subfields that were added
     */
    function addSubfields(array $subfields)
    {
        /*
         * Just in case someone passes in a single ViewFileMarcSubfield
         * instead of an array
         */
        if ($subfields instanceof ViewFileMarcSubfield) {
            $this->appendSubfield($subfields);
            return 1;
        }

        $cnt = 0;
        foreach ($subfields as $subfield) {
            $this->appendSubfield($subfield);
            $cnt++;
        }

        return $cnt;
    }

    /**
     * Delete a subfield from the field.
     *
     * @param ViewFileMarcSubfield $subfield The subfield to delete
     *
     * @return void
     */
    function deleteSubfield(ViewFileMarcSubfield $subfield)
    {
        $this->subfields->deleteNode($subfield);
    }

    /**
     * Get the value of an indicator
     *
     * @param int $ind number of the indicator (1 or 2)
     *
     * @return string returns indicator value if it exists, otherwise false
     */
    function getIndicator($ind)
    {
        if ($ind == 1) {
            return (string)$this->ind1;
        } elseif ($ind == 2) {
            return (string)$this->ind2;
        } else {
             $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_INDICATOR_REQUEST], array("indicator" => $indicator));
             throw new ViewFileMarcException($errorMessage, ViewFileMarcException::ERROR_INVALID_INDICATOR_REQUEST);
        }
        return false;
    }

    /**
     * Set the value of an indicator
     *
     * @param int    $ind   number of the indicator (1 or 2)
     * @param string $value value of the indicator
     *
     * @return string       returns indicator value if it exists, otherwise false
     */
    function setIndicator($ind, $value)
    {
        switch ($ind) {

        case 1:
            $this->ind1 = $this->_validateIndicator($value);
            break;

        case 2:
            $this->ind2 = $this->_validateIndicator($value);
            break;

        default:
            $errorMessage = ViewFileMarcException::formatError(ViewFileMarcException::$messages[ViewFileMarcException::ERROR_INVALID_INDICATOR_REQUEST], array("indicator" => $ind));
            throw new ViewFileMarcException($errorMessage, ViewFileMarcException::ERROR_INVALID_INDICATOR_REQUEST);
            return false;
        }

        return $this->getIndicator($ind);
    }

    /**
     * Returns the first subfield that matches a requested code.
     *
     * @param string $code subfield code for which the
     * {@link ViewFileMarcSubfield} is retrieved
     * @param bool   $pcre if true, then match as a regular expression
     *
     * @return ViewFileMarcSubfield returns the first subfield that matches
     * $code, or false if no codes match $code
     */
    function getSubfield($code = null, $pcre = null)
    {
        // iterate merrily through the subfields looking for the requested code
        foreach ($this->subfields as $sf) {
            if (($pcre
                && preg_match("/$code/", $sf->getCode()))
                || (!$pcre
                && $code == $sf->getCode())
            ) {
                return $sf;
            }
        }

        // No matches were found
        return false;
    }

    /**
     * Returns an array of subfields that match a requested code,
     * or a {@link ViewFileMarcList} that contains all of the subfields
     * if the requested code is null.
     *
     * @param string $code subfield code for which the
     * {@link ViewFileMarcSubfield} is retrieved
     * @param bool   $pcre if true, then match as a regular expression
     *
     * @return ViewFileMarcList|array returns a linked list of all subfields
     * if $code is null, an array of {@link ViewFileMarcSubfield} objects if
     * one or more subfields match, or an empty array if no codes match $code
     */
    function getSubfields($code = null, $pcre = null)
    {
        $results = array();

        // return all subfields if no specific subfields were requested
        if ($code === null) {
            $results = $this->subfields;
            return $results;
        }

        // iterate merrily through the subfields looking for the requested code
        foreach ($this->subfields as $sf) {
            if (($pcre
                && preg_match("/$code/", $sf->getCode()))
                || (!$pcre
                && $code == $sf->getCode())
            ) {
                $results[] = $sf;
            }
        }
        return $results;
    }

    /**
     * Checks if the field is empty.
     *
     * Checks if the field is empty. If the field has at least one subfield
     * with data, it is not empty.
     *
     * @return bool Returns true if the field is empty, otherwise false
     */
    function isEmpty()
    {
        // If $this->subfields is null, we must have deleted it
        if (!$this->subfields) {
            return true;
        }

        // Iterate through the subfields looking for some data
        foreach ($this->subfields as $subfield) {
            // Check if subfield has data
            if (!$subfield->isEmpty()) {
                return false;
            }
        }
        // It is empty
        return true;
    }

    /**
     * ========== OUTPUT METHODS ==========
     */

    /**
     * Return Field formatted
     *
     * Return Field as a formatted string.
     *
     * @return string Formatted output of Field
     */
    function __toString()
    {
        // Variables
        $lines = array();
        // Process tag and indicators
        $pre = sprintf("%3s %1s%1s", $this->tag, $this->ind1, $this->ind2);

        // Process subfields
        foreach ($this->subfields as $subfield) {
            $lines[] = sprintf("%6s _%1s%s", $pre, $subfield->getCode(), $subfield->getData());
            $pre = "";
        }

        return join("\n", $lines);
    }

    /**
     * Return Field in Raw MARC
     *
     * Return the Field formatted in Raw MARC for saving into MARC files
     *
     * @return string Raw MARC
     */
    function toRaw()
    {
        $subfields = array();
        foreach ($this->subfields as $subfield) {
            if (!$subfield->isEmpty()) {
                $subfields[] = $subfield->toRaw();
            }
        }
        return (string)$this->ind1.$this->ind2.implode("", $subfields).ViewFileMarc::END_OF_FIELD;
    }

    /**
     * Return fields data content as joined string
     *
     * Return all the fields data content as a joined string
     *
     * @param  string $joinChar A string used to join the data conntent.
     * Default is an empty string
     *
     * @return string Joined string
     */
    function getContents($joinChar = '')
    {
        $contents = array();
        foreach($this->subfields as $subfield) {
            $contents[] = $subfield->getData();
        }
        return implode($joinChar, $contents);
    }
    
}
