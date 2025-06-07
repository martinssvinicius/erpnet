<?php

/**
 * Description of glw_class_model_sistema
 *
 * @author marti
 */
class ModelSistema {
    
    private $codigo;
    private $nome;
    
    private $Conjunto;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function getNome() {
        return $this->nome;
    }

    public function getConjunto() {
        if (!isset($this->Conjunto)) {
            $this->Conjunto = Factory::loadModel('GLW', 'Conjunto');
        }
        return $this->Conjunto;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

    public function setConjunto($Conjunto): void {
        $this->Conjunto = $Conjunto;
    }

}
