<?php

/**
 * Description of glw_class_view_consulta
 *
 * @author marti
 */
abstract class ViewConsulta {
    
    private $campos = [];
    
    public function __construct() {
        $this->addCampos();
        $this->trataCampos();
    }
    
    protected abstract function addCampos();
    
    protected function addAcoes() {
        
    }
    
    protected function trataCampos() {
        
    }
    
}
