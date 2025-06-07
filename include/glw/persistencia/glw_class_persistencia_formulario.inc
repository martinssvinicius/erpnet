<?php

/**
 * Description of glw_class_persistencia_rotina
 *
 * @author marti
 */
class PersistenciaFormulario extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbform');
        $this->addRelacionamentoAsInt('rotcodigo', 'Rotina.codigo');
        $this->addRelacionamentoAsInt('acacodigo', 'Acao.codigo');
        $this->addRelacionamentoAsVarchar('frmcontroller', 'controller');
        $this->addRelacionamentoAsVarchar('frminclude', 'include');
        $this->addRelacionamentoAsVarchar('frmtitulo', 'titulo');
    }
    
}
