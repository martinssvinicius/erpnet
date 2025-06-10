<?php

/**
 * Description of 
 *
 * @author marti
 */
class ViewConsultaFormModulo extends ViewConsulta {
    
    protected function addCampos() {
        
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
    }
    
}
