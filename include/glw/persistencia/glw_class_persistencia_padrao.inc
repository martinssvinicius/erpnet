<?php

/**
 * Description of glw_class_persistencia_padrao
 *
 * @author marti
 */
abstract class PersistenciaPadrao {
    
    public function __construct() {
        $this->setRelacionamentos();
    }
    
    private $tabela;
    private $relacionamentos = [];
    private $chave = [];
    
    protected abstract function setRelacionamentos();
    
    private function addRelacionamento($coluna, $model, $chave) {
        $this->relacionamentos[] = [$coluna, $model, $chave];
    }
    
    protected function addRelacionamentoAsBigint($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave);
    }
    
    protected function addRelacionamentoAsVarchar($coluna, $model, $chave) {
        $this->addRelacionamento($coluna, $model, $chave);
    }
    
    protected function setTabela($schema, $tabela) {
        $this->tabela = $schema.'.'.$tabela;
    }
    
    public function insere() {
        
    }
    
    public function altera() {
        
    }
    
    public function getSqlGetAll() {
        $sql = "select *
              from {$this->tabela}";
        foreach ($this->relacionamentos as $relacionamento) {
            if ($relacionamento[2]) {
//                $sql = $sql . " where $relacionamento[0] = 1";
            }
        }
        return Conexao::getConexao()->query($sql)->fetchAll(PDO::FETCH_ASSOC);
    }
    
}
