<?php

/**
 * Description of est_class_query
 *
 * @author marti
 */
class Query extends SQL {
    
    private $SQL;
    
    private $Conexao;
    
    public function getConexao() {
        if (!isset($this->Conexao)) {
            $this->Conexao = Conexao::getConexao();
        }
        return $this->Conexao;
    }

    public function setConexao($conexao) {
        $this->Conexao = $conexao;
    }

    public function execute() {
//        return $this->getConexao()->query($this->get_sql())->execute();
        return $this->prepare()->execute();
    }
    
    public function prepare() {
        return $this->getConexao()->prepare($this->get_sql());
    }
    
    public function fetch_array() {
        return $this->getConexao()->query($this->get_sql())->fetch(PDO::FETCH_ASSOC);
//        return $this->prepare()->fetchAll(PDO::FETCH_ASSOC);
    }
    
    public function fetch_object() {
        return $this->prepare()->fetchAll(PDO::FETCH_OBJ);
    }
    
    public function adiciona_condicao($sColuna, $sOperador, $sValor = '', $sValor2 = '') {
        $sSql = $this->get_sql();
        $iPosWhere = strpos($this->get_sql(), 'where');
        $sSql .= $iPosWhere == false ? ' where ' : ' and ' ;
        switch ($sOperador) {
            case SQL::OPERADOR_IGUAL:
                $sSql .= "$sColuna = $sValor";
                break;
        }
        $this->set_sql($sSql);
    }
        
    
}
