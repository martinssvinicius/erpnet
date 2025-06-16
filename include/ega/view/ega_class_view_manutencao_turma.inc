<?php

namespace Ega\View;

use Campo;
use CampoForm;
use Ega\View\Componente\ViewComponenteCampoEstabelecimentoEducacao;
use Lista;
use ViewManutencao;

/**
 * Description of ega_class_view_manutencao_turma
 *
 * @author marti
 */
class ViewManutencaoTurma extends ViewManutencao {
    
    public function criaComponentes() {
        $this->adicionaCampoCodigo();
        $this->adicionaCampoNome();
        $this->adicionaCampoSigla();
        $this->adicionaCampoEstabelecimentoEducacao();
//        $this->adicionaCampoTurno();
    }

    private function adicionaCampoCodigo() {
        $oCampo = new CampoForm(Campo::SERIAL, 'codigo', 'Código');
        $this->adicionaComponente($oCampo);
    }

    private function adicionaCampoNome() {
        $oCampo = new CampoForm(Campo::TEXTO, 'nome', 'Nome');
        $this->adicionaComponente($oCampo);
    }

    private function adicionaCampoSigla() {
        $oCampo = new CampoForm(Campo::TEXTO, 'sigla', 'Sigla');
        $oCampo->setTamanho(50);
        $this->adicionaComponente($oCampo);
    }

    private function adicionaCampoEstabelecimentoEducacao() {
        $oCampo = new CampoForm(Campo::INTEGER, 'EstabelecimentoEducacao.EstabelecimentoPublico.codigo', 'Estabelecimento de Ensino');
        $oCampo->setExterno(\Ega\Enum\EnumEstabelecimentoEducacao::ROTINA);
        $oCampo->getExterno()->adicionaExterno($oCampo, 'EstabelecimentoPublico.codigo');
//        $oCampo = new ViewComponenteCampoEstabelecimentoEducacao();
        $this->adicionaComponente($oCampo);
    }

    private function adicionaCampoTurno() {
        $oCampo = new CampoForm(Campo::LISTA, 'Turno.codigo', 'Turno');
        $oCampo->setLista([
            new Lista(1, 'Matutino'),
            new Lista(2, 'Vespertino'),
        ]);
        $this->adicionaComponente($oCampo);
    }
    
}
