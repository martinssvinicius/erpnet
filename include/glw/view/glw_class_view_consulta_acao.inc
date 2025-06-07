<?php

/**
 * Description of 
 *
 * @author marti
 */
class ViewConsultaAcao extends ViewConsulta {
    
    protected function addCampos() {
        
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
    }
    
}
