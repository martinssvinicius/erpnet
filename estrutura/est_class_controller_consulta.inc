<?php

/**
 * Description of glw_class_controller_consulta
 *
 * @author marti
 */
abstract class ControllerConsulta extends Controller {
    
    public function __construct() {
        parent::__construct();
        $this->getPersistenciaConsulta();
        $this->Tela = $this->getInstanceTela();
    }
    
    private $PersistenciaConsulta;

    public function setPersistenciaConsulta($PersistenciaConsulta) {
        $this->PersistenciaConsulta = $PersistenciaConsulta;
    }
    
    public function getPersistenciaConsulta() {
        if (!isset($this->PersistenciaConsulta)) {
            $this->PersistenciaConsulta = $this->getInstancePersistencia();
        }
        return $this->PersistenciaConsulta;
    }
    
    protected function getInstancePersistencia() {
        $pieces = explode('\\', get_class($this));
        if (count($pieces) > 1) {
            $class = "$pieces[0]\\Persistencia\\".str_replace('ControllerConsulta', 'Persistencia', $pieces[2]);
            return new $class;
        } else {
            $file = basename((new ReflectionClass(get_called_class()))->getFileName());
            $file = str_replace('.inc', '', $file);
            $explod = explode('_', $file);
            $sigla = $explod[0];
            $class = str_replace('ControllerConsulta', '', $pieces[0]);
            return Factory::loadPersistencia($sigla, $class);
        }
    }

    
    public function montaConsulta() {
        return [    
            'tipo' => 1,
            'campos' => $this->Tela->getCampos(),
            'dados' => $this->getPersistenciaConsulta()->getSqlGetAll(),
            'titulo' => $this->Principal->Formulario->getTitulo(),
            'acoes' => $this->Tela->getAcoes(),
        ];
    }
    
}
