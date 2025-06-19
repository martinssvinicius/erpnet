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
        
        
        $path = $_SERVER['DOCUMENT_ROOT'] . '/libs/File_MARC-1.4.1/File/MARC.php';
        require_once $path;
        
        $marcFile = new File_MARC('caminho/para/seuarquivo.mrc');
        
//        parent::processaDadosInclusao();
//        throw \Exception();
    }
    
}
