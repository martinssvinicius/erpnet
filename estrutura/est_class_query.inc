<?php

/**
 * Description of est_class_query
 *
 * @author marti
 */
class Query {
    
    private $SQL;
    
    private $conexao;
    
    public function getConexao() {
        if (!isset($this->conexao)) {
            $this->conexao = Conexao::getConexao();
        }
        return $this->conexao;
    }

    public function setConexao($conexao): void {
        $this->conexao = $conexao;
    }

    public function set_sql($sql) {
        $this->SQL = $sql;
    }
    
    public function get_sql() {
        return $sql;
    }
    
    public function execute() {
        return $this->getConexao()->prepare($this->SQL)->execute();
    }
    
}
