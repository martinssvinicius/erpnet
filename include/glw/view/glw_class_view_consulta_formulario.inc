<?php

/**
 * Description of 
 *
 * @author marti
 */
class ViewConsultaFormulario extends ViewConsulta {
    
    protected function addCampos() {
        
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
    }
    
}
