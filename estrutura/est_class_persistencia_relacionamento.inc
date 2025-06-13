<?php

/**
 * Description of est_class_persistencia_relacionamento
 *
 * @author marti
 */
class PersistenciaRelacionamento {
    
    private $nomeBanco;
    private $nomeModel;
    private $chave;
    
    public function getNomeBanco() {
        return $this->nomeBanco;
    }

    public function getNomeModel() {
        return $this->nomeModel;
    }

    public function getChave() {
        return $this->chave;
    }

    public function setNomeBanco($nomeBanco) {
        $this->nomeBanco = $nomeBanco;
    }

    public function setNomeModel($nomeModel) {
        $this->nomeModel = $nomeModel;
    }

    public function setChave($chave) {
        $this->chave = $chave;
    }

}
