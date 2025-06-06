<?php

/**
 * Description of est_factory
 *
 * @author marti
 */
abstract class Factory {
    
    public static function loadModel($sSigla, $sClass) {
        $classSnake = strtolower(preg_replace('/([a-z])([A-Z])/', '$1_$2', $sClass));
        require_once '../include/'.strtolower($sSigla).'/model/'.strtolower($sSigla).'_class_model_'.$classSnake.'.inc';
        $class = 'Model'.$sClass;
        return new $class;
    }
    
    public static function loadPersistencia($sSigla, $sClass) {
        $classSnake = strtolower(preg_replace('/([a-z])([A-Z])/', '$1_$2', $sClass));
        require_once '../include/'.strtolower($sSigla).'/persistencia/'.strtolower($sSigla).'_class_persistencia_'.$classSnake.'.inc';
        $class = 'Persistencia'.$sClass;
        return new $class;
    }
    
    public static function loadController($sSigla, $sClass) {
        $classSnake = strtolower(preg_replace('/([a-z])([A-Z])/', '$1_$2', $sClass));
        require_once '../include/'.strtolower($sSigla).'/controller/'.strtolower($sSigla).'_class_controller_'.$classSnake.'.inc';
        $class = 'Controller'.$sClass;
        return new $class;
    }
    
}
