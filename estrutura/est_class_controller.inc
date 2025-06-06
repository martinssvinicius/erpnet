<?php

/**
 * Description of glw_class_controller
 *
 * @author marti
 */
abstract class Controller {
    
    protected $Principal;
    protected $Tela;

    public function __construct() {
        $this->Principal = Principal::getInstance();
    }
    
    protected function getInstanceTela() {
        $namespace = str_replace('Controller', 'View', get_called_class());
        return new $namespace;
    }
    
}
