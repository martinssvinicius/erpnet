<?php

/**
 * Description of est_class_view_componente_campo
 *
 * @author marti
 */
abstract class ViewComponenteCampo {
    
    protected $Campo;
    private $prefixo;
    
    abstract protected function getPrefixoDefault();
    
    protected function getPrefixo() {
        return $this->prefixo ?: $this->getPrefixoDefault();
    }
    
}
