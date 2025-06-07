<?php

/**
 * Description of wun_class_view_manutencao_pessoa
 *
 * @author marti
 */
class ViewManutencaoPessoa extends ViewManutencao {
    
    public function criaComponentes() {
        $this->adicionaComponente(new CampoForm(Campo::BIGINT, 'codigo', 'Código'));
        $this->adicionaComponente(new CampoForm(Campo::TEXTO, 'nomeRazao', 'Nome'));
    }
    
}
