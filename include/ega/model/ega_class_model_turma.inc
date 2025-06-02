<?php

namespace Ega\Model;

/**
 * Description of ega_class_model_turma
 *
 * @author marti
 */
class ModelTurma {
    
    private $codigo;
    private $nome;
    
    private $EstabelecimentoEducacao;

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

    public function getNome() {
        return $this->nome;
    }

    public function setEstabelecimentoEducacao($EstabelecimentoEducacao): void {
        $this->EstabelecimentoEducacao = $EstabelecimentoEducacao;
    }
    
    public function getEstabelecimentoEducacao() {
        if (!isset($this->EstabelecimentoEducacao)) {
            
        }
        return $this->EstabelecimentoEducacao;
    }

}
