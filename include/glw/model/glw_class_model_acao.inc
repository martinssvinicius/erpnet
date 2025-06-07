<?php

/**
 * Description of glw_class_model_rotina
 *
 * @author marti
 */
class ModelAcao {
    
    private $codigo;
    private $nome;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }
    
    public function getNome() {
        return $this->nome;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

}
