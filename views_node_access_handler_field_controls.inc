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
    // User roles select.
    $form['views_node_access']['user_roles'] = array(
      '#type' => 'select',
      '#title' => t('User role'),
      '#options' => array(0 => t('None')) + $user_roles,
      '#default_value' => $this->options['views_node_access']['user_roles'],
    );
//    $myFile = "/tmp/handlerDebug.txt";
//    $fh = fopen($myFile, 'a+') or die("can't open file");;
//    fwrite($fh, print_r($this->options, TRUE));
//    fclose($fh);
  }
  
  function render($values) {
//    $query = db_select('node_access', 'na');
//    $query->addField('na', 'grant_view', 'view');
//    $query->condition('na.nid', $values->nid);
//    $query->condition('na.realm', 'views_node_access');
//    $query->condition('na.gid', $this->options['views_node_access']['user_roles']);
    $myFile = "/tmp/handlerDebug.txt";
    $fh = fopen($myFile, 'a+') or die("can't open file");;
    fwrite($fh, print_r($this->options, TRUE));
    fclose($fh);
  }
  
}
