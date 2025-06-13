<?php

/**
 * Description of est_class_campo_consulta
 *
 * @author marti
 */
class CampoConsulta implements JsonSerializable {
    
    private $key = false;
    private $tamanho;
    private $filter = false;
    private $order = false;
    private $nome;
    private $titulo;
    
    public function key() {
        $this->key = true;
    }
    
    public function width($tamanho) {
        $this->tamanho = $tamanho;
        return $this;
    }
    
    public function filter() {
        $this->filter = true;
        return $this;
    }
    
    public function order() {
        $this->order = true;
        return $this;
    }
    
    public function getKey() {
        return $this->key;
    }

    public function getTamanho() {
        return $this->tamanho;
    }

    public function getFilter() {
        return $this->filter;
    }

    public function getOrder() {
        return $this->order;
    }

    public function getNome() {
        return $this->nome;
    }

    public function getTitulo() {
        return $this->titulo;
    }

    public function setKey($key) {
        $this->key = $key;
    }

    public function setTamanho($tamanho) {
        $this->tamanho = $tamanho;
    }

    public function setFilter($filter) {
        $this->filter = $filter;
    }

    public function setOrder($order) {
        $this->order = $order;
    }

    public function setNome($nome) {
        $this->nome = $nome;
    }

    public function setTitulo($titulo) {
        $this->titulo = $titulo;
    }

    public function jsonSerialize(): mixed {
        return [
            'nome' => $this->getNome(),
            'titulo' => $this->getTitulo(),
            'chave' => $this->getKey(),
        ];
    }

//    public function jsonSerialize() {
//    }
    
}
