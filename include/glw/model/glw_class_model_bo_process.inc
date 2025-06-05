<?php

/**
 * Description of glw_class_model_bo_process
 *
 * @author marti
 */
abstract class ModelBoProcess {
    
    protected $Model;
    
    public function __construct($oModel) {
        $this->Model = $oModel;
    }
    
    protected function trataDadosInsere() {
        
    }
    
    protected function trataDadosAltera() {
        
    }
    
}
