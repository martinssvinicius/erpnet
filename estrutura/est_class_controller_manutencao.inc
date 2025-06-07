<?php

/**
 * Description of ega_class_controller_manutencao
 *
 * @author marti
 */
abstract class ControllerManutencao extends Controller {
    
    protected $Model;
    protected $Persistencia;
    
    public function __construct() {
        parent::__construct();
        $this->Model = $this->getInstanceModel();
    }
    
    public function getPersistencia() {
        if (!isset($this->Persistencia)) {
            $this->Persistencia = $this->getInstancePersistencia();
        }
        return $this->Persistencia;
    }
    
    protected function getInstancePersistencia() {
        $namespace = str_replace(['ControllerManutencao', 'Controller'], 'Persistencia', get_called_class());
        if (class_exists($namespace)) {
            return new $namespace($this->Model);
        }
        $pieces = explode('_', str_replace('.inc', '', basename((new ReflectionClass(get_called_class()))->getFileName())));
        $className = '';
        if (!empty($pieces)) {
            for ($i = 4; $i < count($pieces); $i++) {
                $className .= ucfirst($pieces[$i]);
            }
            return Factory::loadPersistencia($pieces[0], $className, [$this->Model]);
        }
        throw 'Não foi encontrada a classe ' . $className;
    }

    protected function getInstanceModel() {
        $namespace = str_replace(['ControllerManutencao', 'Controller'], 'Model', get_called_class());
        if (class_exists($namespace)) {
            return new $namespace;
        }
        $pieces = explode('_', str_replace('.inc', '', basename((new ReflectionClass(get_called_class()))->getFileName())));
        $className = '';
        if (!empty($pieces)) {
            for ($i = 4; $i < count($pieces); $i++) {
                $className .= ucfirst($pieces[$i]);
            }
            return Factory::loadModel($pieces[0], $className);
        }
        throw 'Não foi encontrada a classe ' . $className;
    }
    
    public function criaTela() {
        $this->Tela = $this->getInstanceTela();
        $this->afterCriaTela();
    }
    
    public function setBean($oTela, $oModel) {
        $this->Tela->getValores();
        foreach ($this->Tela->getComponentes() as $oComponente) {
            Bean::callSetter($oModel, $oComponente->getNome(), $oComponente->getValor());
        }
    }
    
    protected function afterCriaTela() {
        
    }
    
    public function getValoresJson() {
        $this->criaTela();
        return /*json_encode(*/[
            'tipo' => 2,
            'campos' => $this->Tela->getComponentes(),
            'titulo' => $this->Principal->Formulario->getTitulo()
        ]/*)*/;
    }
    
    public function processaDados() {
        $iAcao = $this->Principal->Formulario->getAcao();
        switch ($iAcao) {
            case Formulario::ACAO_INCLUIR:
                return $this->processaDadosInclusao();
            default:
                return $this->processaDadosOutrasAcoes();
        }
    }
    
    public function executaInclusaoDados() {
        return $this->getPersistencia()->insere();
    }
    
    public function processaDadosInclusao() {
        $this->criaTela();
        $this->setBean($this->Tela, $this->Model);
        if ($bOk = $this->executaInclusaoDados()) {
            
        }
        return $bOk;
    }
    
    public function processaDadosOutrasAcoes() {
        
    }
    
}
