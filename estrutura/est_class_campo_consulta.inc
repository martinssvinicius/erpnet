<?php

/**
 * Description of est_class_campo_consulta
 *
 * @author marti
 */
class CampoConsulta {
    
    private $key = false;
    private $tamanho;
    private $filter = false;
    private $order = false;
    
    public function key() {
        $this->key = true;
    }
    
    public function width($tamanho) {
        $this->tamanho = $tamanho;
        return $this;
    }
    
    public function filter() {
        $this->filter = true;
        return $this;
    }
    
    public function order() {
        $this->order = true;
        return $this;
    }
    
}
