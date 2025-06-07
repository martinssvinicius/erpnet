<?php

/**
 * Description of glw_class_model_modulo_formulario
 *
 * @author marti
 */
class ModelModuloFormulario {
    
    private $Rotina;
    private $Acao;
    
    private $titulo;
    
    private $Modulo;
    
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

    public function getTitulo() {
        return $this->titulo;
    }

    public function getModulo() {
        if (!isset($this->Modulo)) {
            $this->Modulo = Factory::loadModel('GLW', 'Modulo');
        }
        return $this->Modulo;
    }

    public function setRotina($Rotina): void {
        $this->Rotina = $Rotina;
    }

    public function setAcao($Acao): void {
        $this->Acao = $Acao;
    }

    public function setTitulo($titulo): void {
        $this->titulo = $titulo;
    }

    public function setModulo($Modulo): void {
        $this->Modulo = $Modulo;
    }

}
