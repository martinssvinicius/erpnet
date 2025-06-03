<?php

namespace Ega\Model;

/**
 * Description of ega_class_model_estabelecimento_educacao
 *
 * @author marti
 */
class ModelEstabelecimentoEducacao {
    
    /**
     * @var \ModelEstabelecimentoPublico
     */
    private $EstabelecimentoPublico;

    public function setEstabelecimentoPublico(ModelEstabelecimentoPublico $EstabelecimentoPublico): void {
        $this->EstabelecimentoPublico = $EstabelecimentoPublico;
    }
    
    public function getEstabelecimentoPublico(): \ModelEstabelecimentoPublico {
        if (!isset($this->EstabelecimentoPublico)) {
            $this->EstabelecimentoPublico = \Factory::loadModel('WUN', 'EstabelecimentoPublico');
        }
        return $this->EstabelecimentoPublico;
    }

}
