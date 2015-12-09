<?php
/**
 * @file
 * gold_premium.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gold_premium_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view premium content'.
  $permissions['view premium content'] = array(
    'name' => 'view premium content',
    'roles' => array(
      'premium member' => 'premium member',
    ),
    'module' => 'gold_premium',
  );

  return $permissions;
}
