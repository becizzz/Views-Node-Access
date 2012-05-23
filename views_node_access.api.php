<?php

/**
 * @file
 * Hooks provided by the Views Node Access module.
 */

/**
 * Act on node access changes.
 *
 * @param stdClass $node
 *   Node object.
 */
function hook_node_access_change($node) {
  drupal_set_message($node->title);
}
