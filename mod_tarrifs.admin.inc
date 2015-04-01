<?php

/* common */

function mod_tarrifs_common_form_submit($form, &$form_state)
{
    $entity = entity_ui_form_submit_build_entity($form, $form_state);
    $entity->save();

    $entity_id = entity_id($entity->entityType(), $entity);

    if ($entity_id) {
        $info = $entity->entityInfo();
        drupal_set_message(t('%label saved.', array('%label' => mod_tarrifs_label($entity, $entity->entityType()))));
        $form_state['redirect'] = $info['admin ui']['path'];
    } else {
        drupal_set_message('Unable to save '.$entity->entityType(), 'error');
    }
}

function mod_tarrifs_common_form_submit_delete($form, &$form_state)
{
    $entity = entity_ui_form_submit_build_entity($form, $form_state);
    $entity->delete();

    $info = $entity->entityInfo();
    $form_state['redirect'] =  $info['admin ui']['path'];
}


/* tarrifs */


function mod_tarrifs_form($form, &$form_state, $entity, $op = 'edit')
{

    field_attach_form('mod_tarrifs', $entity, $form, $form_state);

    $form['prefix'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Prefix'),
        '#default_value' => $entity->prefix,
        '#weight' => 50,
    );

    $form['price'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Price'),
        '#default_value' => $entity->price,
        '#weight' => 51,
    );

    $submit = array();
    if (!empty($form['#submit'])) {
        $submit += $form['#submit'];
    }

    $form['actions'] = array(
        '#weight' => 100,
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#submit' => $submit + array('mod_tarrifs_common_form_submit'),
    );

    $entity_id = entity_id($entity->entityType(), $entity);
    if (!empty($entity_id) && mod_tarrifs_access('edit', $entity)) {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete'),
            '#submit' => array('mod_tarrifs_common_form_submit_delete'),
        );
    }

    $form['#validate'][] = 'mod_tarrifs_form_validate';

    return $form;
}

function mod_tarrifs_form_validate($form, &$form_state) {

    $values = &$form_state['values'];

    if (floatval($values['price'])<=0) {
        form_set_error('price', t('Wrong price'));
    }

    if (!intval($values['prefix'])) {
        form_set_error('price', t('Wrong prefix'));
    }

    //refrence field to values

    $entity_form_attrs_map = array(
        'client' => 'mod_tarrifs_client_tid',
        'service' => 'mod_tarrifs_service_tid',
        'currency' => 'mod_tarrifs_currency_tid',
    );

    foreach ($entity_form_attrs_map as $entity_attr=>&$form_attr) {
        $tid = isset($values[$form_attr]['und'][0]['tid']) ? intval($values[$form_attr]['und'][0]['tid']) : 0;
        if ($tid && $term = taxonomy_term_load($tid)) {
            $values[$entity_attr] = $term->name;
        }
    }

    //drupal_set_message('<pre>'.print_r($values,1).'</pre>');

}
