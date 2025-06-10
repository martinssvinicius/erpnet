<?php

namespace Ese\Model;

/**
 * Description of ese_class_model_matricula
 *
 * @author marti
 */
class ModelMatricula {
    
    /**
     * @var \Ega\Model\ModelAluno
     */
    private $Aluno;
    
    /**
     * @var \Ega\Model\ModelEstabelecimentoEducacao
     */
    private $EstabelecimentoEducacao;
    
    /**
     * @var \Ega\Model\ModelTurno
     */
    private $Turno;
    
    private $codigo;
    private $situacao;
    
    public function getAluno() {
        if (!isset($this->Aluno)) {
            $this->Aluno = new \Ega\Model\ModelAluno();
        }
        return $this->Aluno;
    }

    public function getEstabelecimentoEducacao() {
        if (!isset($this->EstabelecimentoEducacao)) {
            $this->EstabelecimentoEducacao = new \Ega\Model\ModelEstabelecimentoEducacao();
        }
        return $this->EstabelecimentoEducacao;
    }

    public function getTurno() {
        if (!isset($this->Turno)) {
            $this->Turno = new \Ega\Model\ModelTurno();
        }
        return $this->Turno;
    }

    public function getCodigo() {
        return $this->codigo;
    }

    public function getSituacao() {
        return $this->situacao;
    }

    public function setAluno(\Ega\Model\ModelAluno $Aluno) {
        $this->Aluno = $Aluno;
    }

    public function setEstabelecimentoEducacao(\Ega\Model\ModelEstabelecimentoEducacao $EstabelecimentoEducacao) {
        $this->EstabelecimentoEducacao = $EstabelecimentoEducacao;
    }

    public function setTurno(\Ega\Model\ModelTurno $Turno) {
        $this->Turno = $Turno;
    }

    public function setCodigo($codigo) {
        $this->codigo = $codigo;
    }

    public function setSituacao($situacao) {
        $this->situacao = $situacao;
    }

}
