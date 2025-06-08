<?php

/**
 * Description of glw_class_persistencia_conjunto
 *
 * @author marti
 */
class PersistenciaSistema extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbsistema');
        $this->addRelacionamentoAsInt('siscodigo', 'codigo');
        $this->addRelacionamentoAsVarchar('sisnome', 'nome');
        $this->addRelacionamentoAsInt('concodigo', 'Conjunto.codigo');
    }
}
