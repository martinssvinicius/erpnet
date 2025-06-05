<?php

/**
 * Description of est_class_principal
 *
 * @author marti
 */
class Principal {
    
    public function __construct() {
        $this->Formulario = new Formulario();
    }
    
    /**
     * @var Formulario
     */
    public $Formulario;
    
    /**
     * @return \Principal
     */
    public static function getInstance() {
        global $principal;
        if (!$principal) {
            $principal = new Principal();
        }
        return $principal;
    }
    
    public function getParametro() {
        return json_decode($_POST['parametro'], true);
    }
    
    public function getChave() {
        
    }
    
    public function getParametroAsInt($sNome) {
        $param = $this->getParametro();
        if (isset($param[$sNome])) {
            return $param[$sNome];
        }
    }
    
    public function getParametroAsBigint($sNome) {
        return $this->getParametroAsInt($sNome);
    }
    
}
