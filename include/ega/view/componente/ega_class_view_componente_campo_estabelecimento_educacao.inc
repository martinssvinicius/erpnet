<?php

namespace Ega\View\Componente;

use Campo;
use CampoForm;
use Ega\Enum\EnumEstabelecimentoEducacao;
use Formulario;
use ViewComponenteCampo;

/**
 * Description of ega_class_view_componente_campo_estabelecimento_educacao
 *
 * @author marti
 */
class ViewComponenteCampoEstabelecimentoEducacao extends ViewComponenteCampo {
    
    protected function getPrefixoDefault() {
        return 'EstabelecimentoEducacao';
    }
    
    public function criaCampo() {
        $this->Campo = new CampoForm(Campo::INTEGER, "{$this->getPrefixo()}.EstabelecimentoPublico.codigo", 'Estabelecimento de Ensino');
        $this->Campo->setExterno(EnumEstabelecimentoEducacao::ROTINA, Formulario::ACAO_CONSULTAR);
    }
    
}
