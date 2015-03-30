<?php

class TarrifsController extends EntityAPIController
{

    public function create(array $values = array())
    {
        $values += array(
            'created' => REQUEST_TIME,
            'changed' => REQUEST_TIME,
        );

        return parent::create($values);
    }

    public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array())
    {

        $content['description'] = array(
            array('#markup' => '<pre>'.json_encode($entity).'</pre>')
        );

        return parent::buildContent($entity, $view_mode, $langcode, $content);
    }


}

/**
 * UI controller for TarrifsUIController.
 */
class TarrifsUIController extends EntityDefaultUIController
{
    /**
     * Overrides hook_menu() defaults.
     */
    public function hook_menu()
    {
        $items = parent::hook_menu();
        $items[$this->path]['description'] = 'Manage tarrifs.';
        return $items;
    }
}

class TarrifsClientTypeController extends EntityAPIController
{

    public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array())
    {

        $content['description'] = array(
            array('#markup' => '<pre>'.json_encode($entity).'</pre>')
        );

        return parent::buildContent($entity, $view_mode, $langcode, $content);
    }
}

/**
 * UI controller for TarrifsClientType.
 */
class TarrifsClientTypeUIController extends EntityDefaultUIController
{
    /**
     * Overrides hook_menu() defaults.
     */
    public function hook_menu()
    {
        $items = parent::hook_menu();
        $items[$this->path]['description'] = 'Manage client types.';
        return $items;
    }
}

class TarrifsServiceTypeController extends EntityAPIController
{
    public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array())
    {

        $content['description'] = array(
            array('#markup' => '<pre>'.json_encode($entity).'</pre>')
        );

        return parent::buildContent($entity, $view_mode, $langcode, $content);
    }
}

/**
 * UI controller for TarrifsClientType.
 */
class TarrifsServiceTypeUIController extends EntityDefaultUIController
{
    /**
     * Overrides hook_menu() defaults.
     */
    public function hook_menu()
    {
        $items = parent::hook_menu();
        $items[$this->path]['description'] = 'Manage service types.';
        return $items;
    }
}

/**
 * Tarrifs class.
 */
class Tarrifs extends Entity
{
    public $client;
    public $service;
    public $prefix;
    public $price;
    public $currency;

    protected  $_client_entity;
    protected $_service_entity;

    public function getClientEntity() {

        if (!$this->_client_entity && $this->client) {
            $this->_client_entity = reset(entity_load('mod_tarrifs_client', array($this->client)));
        }

        return $this->_client_entity;
    }

    public function getServiceEntity() {

        if (!$this->_service_entity && $this->service) {
            $this->_service_entity = reset(entity_load('mod_tarrifs_service', array($this->service)));
        }

        return $this->_service_entity;
    }

    protected function defaultUri()
    {
        return array('path' => 'tarrifs/' . $this->identifier());
    }
}

/**
 * TarrifsClientType class.
 */
class TarrifsClientType extends Entity
{
    public $type;
    public $label;
    public $description;

    protected function defaultUri()
    {
        return array('path' => 'tarrifs_client/' . $this->identifier());
    }
}

/**
 * TarrifsServiceType class.
 */
class TarrifsServiceType extends Entity
{
    public $type;
    public $label;
    public $description;

    protected function defaultUri()
    {
        return array('path' => 'tarrifs_service/' . $this->identifier());
    }

}