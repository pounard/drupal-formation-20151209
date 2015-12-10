<?php
/**
 * @file
 * Pages.
 */

function gold_premium_mon_form($form, &$form_state, $pouet) {

  $form['pouet'] = [
    '#type'   => 'value',
    '#value'  => $pouet,
  ];

  $form['#pouet'] = $pouet;

  $form['name'] = [
    '#type'         => 'textfield',
    '#required'     => true,
    '#title'        => t("Your name"),
    '#description'  => t("Please, enter your name here"),
    '#attributes'   => ['placeholder' => $pouet],
  ];

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = [
    '#type'   => 'submit',
    '#value'  => t("Hop!"),
  ];

  return $form;
}

function gold_premium_mon_form_submit($form, &$form_state) {

  // #type = value
  $form_state['values']['pouet'];

  // toto
  $form['#pouet'];

  drupal_set_message(t("Hello, @name", [
    '@name' => check_plain($form_state['values']['name']),
  ]));
}

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
    'form'  => drupal_get_form('gold_premium_mon_form', "Pouet"),
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

/**
 * Premium users list.
 */
function gold_premium_list_all_nodes() {

  $r = db_select('node', 'n')
    ->fields('n', ['nid'])
    ->addTag('node_access')
    ->extend('PagerDefault')
    ->limit(7)
    ->execute()
    ->fetchCol()
  ;

  return [
    'nodes' => node_view_multiple(node_load_multiple($r), 'teaser'),
    'pager' => [
      '#theme'    => 'pager',
      '#element'  => (PagerDefault::$maxElement - 1),
    ],
  ];
}
