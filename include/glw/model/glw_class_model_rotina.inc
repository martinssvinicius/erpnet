<?php

/**
 * Description of glw_class_model_rotina
 *
 * @author marti
 */
class ModelRotina {
    
    private $codigo;
    private $nome;
    private $descricao;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }
    
    public function getNome() {
        return $this->nome;
    }

    public function getDescricao() {
        return $this->descricao;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

    public function setDescricao($descricao): void {
        $this->descricao = $descricao;
    }

}
