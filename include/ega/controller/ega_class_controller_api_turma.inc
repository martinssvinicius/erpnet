<?php

namespace Ega\Controller;

/**
 * Description of ega_class_controller_api_turma
 *
 * @author marti
 */
class ControllerApiTurma {
    
    public function getTurmas() {
//        $oPers = new \Ega\Persistencia\PersistenciaTurma();
        $oQuery = new \Query();
        $oQuery->set_sql("
            select *
              from ega.tbturma
        ");
        $oQuery->adiciona_condicao('tbturma.turcodigo', \SQL::OPERADOR_IGUAL, 107);
        $dados = $oQuery->fetch_array();
        echo toJson($dados);
    }
    
}
