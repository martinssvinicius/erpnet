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
    private $anoEdicao;
    private $numEdicao;
    private $nomeEdicao;
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

    public function getAnoEdicao() {
        return $this->anoEdicao;
    }

    public function getNumEdicao() {
        return $this->numEdicao;
    }

    public function getNomeEdicao() {
        return $this->nomeEdicao;
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

    public function setAnoEdicao($anoEdicao) {
        $this->anoEdicao = $anoEdicao;
    }

    public function setNumEdicao($numEdicao) {
        $this->numEdicao = $numEdicao;
    }

    public function setNomeEdicacao($nomeEdicacao) {
        $this->nomeEdicao = $nomeEdicacao;
    }

    public function setDataPublicacao($dataPublicacao) {
        $this->dataPublicacao = $dataPublicacao;
    }

}
