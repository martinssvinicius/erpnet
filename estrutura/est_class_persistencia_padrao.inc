<?php

/**
 * Description of glw_class_persistencia_padrao
 *
 * @author marti
 */
abstract class PersistenciaPadrao {
    
    protected $Model;
    
    public function __construct($oModel = null) {
        $this->Model = $oModel;
        $this->setRelacionamentos();
    }
    
    private $tabela;
    private $relacionamentos = [];
    private $chave = [];
    
    private $PersistenciaRelacionamento = [];
    
    protected abstract function setRelacionamentos();
    
    /**
     * arrumar essa estrutura de relacionamentos o mais rápido possível pois está péssimo
     */
    private function addRelacionamento($coluna, $model, $chave, $bText = false) {
//        $oPersistenciaRel = new PersistenciaRelacionamento();
//        $oPersistenciaRel->setNomeBanco($coluna);
//        $oPersistenciaRel->setNomeModel($model);
//        $oPersistenciaRel->setChave($chave);
//        $this->PersistenciaRelacionamento[] = $oPersistenciaRel;
         
        $this->relacionamentos[] = [$coluna, $model, $chave, $bText];
    }
    
    protected function addRelacionamentoAsInt($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave);
    }
    
    protected function addRelacionamentoAsSmallint($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave);
    }
    
    protected function addRelacionamentoAsBigint($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave);
    }
    
    protected function addRelacionamentoAsVarchar($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave, true);
    }
    
    protected function addRelacionamentoAsText($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave, true);
    }
    
    protected function addRelacionamentoAsDate($coluna, $model, $chave = false) {
        $this->addRelacionamento($coluna, $model, $chave, true);
    }
    
    protected function setTabela($schema, $tabela) {
        $this->tabela = $schema.'.'.$tabela;
    }
    
    protected function getTabela($bComSchema = true) {
        return $this->tabela;
    }
    
    public function insere() {
        $aColuna = [];
        $aValor = [];
        foreach ($this->relacionamentos as $relacionamento) {
            if ($relacionamento[2]) {
                $oQuery = new Query();
                $oQuery->set_sql("select max($relacionamento[0]) qtd from ".$this->getTabela());
                $dados = $oQuery->fetch_array();
                $iSeq = isset($dados['qtd']) ? $dados['qtd'] + 1 : 1;
                Bean::callSetter($this->Model, $relacionamento[1], $iSeq);
                
            }
            $aColuna[] = $relacionamento[0];
            if (isset($relacionamento[3]) && $relacionamento[3]) {
                $aValor[] = '\''.Bean::callGetter($this->Model, $relacionamento[1]).'\'';
            } else {
                $aValor[] = Bean::callGetter($this->Model, $relacionamento[1]);
            }
        };
        
        $oQuery = new Query();
        $oQuery->set_sql('insert into '.$this->getTabela().'('.implode(',', $aColuna).') values ('.implode(',', $aValor).')');
        return $oQuery->execute();
    }
    
    public function altera($bAlteraRelacionamentos = false) {
        
    }
    
    public function getSqlGetAll() {
        $sql = "select *
              from {$this->getTabela()}
                  order by 1 desc
                  limit 10
              ";
        foreach ($this->relacionamentos as $relacionamento) {
            if ($relacionamento[2]) {
//                $sql = $sql . " where $relacionamento[0] = 1";
            }
        }
        return Conexao::getConexao()->query($sql)->fetchAll(PDO::FETCH_ASSOC);
    }
    
    public function getFirstFromSql(\SQL $oSql) {
        $oQuery = new Query();
        $oQuery->set_sql($oSql->get_sql());
        $dados = $oQuery->fetch_array();
        return $dados;
    }
    
}
