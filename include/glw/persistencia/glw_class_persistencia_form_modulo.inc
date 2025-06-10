<?php

/**
 * Description of glw_class_persistencia_conjunto
 *
 * @author marti
 */
class PersistenciaFormModulo extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('webbased', 'tbformmod');
        $this->addRelacionamentoAsInt('rotcodigo', 'Rotina.codigo');
        $this->addRelacionamentoAsInt('acacodigo', 'Acao.codigo');
        $this->addRelacionamentoAsVarchar('fmotitulo', 'titulo');
        $this->addRelacionamentoAsInt('modcodigo', 'Modulo.codigo');
    }
}
