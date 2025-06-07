<?php

/**
 * Description of glw_class_model_sistema
 *
 * @author marti
 */
class ModelModulo {
    
    private $codigo;
    private $nome;
    
    private $Sistema;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }
    
    public function getNome() {
        return $this->nome;
    }

    public function getSistema() {
        if (!isset($this->Sistema)) {
            $this->Sistema = Factory::loadModel('GLW', 'Modulo');
        }
        return $this->Sistema;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

    public function setSistema($Sistema): void {
        $this->Sistema = $Sistema;
    }

}
