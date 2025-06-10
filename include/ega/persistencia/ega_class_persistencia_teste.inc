<?php

namespace Ega\Persistencia;

/**
 * Description of ega_class_persistencia_teste
 *
 * @author marti
 */
class PersistenciaTeste extends \PersistenciaPadrao {
    
    protected function setRelacionamentos() {
        $this->setTabela('public', 'tbteste');
    }
}
