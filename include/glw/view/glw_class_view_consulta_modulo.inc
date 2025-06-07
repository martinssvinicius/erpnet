<?php

/**
 * Description of 
 *
 * @author marti
 */
class ViewConsultaModulo extends ViewConsulta {
    
    protected function addCampos() {
        
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
        $this->addAcaoRotina();
    }
    
    private function addAcaoRotina() {
        $oAcao = $this->adicionaAcaoGrid(93, 101);
        $oAcao->setTitulo('Rotinas');
    }
    
}
