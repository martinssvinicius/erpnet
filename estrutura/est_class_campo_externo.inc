<?php

/**
 * Description of est_class_campo_externo
 *
 * @author marti
 */
class CampoExterno {
    
    private $rotina;
    private $acao;
    
    public function getRotina() {
        return $this->rotina;
    }

    public function getAcao() {
        return $this->acao;
    }

    public function setRotina($rotina) {
        $this->rotina = $rotina;
    }

    public function setAcao($acao) {
        $this->acao = $acao;
    }

}
