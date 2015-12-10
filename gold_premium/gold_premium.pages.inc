<?php
/**
 * @file
 * Pages.
 */

/**
 * Am I premium page.
 */
function gold_premium_page_am_i_premium($account = null) {

  if (!$account) {
    $account = user_load($GLOBALS['user']->uid);
  }

  if (!$account) {
    return MENU_NOT_FOUND;
  }

  return [
    '#theme'      => 'premium_block',
    '#account'    => $account,
    '#is_premium' => user_access(GOLD_PREMIUM_PERM_VIEW, $account),
  ];
}
