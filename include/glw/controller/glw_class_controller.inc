<?php

/**
 * Description of glw_class_controller
 *
 * @author marti
 */
abstract class Controller {
    
    protected $Principal;

    public function __construct() {
        $this->Principal = Principal::getInstance();
    }
    
}
