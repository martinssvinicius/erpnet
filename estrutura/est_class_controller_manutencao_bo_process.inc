<?php

/**
 * Description of glw_class_controller_manutencao_bo_process
 *
 * @author marti
 */
abstract class ControllerManutencaoBoProcess extends ControllerManutencao {
    
    private $BoProcess;
    
    protected function getBoProcess() {
        if (!isset($this->BoProcess)) {
            $this->BoProcess = $this->getInstanceBoProcess();
        }
        return $this->BoProcess;
    }
        
    protected function getInstanceBoProcess() {
        $namespace = str_replace('ControllerManutencao', 'ModelBoProcess', str_replace('\\Controller\\', '\\Model\\Bo\\', get_called_class()));
//        if (class_exists($namespace)) {
            $oProcess = new $namespace($this->Model);
            $oProcess->setPersistencia($this->getPersistencia());
            return $oProcess;
            
//        }
        $pieces = explode('_', str_replace('.inc', '', basename((new ReflectionClass(get_called_class()))->getFileName())));
        $className = '';
        if (!empty($pieces)) {
            for ($i = 4; $i < count($pieces); $i++) {
                $className .= ucfirst($pieces[$i]);
            }
            return Factory::loadModel($pieces[0], 'BoProcess'.$className, [$this->Model]);
        }
        throw 'Não foi encontrada a classe ' . $className;
    }
    
    public function executaInclusaoDados() {
        if ($this->getBoProcess()) {
            return $this->getBoProcess()->processaInclusao();
        }
        return parent::executaInclusaoDados();
    }
    
}
