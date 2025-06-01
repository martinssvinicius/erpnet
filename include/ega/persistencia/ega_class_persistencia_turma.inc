<?php

namespace Ega\Persistencia;

/**
 * Description of ega_class_persistencia_turma
 *
 * @author marti
 */
class PersistenciaTurma extends \PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('EGA', 'tbturma');
        $this->addRelacionamentoAsBigint('turcodigo', 'codigo', true);
        $this->addRelacionamentoAsBigint('turnome', 'nome');
    }
}
