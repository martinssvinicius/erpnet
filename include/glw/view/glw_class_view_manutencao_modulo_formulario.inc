<?php

/**
 * Description of glw_class_view_manutencao_rotina
 *
 * @author marti
 */
class ViewManutencaoModuloFormulario extends ViewManutencao {
    
    public function criaComponentes() {
        $this->adicionaComponente(new CampoForm(Campo::INTEGER, 'Rotina.codigo', 'Rotina'));
        $this->adicionaComponente(new CampoForm(Campo::INTEGER, 'Acao.codigo', 'Ação'));
        $this->adicionaComponente(new CampoForm(Campo::TEXTO, 'titulo', 'Título'));
        $this->adicionaComponente(new CampoForm(Campo::INTEGER, 'Modulo.codigo', 'Módulo'));
    }
}
