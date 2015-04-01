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

    protected function defaultUri()
    {
        return array('path' => 'tarrifs/' . $this->identifier());
    }
}
