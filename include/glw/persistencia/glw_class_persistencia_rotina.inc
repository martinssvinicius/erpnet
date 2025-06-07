<?php

/**
 * Description of glw_class_persistencia_rotina
 *
 * @author marti
 */
class PersistenciaRotina extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbrotina');
        $this->addRelacionamentoAsInt('rotcodigo', 'codigo');
        $this->addRelacionamentoAsVarchar('rotnome', 'nome');
        $this->addRelacionamentoAsVarchar('rotdescricao', 'descricao');
    }
    
}
