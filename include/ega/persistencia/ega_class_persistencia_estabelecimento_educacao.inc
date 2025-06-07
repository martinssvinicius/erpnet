<?php

namespace Ega\Persistencia;

/**
 * Description of ega_class_persistencia_estabelecimento_educacao
 *
 * @author marti
 */
class PersistenciaEstabelecimentoEducacao extends \PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('EGA', 'tbestabeducacao');
        $this->addRelacionamentoAsInt('estcodigo', 'EstabelecimentoPublico.codigo', true);
    }
}
