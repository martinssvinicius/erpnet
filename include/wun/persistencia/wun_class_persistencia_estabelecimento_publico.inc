<?php

/**
 * Description of wun_class_persistencia_estabelecimento_publico
 *
 * @author marti
 */
class PersistenciaEstabelecimentoPublico extends PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('WUN', 'tbestabelecimento');
        $this->addRelacionamentoAsInt('estcodigo', 'codigo');
    }
}
