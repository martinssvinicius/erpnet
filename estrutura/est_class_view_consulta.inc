<?php

/**
 * Description of glw_class_view_consulta
 *
 * @author marti
 */
abstract class ViewConsulta {
    
    private $campos = [];
    private $acoes = [];
    
    public function __construct() {
        $this->addCampos();
        $this->trataCampos();
        $this->addAcoes();
    }
    
    protected abstract function addCampos();
    
    protected function addAcoes() {
        
    }
    
    protected function trataCampos() {
        
    }
    
    protected function adicionaAcaoGrid($iRotina, $iAcao) {
        $acao = new AcaoConsulta();
        $acao->setRotina($iRotina);
        $acao->setAcao($iAcao);
        $this->acoes[] = $acao;
        return $acao;
        
    }
    
    public function getAcoes() {
        return $this->acoes;
    }
    
    protected function integer() {
        $campo = new CampoConsulta();
        return $campo;
    }
    
    protected function texto() {
        $campo = new CampoConsulta();
        return $campo;
    }
    
    protected function smallint() {
        
    }
    
    private function adicionaCampo() {
        
    }
    
    protected function bigint() {
        return $this->integer();
    }
    
    protected function lista() {
        
    }

}
