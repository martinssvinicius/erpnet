<?php

/**
 * Description of wun_class_persistencia_pessoa
 *
 * @author marti
 */
class PersistenciaPessoa extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('WUN', 'tbunico');
        $this->addRelacionamentoAsBigint('unicodigo', 'codigo', true);
        $this->addRelacionamentoAsVarchar('uninomerazao', 'nomeRazao');
    }
}
