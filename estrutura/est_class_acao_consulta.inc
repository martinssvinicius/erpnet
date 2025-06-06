<?php

/**
 * Description of est_class_acao_consulta
 *
 * @author marti
 */
class AcaoConsulta implements JsonSerializable {
    
    private $rotina;
    private $acao;
    private $titulo;
    
    public function getRotina() {
        return $this->rotina;
    }

    public function getAcao() {
        return $this->acao;
    }

    public function getTitulo() {
        return $this->titulo;
    }

    public function setRotina($rotina): void {
        $this->rotina = $rotina;
    }

    public function setAcao($acao): void {
        $this->acao = $acao;
    }

    public function setTitulo($titulo): void {
        $this->titulo = $titulo;
    }

    public function jsonSerialize(): mixed {
        return [
            'rotina' => $this->rotina,
            'acao' => $this->acao,
            'titulo' => $this->titulo,
        ];
    }
}
