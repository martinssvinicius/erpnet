<?php

/**
 * Description of glw_class_model_bo_process
 *
 * @author marti
 */
abstract class ModelBoProcess implements InterfaceBusinessObject {
    
    protected $Model;
    
    public function __construct($oModel) {
        $this->Model = $oModel;
    }
    
    protected function trataDadosInsere() {
        
    }
    
    protected function trataDadosAltera() {
        
    }
    
}
