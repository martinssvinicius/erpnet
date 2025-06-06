<?php

spl_autoload_register(function($classe) {
    require_once 'conexao.php';
    
    
    require_once 'est_class_formulario.inc';
    require_once 'est_class_factory.inc';
    require_once 'est_class_query.inc';
    require_once 'est_class_sql.inc';
    require_once 'est_class_bean.inc';
    require_once 'est_class_principal.inc';
    require_once 'est_class_campo_consulta.inc';
    require_once 'est_class_acao_consulta.inc';
    require_once 'est_class_lista.inc';
    require_once 'est_class_campo_form.inc';
    require_once 'est_class_campo.inc';
    require_once 'est_class_controller.inc';
    require_once 'est_class_persistencia_padrao.inc';
    require_once 'est_class_controller_consulta.inc';
    require_once 'est_class_controller_manutencao.inc';
    require_once 'est_class_model_bo_process.inc';
    require_once 'est_class_controller_manutencao_bo_process.inc';
    require_once 'est_class_view_consulta.inc';
    require_once 'est_class_view_manutencao.inc';
    
    $pieces = explode('\\', $classe);
    
    if (isset($pieces[1])) {
        $output = strtolower(preg_replace('/([a-z])([A-Z])/', '$1_$2', $pieces[2]));
        if ($pieces[1] == 'Enum') {
            $caminho = "../include/".strtolower($pieces[0])."/model/".strtolower($pieces[1])."/".strtolower($pieces[0]).'_class_'.$output.'.inc'; 
        } else {
            $caminho = "../include/".strtolower($pieces[0])."/".strtolower($pieces[1])."/".strtolower($pieces[0]).'_class_'.$output.'.inc'; 
        }
        if (file_exists($caminho)) {
            require_once $caminho;
        }
    }
});