<?php
/**
 * @file
 * gold_premium.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function gold_premium_user_default_roles() {
  $roles = array();

  // Exported role: premium member.
  $roles['premium member'] = array(
    'name' => 'premium member',
    'weight' => 4,
  );

  return $roles;
}
