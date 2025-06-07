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
    }
    
    private $componentes = [];

    public function getComponentes() {
        return $this->componentes;
    }

    public function adicionaComponente($componente) {
        $this->componentes[] = $componente;
    }

    public abstract function criaComponentes();

    public function getValores() {
        $dados = $this->Principal->getParametro()['dados'];
        foreach ($this->getComponentes() as $oComponente) {
            $oComponente->setValor($dados[$oComponente->getNome()]);
        }
        return [];
    }
    
}
