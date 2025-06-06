<?php

/**
 * Description of wun_class_model_pessoa
 *
 * @author marti
 */
class ModelPessoa {
    
    private $codigo;
    private $nomeRazao;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function getNomeRazao() {
        return $this->nomeRazao;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }

    public function setNomeRazao($nomeRazao): void {
        $this->nomeRazao = $nomeRazao;
    }

}
