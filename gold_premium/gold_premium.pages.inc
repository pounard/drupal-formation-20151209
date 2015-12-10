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

/**
 * Premium users list.
 */
function gold_premium_page_premium_users_list() {

  $header = [t("Id"), t("Name"), t("Profile")];
  $rows   = [];

  $q = db_select('users', 'u');
  $q->join('users_roles', 'ur', "ur.uid = u.uid");
  $q->join('role_permission', 'rp', "rp.rid = ur.rid");
  $uid_list = $q
    ->fields('u', ['uid'])
    ->condition('rp.permission', GOLD_PREMIUM_PERM_VIEW)
    ->execute()
    ->fetchCol()
  ;

  foreach ($uid_list as $uid) {
    if ($account = user_load($uid)) {
      $rows[] = [
        $account->uid,
        format_username($account),
        l(t("View"), 'user/' . $account->uid),
      ];
    }
  }

  return [
    '#theme'  => 'table__gold_premium__member_list',
    '#header' => $header,
    '#rows'   => $rows,
  ];
}

/**
 * Premium users list.
 */
function gold_premium_page_premium_users_list_plus_plus() {

  $header = [
    ['data' => t("Id"), 'field' => 'u.uid', 'order' => 'desc'],
    ['data' => t("Name"), 'field' => 'u.name'],
    ['data' => t("Profile")],
  ];

  $rows   = [];

  $q = db_select('users', 'u');
  $q->join('users_roles', 'ur', "ur.uid = u.uid");
  $q->join('role_permission', 'rp', "rp.rid = ur.rid");
  $uid_list = $q
    ->fields('u', ['uid'])
    ->condition('rp.permission', GOLD_PREMIUM_PERM_VIEW)
    ->extend('TableSort')
    ->orderByHeader($header)
    ->extend('PagerDefault')
    ->limit(7)
    ->execute()
    ->fetchCol()
  ;

  foreach (user_load_multiple($uid_list) as $account) {
    $rows[] = [
      $account->uid,
      format_username($account),
      l(t("View"), 'user/' . $account->uid),
    ];
  }

  return [
    'table' => [
      '#theme'  => 'table',
      '#header' => $header,
      '#rows'   => $rows,
    ],
    'pager' => [
      '#theme'    => 'pager',
      '#element'  => (PagerDefault::$maxElement - 1),
    ],
  ];
}
