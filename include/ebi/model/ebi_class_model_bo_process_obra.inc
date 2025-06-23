<?php

namespace Ebi\Model\Bo;

/**
 * Description of ebi_class_model_bo_process_obra
 *
 * @author marti
 */
class ModelBoProcessObra extends \ModelBoProcess {
    
    protected function afterInclusao() {
        parent::afterInclusao();
//        throw new \Exception('teste');
        
        \ElasticsearchHandler::index('obra', [
            'titulo' => $this->Model->getTitulo()
        ], $this->Model->getCodigo());
        
    }
    
}
