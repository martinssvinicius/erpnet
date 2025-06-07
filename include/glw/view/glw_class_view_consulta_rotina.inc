<?php

/**
 * Description of glw_class_view_consulta_rotina
 *
 * @author marti
 */
class ViewConsultaRotina extends ViewConsulta {
    
    protected function addCampos() {
        
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
    }
    
}
