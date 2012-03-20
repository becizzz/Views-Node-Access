<?php

/**
 * Implements hook_views_data_alter(). 
 */
function views_node_access_views_data_alter(&$data) {
  $data['node']['views_node_access'] = array(
    'title' => t('Views Node Access'),
    'group' => t('Views Node Access'),
    'help' => t('Node Access Controls.'),
    'real field' => 'nid',
    'field' => array(
      'handler' => 'views_node_access_handler_field_controls',
      'click sortable' => FALSE,
    ),
  );
}

/**
 * Implements hook_views_handlers().
 */
function views_node_access_views_handlers() {
  return array(
    'handlers' => array(
      'views_node_access_handler_field_controls' => array(
        'parent' => 'views_handler_field',
      )
    )
  );
}
