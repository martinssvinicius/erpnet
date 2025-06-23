<?php

use Elastic\Elasticsearch\ClientBuilder;

require 'vendor/autoload.php';

/**
 * Description of est_class_elasticsearch_handler
 *
 * @author marti
 */
abstract class ElasticsearchHandler {
    
    private static $Connection;
    
    private static function getConnection() {
        if (!isset(self::$Connection)) {
            self::$Connection = ClientBuilder::create()
                ->setHosts(['localhost:9200'])
                ->build();
        }
        return self::$Connection;
    }
    
    public static function index($name, $data, $id = null) {
        $param['index'] = $name;
        $param['body'] = $data;
        if (!is_null($id)) {
            $param['id'] = $id;
        }
        self::getConnection()->index($param);
    }
    
    public static function search($params) {
        self::getConnection()->search($params);
    }
    
}
