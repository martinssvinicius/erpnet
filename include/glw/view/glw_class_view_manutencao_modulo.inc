<?php

/**
 * Description of glw_class_view_manutencao_rotina
 *
 * @author marti
 */
class ViewManutencaoModulo extends ViewManutencao {
    
    public function criaComponentes() {
        $this->adicionaComponente(new CampoForm(Campo::SERIAL, 'codigo', 'Código'));
        $this->adicionaComponente(new CampoForm(Campo::TEXTO, 'descricao', 'Descrição'));
        $this->adicionaComponente(new CampoForm(Campo::INTEGER, 'Sistema.codigo', 'Sistema'));
    }
}
