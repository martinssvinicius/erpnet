<?php

/**
 * Description of 
 *
 * @author marti
 */
class ViewConsultaSistema extends ViewConsulta {
    
    protected function addCampos() {
        $this->integer('codigo', 'Código')->key();
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
        $this->addAcaoModulo();
    }
    
    private function addAcaoModulo() {
        $oAcao = $this->adicionaAcaoGrid(92, 101);
        $oAcao->adicionaParametro('Sistema.codigo', '$consulta->codigo');
        $oAcao->setTitulo('Menu');
    }
    
}
