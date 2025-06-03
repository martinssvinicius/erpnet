<?php

/**
 * Description of est_class_campo_form
 *
 * @author marti
 */
class CampoForm {
    
    public $tipo;
    public $nome;
    public $titulo;
    private $tamanho;
    private $opcoes;
    private $loadToModel;
    private $valor;
    
    private $lista = [];

    public function __construct($tipo, $nome, $titulo) {
        $this->tipo = $tipo;
        $this->nome = $nome;
        $this->titulo = $titulo;
    }

    public function setTamanho($tamanho) {
        $this->tamanho = $tamanho;
    }

    public function getTamanho() {
        return $this->tamanho;
    }

    public function setOpcoes($opcoes) {
        $this->opcoes = $opcoes;
    }

    public function getOpcoes() {
        return $this->opcoes;
    }
    
    public function setLista($aLista) {
        $this->lista = $aLista;
    }
    
    public function getLista() {
        return $this->lista;
    }
    
    public function getLoadToModel() {
        return $this->loadToModel;
    }

    public function setLoadToModel($loadToModel): void {
        $this->loadToModel = $loadToModel;
    }
    
    public function getTipo() {
        return $this->tipo;
    }

    public function getNome() {
        return $this->nome;
    }

    public function getTitulo() {
        return $this->titulo;
    }

    public function setTipo($tipo): void {
        $this->tipo = $tipo;
    }

    public function setNome($nome): void {
        $this->nome = $nome;
    }

    public function setTitulo($titulo): void {
        $this->titulo = $titulo;
    }
    
    public function getValor() {
        return $this->valor;
    }

    public function setValor($valor): void {
        $this->valor = $valor;
    }

}
