<?php

/**
 * Description of est_class_sql
 *
 * @author marti
 */
class SQL {
    
    const OPERADOR_IGUAL = '=';
    
    private $sql;
    
    public function set_sql($sql) {
        $this->sql = $sql;
    }
    
    public function get_sql() {
        return $this->sql;
    }
    
}
