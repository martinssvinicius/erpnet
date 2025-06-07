<?php

/**
 * Description of glw_class_model_rotina
 *
 * @author marti
 */
class ModelFormulario {
    
    private $Rotina;
    
    private $Acao;
    
    private $controller;
    private $include;
    private $titulo;

    public function getRotina() {
        if (!isset($this->Rotina)) {
            $this->Rotina = Factory::loadModel('GLW', 'Rotina');
        }
        return $this->Rotina;
    }

    public function getAcao() {
        if (!isset($this->Acao)) {
            $this->Acao = Factory::loadModel('GLW', 'Acao');
        }
        return $this->Acao;
    }

    public function setRotina($Rotina) {
        $this->Rotina = $Rotina;
    }

    public function setAcao($Acao) {
        $this->Acao = $Acao;
    }
    
    public function getController() {
        return $this->controller;
    }

    public function getInclude() {
        return $this->include;
    }

    public function getTitulo() {
        return $this->titulo;
    }

    public function setController($controller): void {
        $this->controller = $controller;
    }

    public function setInclude($include): void {
        $this->include = $include;
    }

    public function setTitulo($titulo): void {
        $this->titulo = $titulo;
    }

}
