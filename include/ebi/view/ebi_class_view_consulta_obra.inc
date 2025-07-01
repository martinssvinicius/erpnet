<?php

namespace Ebi\View;

use ViewConsulta;

/**
 * Description of ebi_class_view_consulta_obra
 *
 * @author marti
 */
class ViewConsultaObra extends ViewConsulta {
    
    protected function addCampos() {
        
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
//        $this->adicionaAcao(92001, $iAcao);
    }
    
}
