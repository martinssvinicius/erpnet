<?php

/**
 * Description of conexao
 *
 * @author marti
 */
class Conexao {
    
    private static $instancia;
    
    public static function getConexao() {
        if (!self::$instancia) {
            try {
                self::$instancia = new PDO('pgsql:host=localhost;port=5432;dbname=postgres', 'postgres', '9f18dd360ceb47d4888ab8271bc898c2', [
                    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
                ]);
            } catch (Exception $ex) {
                die('Erro ao conectar: '. $ex->getMessage()) ;
            }
        }
        return self::$instancia;
    }
    
}
