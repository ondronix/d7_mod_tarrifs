<?php

function mod_tarrifs_view($type, $id) {

    $entities = entity_load($type, array($id));

    $entity = reset($entities);

    drupal_set_title($entity->entityType(). ': '.$entity->label());
    $output = entity_view($type, array($entity));

    return $output;

}