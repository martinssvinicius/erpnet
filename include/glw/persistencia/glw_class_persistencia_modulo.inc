<?php

/**
 * Description of glw_class_persistencia_conjunto
 *
 * @author marti
 */
class PersistenciaModulo extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbmodulo');
        $this->addRelacionamentoAsInt('modcodigo', 'codigo');
        $this->addRelacionamentoAsVarchar('moddescricao', 'descricao');
        $this->addRelacionamentoAsInt('siscodigo', 'Sistema.codigo');
    }
}
