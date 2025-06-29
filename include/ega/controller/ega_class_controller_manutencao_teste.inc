<?php

namespace Ega\Controller;

use ControllerManutencao;
use File_MARC;

/**
 * Description of ega_class_controller_manutencao_teste
 *
 * @author marti
 */
class ControllerManutencaoTeste extends ControllerManutencao {
    
    public function processaDadosInclusao() {
        require_once 'C:\vinicius.martins\Repositório\erpnet\estrutura\libs\phpoffice\phpspreadsheet\src\PhpSpreadsheet\IOFactory.php';
        //    $oSpreadsheet = \PhpOffice\PhpSpreadsheet\IOFactory::load($aFile['tmp_name']);
//        $oSpreadsheet = \PhpOffice\PhpSpreadsheet\IOFactory::load('../temp/layout_de_importacao_e_exportacao_2025.xlsx');
        $oSpreadsheet = \PhpOffice\PhpSpreadsheet\IOFactory::load($_FILES['teste']['tmp_name']);
        
        
//        $url = 'https://books.google.com/books/content?id=f7JVBQAAQBAJ&printsec=frontcover&img=1&zoom=5&edge=curl&source=gbs_api';
//        $data = file_get_contents($url);
//        file_put_contents("isbn.jpg", $data);
        
        
        
        
        
//        $path = $_SERVER['DOCUMENT_ROOT'] . '/libs/File_MARC-1.4.1/File/MARC.php';
//        require_once $path;
//        
//        $marcFile = new File_MARC('caminho/para/seuarquivo.mrc');
        
//        parent::processaDadosInclusao();
//        throw \Exception();
    }
    
}
