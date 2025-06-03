<?php

/**
 * Description of est_factory
 *
 * @author marti
 */
abstract class Factory {
    
    public static function loadModel($sSigla, $sModel) {
        $classSnake = strtolower(preg_replace('/([a-z])([A-Z])/', '$1_$2', $sModel));
        require_once '../include/'.strtolower($sSigla).'/model/'.strtolower($sSigla).'_class_model_'.$classSnake.'.inc';
        $class = 'Model'.$sModel;
        return new $class;
    }
    
}
