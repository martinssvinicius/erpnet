<?php

/**
 * Description of glw_class_model_bo_process
 *
 * @author marti
 */
abstract class ModelBoProcess implements InterfaceBusinessObjectProcess {
    
    protected $Model;
    protected $Persistencia;
    
    protected function getPersistencia() {
        return $this->Persistencia;
    }

    public function setPersistencia($Persistencia): void {
        $this->Persistencia = $Persistencia;
    }

        
    public function __construct($oModel) {
        $this->Model = $oModel;
    }
    
    protected function validaInclusao() {
        
    }
    
    protected function trataDadosInsere() {
        
    }
    
    protected function trataDadosAltera() {
        
    }
    
    protected function afterInclusao() {
        
    }
    
    protected function beforeAlteracao() {
        $this->trataDadosInsere();
    }
    
    protected function beforeInclusao() {
        $this->validaInclusao();
        $this->trataDadosInsere();
    }
    
    public function processaInclusao() {
        $this->beforeInclusao();
        if ($this->getPersistencia()->insere()) {
            $this->afterInclusao();
            return true;
        }
        return false;
    }
    
    public function processaAlteracao() {
        $this->beforeAlteracao();
        return $this->getPersistencia()->altera();
    }
    
}
