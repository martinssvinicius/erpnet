<?php

/**
 * Description of wun_class_estabelecimento_publico
 *
 * @author marti
 */
class ModelEstabelecimentoPublico {
    
    private $codigo;
    
    public function getCodigo() {
        return $this->codigo;
    }

    public function setCodigo($codigo): void {
        $this->codigo = $codigo;
    }

}
