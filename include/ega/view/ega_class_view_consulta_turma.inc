<?php

namespace Ega\View;

use Ega\Enum\EnumTurma;
use Formulario;
use ViewConsulta;

/**
 * Description of ega_class_view_consulta_turma
 *
 * @author marti
 */
class ViewConsultaTurma extends ViewConsulta {
    
    protected function addCampos() {
        $this->bigint('codigo', 'Código')->width(2)->filter()->order()->key();
        $this->texto ('nome'  , 'Nome')->width(10)->filter()->order();
        $this->texto ('sigla' , 'Sigla')->width(10)->filter()->order();
    }
    
    protected function addAcoes() {
        parent::addAcoes();
        $this->adicionaAcoesPadrao();
    }
    
}
