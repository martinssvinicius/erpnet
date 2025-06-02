<?php

/**
 * Description of glw_class_view_manutencao
 *
 * @author marti
 */
abstract class ViewManutencao  {
    
    public function __construct() {
        $this->criaComponentes();
    }
    
    private $componentes;

    public function getComponentes() {
        return $this->componentes;
    }

    public function adicionaComponente($componente) {
        $this->componentes[] = $componente;
    }

    public abstract function criaComponentes();

    public function getValores() {
//        return json_decode($_POST['dados']);
    }
    
}
