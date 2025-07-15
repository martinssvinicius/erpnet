<?php

require_once 'est_class_autoloader.inc';

header('Content-type: application/json; charset=ISO-8859-1');

set_exception_handler(function ($e) {
    http_response_code(500);
    echo json_encode([
        'status' => 'error',
        'message' => $e->getMessage(),
        'stack' => $e->getTraceAsString()
    ]);
    exit;
});

// Lidar com warnings, notices etc.
set_error_handler(function ($errno, $errstr, $errfile, $errline) {
    http_response_code(500);
    echo json_encode([
        'status' => 'error',
        'message' => "$errstr in $errfile on line $errline",
        'stack' => implode("\n", array_map(function ($t) {
            return "{$t['file']}:{$t['line']} - {$t['function']}";
        }, debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS)))
    ]);
    exit;
});

// Lidar com erros fatais no shutdown
register_shutdown_function(function () {
    $error = error_get_last();
    if ($error && in_array($error['type'], [E_ERROR, E_PARSE, E_CORE_ERROR, E_COMPILE_ERROR])) {
        http_response_code(500);
        echo json_encode([
            'status' => 'error',
            'message' => $error['message'] . " in " . $error['file'] . " on line " . $error['line'],
            'stack' => 'N/A (fatal error)'
        ]);
    }
});

require_once 'conexao.php';

$rotina = $_POST['rotina'];
$acao = $_POST['acao'];
$processo = $_POST['processo'];

$result = Conexao::getConexao()->query("
    select frmcontroller, 
           frminclude,
           frmtitulo
      from webbased.tbform 
     where rotcodigo = $rotina
       and acacodigo = $acao
")->fetchAll(PDO::FETCH_ASSOC);

Principal::getInstance()->Formulario->setTitulo($result[0]['frmtitulo']);
Principal::getInstance()->Formulario->setRotina($_POST['rotina']);
Principal::getInstance()->Formulario->setAcao($_POST['acao']);

if (isset($result)) {
    $fileController = $result[0]['frmcontroller'];
    $controller = str_replace('.inc', '', $fileController);
    $pieces = explode('_', $controller);
    $className = '';
    for ($i = 2; $i < count($pieces); $i++) {
        $className .= ucfirst($pieces[$i]);
    }
    $class = ucfirst($pieces[0]).'\\'.ucfirst($pieces[2]).'\\'.$className;
    
    
    $path = realpath(__DIR__ . "/../../include/$pieces[0]/$pieces[2]/$fileController");
    require_once $path;
    
    if (class_exists($class)) {
        $controller = new $class;
    } else {
        $controller = Factory::loadController($pieces[0], substr($className, 10, strlen($className)));
    }
    
    if ($processo != 'undefined') {
        $controller->$processo();
    }
    if ($controller instanceof ControllerConsulta) {
        $dados = $controller->montaConsulta();
    } else if ($controller instanceof ControllerManutencao) {
        $dados = $controller->getValoresJson();
    }
    
}

echo json_encode($dados);