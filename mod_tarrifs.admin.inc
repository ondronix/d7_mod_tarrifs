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

    $entity->mod_tarrifs_client_ref = $entity->client ? array('und'=>array(array('target_id'=>$entity->client))) : NULL;
    $entity->mod_tarrifs_service_ref = $entity->service ? array('und'=>array(array('target_id'=>$entity->service))) : NULL;

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

    $form['currency'] = array(
        '#type' => 'select',
        '#required' => TRUE,
        '#title' => t('Currency'),
        '#default_value' => $entity->currency ? $entity->currency : 'usd',
        '#options' => array('usd'=>'USD', 'eur'=>'EUR'),
        '#weight' => 52,
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
    $client_target_id = intval($values['mod_tarrifs_client_ref']['und'][0]['target_id']);
    if ($client_target_id) $values['client'] = $client_target_id;

    $service_target_id = intval($values['mod_tarrifs_service_ref']['und'][0]['target_id']);
    if ($service_target_id) $values['service'] = $service_target_id;
}

/* tarrifs_client */

function mod_tarrifs_client_form($form, &$form_state, $entity, $op = 'edit')
{

    $form['type'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Name'),
        '#default_value' => $entity->type,
    );

    $form['label'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Label'),
        '#default_value' => $entity->label,
    );

    $form['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => $entity->description,
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

    return $form;
}


/* tarrifs_service */

function mod_tarrifs_service_form($form, &$form_state, $entity, $op = 'edit')
{
    $form = mod_tarrifs_client_form($form, $form_state, $entity, $op);

    return $form;
}
