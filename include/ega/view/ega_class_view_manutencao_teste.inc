<?php

namespace Ega\View;

use ViewManutencao;
use function toJson;

/**
 * Description of ega_class_view_manutencao_teste
 *
 * @author marti
 */
class ViewManutencaoTeste extends ViewManutencao {
    
    public function criaComponentes() {
        $this->adicionaComponente(new \CampoForm(\Campo::FILE, 'teste', 'teste'));
//        $this->adicionaComponente(new \CampoForm(\Campo::FILE, 'other_file', 'other file'));
    }
}
