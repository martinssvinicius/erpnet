<?php

/**
 * Description of est_class_formulario
 *
 * @author marti
 */
class Formulario {
    
    const ACAO_CONSULTAR  = 101;
    const ACAO_INCLUIR    = 102;
    const ACAO_ALTERAR    = 103;
    const ACAO_EXCLUIR    = 104;
    const ACAO_VISUALIZAR = 105;
    
    /**
     * @var Rotina
     */
    private $Rotina;
    
    private $Acao;
    
    private $titulo;
    
    public function getRotina() {
        return $this->Rotina;
    }

    public function getAcao() {
        return $this->Acao;
    }

    public function setRotina($Rotina): void {
        $this->Rotina = $Rotina;
    }

    public function setAcao($Acao): void {
        $this->Acao = $Acao;
    }
    
    public function getTitulo() {
        return $this->titulo;
    }

    public function setTitulo($titulo): void {
        $this->titulo = $titulo;
    }

}
