<?php

/**
 * Description of glw_class_model_sistema
 *
 * @author marti
 */
class ModelModulo {
    
    private $codigo;
    private $descricao;
    
    private $Sistema;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }
    
    public function getDescricao() {
        return $this->descricao;
    }

    public function getSistema() {
        if (!isset($this->Sistema)) {
            $this->Sistema = Factory::loadModel('GLW', 'Modulo');
        }
        return $this->Sistema;
    }

    public function setDescricao($nome): void {
        $this->descricao = $nome;
    }

    public function setSistema($Sistema): void {
        $this->Sistema = $Sistema;
    }

}
