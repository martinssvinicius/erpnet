<?php

/**
 * Description of ebi_class_model_obra
 *
 * @author marti
 */
class ModelObra {
    
    private $codigo;
    private $titulo;
    private $subtitulo;
    private $artigoTitulo;
    private $anoEdicacao;
    private $numEdicacao;
    private $nomeEdicacao;
    private $dataPublicacao;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function getTitulo() {
        return $this->titulo;
    }

    public function getSubtitulo() {
        return $this->subtitulo;
    }

    public function getArtigoTitulo() {
        return $this->artigoTitulo;
    }

    public function getAnoEdicacao() {
        return $this->anoEdicacao;
    }

    public function getNumEdicacao() {
        return $this->numEdicacao;
    }

    public function getNomeEdicacao() {
        return $this->nomeEdicacao;
    }

    public function getDataPublicacao() {
        return $this->dataPublicacao;
    }

    public function setCodigo($codigo) {
        $this->codigo = $codigo;
    }

    public function setTitulo($titulo) {
        $this->titulo = $titulo;
    }

    public function setSubtitulo($subtitulo) {
        $this->subtitulo = $subtitulo;
    }

    public function setArtigoTitulo($artigoTitulo) {
        $this->artigoTitulo = $artigoTitulo;
    }

    public function setAnoEdicacao($anoEdicacao) {
        $this->anoEdicacao = $anoEdicacao;
    }

    public function setNumEdicacao($numEdicacao) {
        $this->numEdicacao = $numEdicacao;
    }

    public function setNomeEdicacao($nomeEdicacao) {
        $this->nomeEdicacao = $nomeEdicacao;
    }

    public function setDataPublicacao($dataPublicacao) {
        $this->dataPublicacao = $dataPublicacao;
    }

}
