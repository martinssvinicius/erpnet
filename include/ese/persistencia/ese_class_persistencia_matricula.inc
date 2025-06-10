<?php

namespace Ese\Persistencia;

/**
 * Description of ese_class_persistencia_matricula
 *
 * @author marti
 */
class PersistenciaMatricula extends \PersistenciaPadrao {
    
    const TABELA = 'tbmatricula';
    
    protected function setRelacionamentos() {
        $this->setTabela('ESE', self::TABELA);
        $this->addRelacionamentoAsBigint('matcodigo', 'codigo', true);
        $this->addRelacionamentoAsBigint('matcodigo', 'Matricula.codigo');
        $this->addRelacionamentoAsInt('estcodigo', 'EstabelecimentoEducacao.EstabelecimentoPublico.codigo');
        $this->addRelacionamentoAsSmallint('trncodigo', 'Turno.codigo');
        $this->addRelacionamentoAsSmallint('matsituacao', 'situacao');
    }
}
