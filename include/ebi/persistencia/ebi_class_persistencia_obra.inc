<?php

namespace Ebi\Persistencia;

/**
 * Description of ebi_class_persistencia_obra
 *
 * @author marti
 */
class PersistenciaObra extends \PersistenciaPadrao {
    
    const TABLE = 'tbobra';
    
    protected function setRelacionamentos() {
        $this->setTabela('EBI', self::TABLE);
        $this->addRelacionamentoAsBigint('obrcodigo', 'codigo', true);
        $this->addRelacionamentoAsVarchar('obrtitulo', 'titulo');
//        $this->addRelacionamentoAsSmallint('caocodigo', '');
        $this->addRelacionamentoAsVarchar('obrsubtitulo', 'subtitulo');
        $this->addRelacionamentoAsVarchar('artigotitulo', 'artigoTitulo');
//        $this->addRelacionamentoAsSmallint('edtcodigo', '');
        $this->addRelacionamentoAsSmallint('obranoedicacao', 'anoEdicacao');
        $this->addRelacionamentoAsSmallint('obrnumedicacao', 'numEdicacao');
        $this->addRelacionamentoAsVarchar('obrnomeedicacao', 'nomeEdicacao');
        $this->addRelacionamentoAsDate('obrdatapublicacao', 'dataPublicacao');
//        $this->addRelacionamentoAsInt('lpbcodigo', '');
    }
}
