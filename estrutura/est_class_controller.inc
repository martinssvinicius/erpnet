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
        if (class_exists($namespace)) {
            return new $namespace;
        }
        $pieces = explode('_', str_replace('.inc', '', basename((new ReflectionClass(get_called_class()))->getFileName())));
        $className = '';
        if (!empty($pieces)) {
            for ($i = 3; $i < count($pieces); $i++) {
                $className .= ucfirst($pieces[$i]);
            }
            return Factory::loadView($pieces[0], $className);
        }
        throw 'Não foi encontrada a classe ' . $className;
    }
    
}
