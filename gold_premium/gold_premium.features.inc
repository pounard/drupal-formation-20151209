<?php
/**
 * @file
 * gold_premium.features.inc
 */

/**
 * Implements hook_node_info().
 */
function gold_premium_node_info() {
  $items = array(
    'premium' => array(
      'name' => t('Premium'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
