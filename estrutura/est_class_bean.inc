<?php

/**
 * Description of est_class_bean
 *
 * @author marti
 */
abstract class Bean {
    
    public static function callSetter($oModel, $sCampo, $sValor) {
        $sSetter = 'set'.ucfirst($sCampo);
        $oModel->$sSetter($sValor);
    }
    
    public static function callGetter($oModel, $sCampo) {
        $sGetter = 'get'.ucfirst($sCampo);
        $oModel->$sGetter();
    }
    
}
