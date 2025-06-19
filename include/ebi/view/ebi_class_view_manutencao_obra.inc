<?php

namespace Ebi\View;

use Ega\View\ViewManutencaoEducacao;

/**
 * Description of ebi_class_view_manutencao_obra
 *
 * @author marti
 */
class ViewManutencaoObra extends ViewManutencaoEducacao {
    
    public function criaComponentes() {
        $this->serial('codigo', 'Código');
        $this->texto('titulo', 'Título');
        $lista = $this->adicionaComponente(new \CampoForm('lista', 'teste', 'teste'));
        $lista->setLista([new \Lista(1, 'Teste 1')]);
    }
}
