<?php

class views_node_access_handler_field_controls extends views_handler_field {
  
  function option_definition() {
    $options = parent::option_definition();
    // Define options for user role.
    $options['views_node_access'] = array(
      'contains' => array(
        'user_roles' => array('default' => 0),
      ),
    );
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Hide unneeded things
    $form['exclude']['#access'] = FALSE;
    $form['alter']['#access'] = FALSE;
    $form['style_settings']['#access'] = FALSE;
    $form['empty_field_behavior']['#access'] = FALSE;
    // Views Node Access specific settings.
    $form['views_node_access'] = array(
      '#type' => 'fieldset',
      '#title' => t('Views Node Access'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $user_roles = user_roles();
    // User role "authenticated user" is not used when other custom
    // created user roles exist.
    if (sizeof($user_roles) > 2) {
      unset($user_roles[2]);
    }
    // User roles select.
    $form['views_node_access']['user_roles'] = array(
      '#type' => 'select',
      '#title' => t('User role'),
      '#options' => array(0 => t('None')) + $user_roles,
      '#default_value' => $this->options['views_node_access']['user_roles'],
    );
  }
  
  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);
    // Check if user role is set.
    if ($form_state['values']['options']['views_node_access']['user_roles'] == 0) {
      form_error($form['views_node_access'], t('User role must be selected!'));
    }
  }
  
  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    $user_roles = user_roles();
    if ($form_state['values']['options']['label'] == 'Views Node Access') {
      // Set label the same as user role name if default label was not changed.
      $form_state['values']['options']['label'] = $user_roles[$form_state['input']['options']['views_node_access']['user_roles']];
    }
  }
  
  function render($values) {
    // First check values in node_access table.
    $query = db_select('node_access', 'na');
    $query->fields('na');
    $query->condition('na.nid', $values->nid);
    $query->condition('na.gid', $this->options['views_node_access']['user_roles']);
    $query->condition('na.grant_view', 1);
    $result = $query->execute()->fetchObject();
    // Get the values from views_node_access table.
    $query = db_select('views_node_access', 'foo');
    $query->fields('foo');
    $query->condition('foo.nid', $values->nid);
    $query->condition('foo.rid', $this->options['views_node_access']['user_roles']);
    $result2 = $query->execute()->fetchObject();
    if (!$result && !$result2) {
      // The access settings can not be changed from here.
      $img_options = array(
        'path' => base_path() . drupal_get_path('module', 'taxonomy_tools') . '/img/false.png',
        'title' => t('not changeable'),
        'attributes' => array(),
      );
      $markup = theme_image($img_options);
      $element = array(
        '#markup' => $markup,
        '#access' => user_access('administer node access'),
      );
    }
    else {
      // Display links for changing the value.
      // Make sure Drupal Ajax framework javascript is around.
      drupal_add_library('system', 'drupal.ajax');
      $destination = drupal_get_destination();
      $link_options = array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array(
            'use-ajax',
            'access-' . $values->nid . '-' . $this->options['views_node_access']['user_roles'],
          ),
        ),
        'query' => array(
          'destination' => $destination['destination'],
        ),
      );
      $access = $result2 ? 'false' : 'true';
      $opposite = $access == 'true' ? 'false' : 'true';
      $img_options = array(
        'path' => base_path() . drupal_get_path('module', 'taxonomy_tools') . '/img/' . $access . '.png',
        'title' => t('change'),
        'attributes' => array(),
      );
      $link = 'views-node-access/nojs/' . $values->nid . '/' . $this->options['views_node_access']['user_roles'] . '/' . $opposite;
      $markup = l(theme_image($img_options), $link, $link_options);
      $element = array(
        '#markup' => $markup,
        '#access' => user_access('administer node access'),
      );
    }
    return drupal_render($element);
  }
}
