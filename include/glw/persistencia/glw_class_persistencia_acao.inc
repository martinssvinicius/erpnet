<?php

/**
 * Description of glw_class_persistencia_rotina
 *
 * @author marti
 */
class PersistenciaAcao extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbacao');
        $this->addRelacionamentoAsInt('acacodigo', 'codigo');
        $this->addRelacionamentoAsVarchar('acanome', 'nome');
    }
    
}
