<?php

/**
 * Description of glw_class_view_manutencao_rotina
 *
 * @author marti
 */
class ViewManutencaoAcao extends ViewManutencao {
    
    public function criaComponentes() {
        $this->adicionaComponente(new CampoForm(Campo::INTEGER, 'codigo', 'Código'));
        $this->adicionaComponente(new CampoForm(Campo::TEXTO, 'nome', 'Nome'));
    }
}
