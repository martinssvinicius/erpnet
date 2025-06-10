<?php

namespace Ega\Model;

/**
 * Description of ega_class_model_aluno
 *
 * @author marti
 */
class ModelAluno {
    
    /**
     * @var \ModelPessoa
     */
    private $Pessoa;
    
    public function getPessoa() {
        if (!isset($this->Pessoa)) {
            $this->Pessoa = \Factory::loadModel('WUN', 'Pessoa');
        }
        return $this->Pessoa;
    }

    public function setPessoa(\ModelPessoa $Pessoa) {
        $this->Pessoa = $Pessoa;
    }

}
