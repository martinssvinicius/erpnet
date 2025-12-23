<?php

/**
 * Description of conexao
 *
 * @author marti
 */
class Conexao {
    
    private static $instancia;
    
    /**
     * 
     * @return PDO
     */
    public static function getConexao() {
        if (!self::$instancia) {
            try {
//                self::$instancia = new PDO('pgsql:host=localhost;port=5432;dbname=erpnet', 'postgres', '9f18dd360ceb47d4888ab8271bc898c2', [
//                self::$instancia = new PDO('pgsql:host=localhost;port=5432;dbname=dbwin1252', 'postgres', '9f18dd360ceb47d4888ab8271bc898c2', [
                // self::$instancia = new PDO('pgsql:host=localhost;port=5432;dbname=erpnetlatin', 'postgres', '9f18dd360ceb47d4888ab8271bc898c2', [
                self::$instancia = new PDO('pgsql:host=localhost;port=5432;dbname=erpnet', 'postgres', 'postgres', [
                    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
                ]);
            } catch (Exception $ex) {
                die('Erro ao conectar: '. $ex->getMessage()) ;
            }
        }
        return self::$instancia;
    }
    
}
