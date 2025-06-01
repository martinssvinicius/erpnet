<?php

/**
 * Description of glw_class_controller_consulta
 *
 * @author marti
 */
abstract class ControllerConsulta {
    
    public function __construct() {
        $this->getPersistenciaConsulta();
    }
    
    private $PersistenciaConsulta;

    public function setPersistenciaConsulta($PersistenciaConsulta): void {
        $this->PersistenciaConsulta = $PersistenciaConsulta;
    }
    
    public function getPersistenciaConsulta() {
        if (!isset($this->PersistenciaConsulta)) {
            $this->PersistenciaConsulta = $this->getInstancePersistencia();
        }
        return $this->PersistenciaConsulta;
    }
    
    protected function getInstancePersistencia() {
        $pieces = explode('\\', get_class($this));
        $class = "$pieces[0]\\Persistencia\\".str_replace('ControllerConsulta', 'Persistencia', $pieces[2]);
        return new $class;
    }

    
    public function montaConsulta() {
        return $this->getPersistenciaConsulta()->getSqlGetAll();
    }
    
}
