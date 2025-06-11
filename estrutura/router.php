<?php

$path = parse_url($_SERVER["REQUEST_URI"], PHP_URL_PATH);
$file = __DIR__ . $path;

if (file_exists($file) && !is_dir($file)) {
    return false;
}

if ($path == '/erpnet/teste_martins.php') {
    require __DIR__ . '/../teste_martins.php';
    return;
}

require __DIR__ . '/index.php';
