<?php

/**
 * Description of ega_class_controller_manutencao
 *
 * @author marti
 */
abstract class ControllerManutencao extends Controller {
    
    protected $Model;
    
    protected $Tela;
    
    public function __construct() {
        parent::__construct();
        $this->Model = $this->getInstanceModel();
    }
    
    protected function getInstanceModel() {
        $namespace = str_replace(['ControllerManutencao', 'Controller'], 'Model', get_called_class());
        return new $namespace;
    }
    
    protected function getInstanceTela() {
        $namespace = str_replace('Controller', 'View', get_called_class());
        return new $namespace;
    }
    
    public function criaTela() {
        $this->Tela = $this->getInstanceTela();
        $this->afterCriaTela();
    }
    
    public function setBean($oTela, $oModel) {
        foreach ($this->Tela->getComponentes() as $oComponente) {
            Bean::callSetter($oModel, $oComponente->getNome(), $sValor);
        }
    }
    
    protected function afterCriaTela() {
        
    }
    
    public function getValoresJson() {
        $this->criaTela();
        return /*json_encode(*/[
            'tipo' => 2,
            'campos' => $this->Tela->getComponentes()
        ]/*)*/;
    }
    
    public function processaDados() {
        $this->criaTela();
        $this->setBean($this->Tela, $this->Model);
        if ($bOk = $this->executaInclusaoDados()) {
            
        }
        return $bOk;
    }
    
    public function executaInclusaoDados() {
        $this->Model->getPersistencia()->insere();
    }
    
}
