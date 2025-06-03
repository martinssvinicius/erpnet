<?php

/**
 * Description of est_class_bean
 *
 * @author marti
 */
abstract class Bean {
    
    public static function callSetter($oModel, $sCampo, $sValor) {
        $campos = explode('.', $sCampo);
        $oModelPartial = $oModel;
        if (count($campos) > 1) {
            foreach ($campos as $indice => $campo) {
                if ($indice == count($campos)-1) {
                    self::callSetter($oModelPartial, $campo, $sValor);
                    return;
                }
                $oModelPartial = self::callGetter($oModelPartial, $campo);
            }
        }
        $sSetter = 'set'.ucfirst($sCampo);
        $oModel->$sSetter($sValor);
    }
    
    public static function callGetter($oModel, $sCampo) {
        $campos = explode('.', $sCampo);
        $oModelPartial = $oModel;
        if (count($campos) > 1) {
            foreach ($campos as $indice => $campo) {
                if ($indice == count($campos)-1) {
                    return self::callGetter($oModelPartial, $campo, $sValor);
                }
                $oModelPartial = self::callGetter($oModelPartial, $campo);
            }
        }
        $sGetter = 'get'.ucfirst($sCampo);
        return $oModel->$sGetter();
    }
    
}
