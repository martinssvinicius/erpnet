<?php

/**
 * Description of glw_class_model_sistema
 *
 * @author marti
 */
class ModelConjunto {
    
    private $codigo;
    private $nome;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function getNome() {
        return $this->nome;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

}
