<?php

/**
 * Description of glw_class_view_manutencao
 *
 * @author marti
 */
abstract class ViewManutencao  {
    
    private $Principal;

    public function __construct() {
        $this->Principal = Principal::getInstance();
        $this->criaComponentes();
        $this->criaComportamentos();
    }
    
    private $componentes = [];

    public function getComponentes() {
        return $this->componentes;
    }

    public function adicionaComponente($componente) {
        $this->componentes[] = $componente;
        return $componente;
    }

    public abstract function criaComponentes();

    public function getValores() {
        $dados = $this->Principal->getParametro()['dados'];
        foreach ($this->getComponentes() as $oComponente) {
            $oComponente->setValor($dados[$oComponente->getNome()]);
        }
        return [];
    }
    
    public function criaComportamentos() {
        
    }
    
    protected function loadComportamentoFromFile($sSigla, $sNome) {
//        echo '<script></script>';
    }
    
    protected function serial($nome, $titulo) {
        return $this->adicionaComponente(new CampoForm(Campo::SERIAL, $nome, $titulo));
    }
    
    protected function integer($nome, $titulo) {
        return $this->adicionaComponente(new CampoForm(Campo::INTEGER, $nome, $titulo));
    }
    
    protected function texto($nome, $titulo) {
        return $this->adicionaComponente(new CampoForm(Campo::TEXTO, $nome, $titulo));
    }
    
}
