<?php

namespace Ebi\View;

use Exception;
use SplDoublyLinkedList;

/**
 * Description of ebi_class_view_file_marc_list
 *
 * @author marti
 */
class ViewFileMarcList extends SplDoublyLinkedList {
    
// {{{ properties
    /**
     * Position of the subfield
     * @var int
     */
    protected $position;

    // }}}

    // {{{ key()
    /**
     * Returns the tag for a {@link ViewFileMarcField} object, or the code
     * for a {@link ViewFileMarcSubfield} object.
     *
     * This method enables you to use a foreach iterator to retrieve
     * the tag or code as the key for the iterator.
     *
     * @return string returns the tag or code
     */
    function key()
    {
        if ($this->current() instanceof ViewFileMarcField) {
            return $this->current()->getTag();
        } elseif ($this->current() instanceof ViewFileMarcSubfield) {
            return $this->current()->getCode();
        }
        return false;
    }
    // }}}

    // {{{ function insertNode()
    /**
     * Inserts a node into the linked list, based on a reference node that
     * already exists in the list.
     *
     * @param mixed $new_node      New node to add to the list
     * @param mixed $existing_node Reference position node
     * @param bool  $before        Insert new node before or after the existing node
     *
     * @return bool Success or failure
     **/
    public function insertNode($new_node, $existing_node, $before = false)
    {
        $pos = 0;
        $exist_pos = $existing_node->getPosition();
        $this->rewind();

        // Now add the node according to the requested mode
        switch ($before) {

        case true:
            $this->add($exist_pos, $new_node);
            break;

        // after
        case false:
            if ($this->offsetExists($exist_pos + 1)) {
                $this->add($exist_pos + 1, $new_node);
            } else {
                $this->appendNode($new_node);
                return true;
            }
            break;
        }

        // Fix positions
        $this->rewind();
        while ($n = $this->current()) {
            $n->setPosition($pos);
            $this->next();
            $pos++;
        }

        return true;
    }
    // }}}

    // {{{ function appendNode()
    /**
     * Adds a node onto the linked list.
     *
     * @param mixed $new_node New node to add to the list
     *
     * @return void
     **/
    public function appendNode($new_node)
    {
        $pos = $this->count();
        $new_node->setPosition($pos);
        $this->push($new_node);
    }
    // }}}

    // {{{ function prependNode()
    /**
     * Adds a node to the start of the linked list.
     *
     * @param mixed $new_node New node to add to the list
     *
     * @return void
     **/
    public function prependNode($new_node)
    {
        $this->insertNode($new_node, $this->bottom(), true);
    }
    // }}}

    // {{{ function deleteNode()
    /**
     * Deletes a node from the linked list.
     *
     * @param mixed $node Node to delete from the list
     *
     * @return void
     **/
    public function deleteNode($node)
    {
        $target_pos = $node->getPosition();
        $this->rewind();
        $pos = 0;

        // Omit target node and adjust pos of remainder
        $done = false;
        try {
            while ($n = $this->current()) {
                if ($pos == $target_pos && !$done) {
                    $done = true;
                    $this->next();
                    $this->offsetUnset($pos);
                } elseif ($pos >= $target_pos) {
                    $n->setPosition($pos);
                    $pos++;
                    $this->next();
                } else {
                    $pos++;
                    $this->next();
                }
            }
        }
        catch (Exception $e) {
            // no-op - shift() throws an exception, sigh
        }

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

}
