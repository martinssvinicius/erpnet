<?php

/**
 * Description of glw_class_persistencia_conjunto
 *
 * @author marti
 */
class PersistenciaConjunto extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbconjunto');
        $this->addRelacionamentoAsInt('concodigo', 'codigo');
        $this->addRelacionamentoAsVarchar('connome', 'nome');
    }
}
