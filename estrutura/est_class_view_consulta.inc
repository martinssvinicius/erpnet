<?php

/**
 * Description of glw_class_view_consulta
 *
 * @author marti
 */
abstract class ViewConsulta {
    
    protected $Principal;
    
    private $campos = [];
    private $acoes = [];
    
    public function __construct() {
        $this->Principal = Principal::getInstance();
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
    
    protected function adicionaAcoesPadrao($iRotina = null) {
        if (is_null($iRotina)) {
            $iRotina = $this->Principal->Formulario->getRotina();
        }
        $this->adicionaAcaoGrid($iRotina, Formulario::ACAO_INCLUIR);
        $this->adicionaAcaoGrid($iRotina, Formulario::ACAO_ALTERAR);
        $this->adicionaAcaoGrid($iRotina, Formulario::ACAO_EXCLUIR);
        $this->adicionaAcaoGrid($iRotina, Formulario::ACAO_VISUALIZAR);
    }

}
