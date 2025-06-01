<?php

require_once 'autoload.php';

header('Content-type: application/json');

require_once 'conexao.php';

$rotina = $_POST['rotina'];
$acao = $_POST['acao'];

$result = Conexao::getConexao()->query("
    select frmcontroller, 
           frminclude 
      from webbased.tbform 
     where rotcodigo = $rotina
       and acacodigo = $acao
")->fetchAll(PDO::FETCH_ASSOC);

if (isset($result)) {
    $fileController = $result[0]['frmcontroller'];
    $controller = str_replace('.inc', '', $fileController);
    $pieces = explode('_', $controller);
    
    $class = ucfirst($pieces[0]).'\\'.ucfirst($pieces[2]).'\\'.ucfirst($pieces[2]).ucfirst($pieces[3]).ucfirst($pieces[4]);
    
    
    $path = realpath(__DIR__ . "/../../include/$pieces[0]/$pieces[2]/$fileController");
    require_once $path;
    $controller = new $class;
    
    if ($controller instanceof ControllerConsulta) {
        $dados = $controller->montaConsulta();
    } else if ($controller instanceof ControllerManutencao) {
        $dados = $controller->montaConsulta();
    }
    
}

echo json_encode($dados);