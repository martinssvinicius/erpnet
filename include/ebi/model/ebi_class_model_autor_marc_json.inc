<?php

namespace Ebi\Model;

/**
 * Description of ebi_class_model_autor_marc_json
 *
 * @author marti
 */
class ModelAutorMarcJson {
    
    private $attr1;
    private $attr2;
    
    public function getAttr1() {
        return $this->attr1;
    }

    public function getAttr2() {
        return $this->attr2;
    }

    public function setAttr1($attr1) {
        $this->attr1 = $attr1;
    }

    public function setAttr2($attr2) {
        $this->attr2 = $attr2;
    }

    public function toJson() {
        get_object_vars($this);
    }
    
}
