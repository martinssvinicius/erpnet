<?php

require_once './est_class_autoloader.inc';

$path = parse_url($_SERVER["REQUEST_URI"], PHP_URL_PATH);
$file = __DIR__ . $path;


//if (preg_match('#^/api/v1/pessoas/?$#', $path)) {
if ($path == '/erpnet/api/v1/turmas') {
    
    header('Content-Type: application/json');
    
    $_SERVER['REQUEST_METHOD'];
    
    $controller = new Ega\Controller\ControllerApiTurma();
    $controller->getTurmas();
//    http_response_code(404);
    
    exit;
}

if (file_exists($file) && !is_dir($file)) {
    return false;
}

if ($path == '/erpnet/teste_martins.php') {
    require __DIR__ . '/../teste_martins.php';
    return;
}

if (str_starts_with($path, '/erpnet/sistema/')) {
    require __DIR__ . '/index.php';
    exit;
}


http_response_code(404);
?>
<script>
    document.cookie = 'XDEBUG_SESSION=VSCODE';
</script>