<?php

//system_rebuild_theme_data();
//drupal_theme_rebuild();

/**
 * Implements hook_preprocess_html().
 */
function ssd_preprocess_html(&$variables) {
  switch (theme_get_setting('bootstrap_navbar_position')) {
    case 'fixed-top':
      $variables['classes_array'][] = 'navbar-is-fixed-top';
      break;

    case 'fixed-bottom':
      $variables['classes_array'][] = 'navbar-is-fixed-bottom';
      break;

    case 'static-top':
      $variables['classes_array'][] = 'navbar-is-static-top';
      break;
  }
}

function ssd_preprocess_node(&$variables) {
  $node = $variables['node'];
  $variables['title'] = check_plain($node->title);
  
  if ($node->type == 'article') {
    // Get only the first body summary for a module.
    $body = field_get_items('node', $node, 'body');
    $variables['summary'] = field_view_value('node', $node, 'body', $body[0], 'teaser');
    $variables['metadata'] = field_view_field('node', $node, 'field_metadata', 'default');
  }
}

function ssd_form_search_form_alter(&$form, &$form_state, $form_id) {
  $form['#action'] = url('searchapi');
  $form['#method'] = 'GET';
  $form['form_build_id']['#access'] = FALSE;
  $form['form_token']['#access'] = FALSE;
  $form['form_id']['#access'] = FALSE;
  $form['basic']['submit']['#name'] = '';
}

function ssd_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#id'] == 'views-exposed-form-search-page') {
    $form['submit']['#value'] = t('Search');
  }
}

function ssd_preprocess_page(&$variables) {
  global $base_path;

  $variables['global_container'] = '';
  if (!isset($variables['node'])) {
    $variables['global_container'] = ' container';
  }
  $variables['theme_path'] = $variables['base_path'] . $variables['directory'];
  $variables['eff_logo_small'] = $variables['theme_path'] . '/img/eff-logo.png';
  
  $variables['is_playlist'] = false;
  $variables['playlist_graphic'] = '';
  // Is the current page a playlist node?
  if (isset($variables['node'])) {
    if ($variables['node']->type == 'playlist') {
      $variables['is_playlist'] = true;
      // Show playlist graphic.
      $variables['playlist_graphic'] = '<img src="'. $base_path . $variables['directory'] . '/img/play-c-header.png' .'" alt="'. t('Playlist') .'" />';
    }
  }
  // Show playlist graphic while on the /playlist page.
  if (arg(0) == 'playlist') {
    $variables['playlist_graphic'] = '<img src="'. $base_path . $variables['directory'] . '/img/play-c-header.png' .'" alt="'. t('Playlist') .'" />';
  }

  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-9"';
  }
  // For pages that need full width backgrounds. */
  elseif (arg(0) == 'index' || $variables['is_front'] == TRUE) {
    $variables['content_column_class'] = ' container-full-width';
    $variables['global_container'] = ' ';
  }
  else {
    $variables['content_column_class'] = '';
  }

  // Primary nav.
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links.
    $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function.
    $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }

  // Secondary nav.
  $variables['secondary_nav'] = FALSE;
  if ($variables['secondary_menu']) {
    // Build links.
    $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    // Provide default theme wrapper function.
    $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
  }

  $variables['navbar_classes_array'] = array('navbar');

  if (theme_get_setting('bootstrap_navbar_position') !== '') {
    $variables['navbar_classes_array'][] = 'navbar-' . theme_get_setting('bootstrap_navbar_position');
  }
  if (theme_get_setting('bootstrap_navbar_inverse')) {
    $variables['navbar_classes_array'][] = 'navbar-inverse';
  }
  else {
    $variables['navbar_classes_array'][] = 'navbar-default';
  }

  $search_form = drupal_get_form('search_form');
  $variables['search_form'] = drupal_render($search_form);
 
  // Show links to translations if on a node.
  $node_view = '';
  $variables['custom_language_switcher'] = '';
  if (isset($node_view['links']['translation'])) {
    $node_view = node_view($variables['node'], $view_mode = 'full', $langcode = NULL);
    $variables['custom_language_switcher'] = $node_view['links']['translation'];
  }
  if ($variables['language']->language == 'en') {
    $variables['tagline'] = variable_get('site_slogan', '');
  }
  else {
    $variables['tagline'] = variable_get('site_name', '') . ': ' . variable_get('site_slogan', '');
  }

  // Add module category graphic to page header for module nodes.
  $variables['module_header_graphic'] = '';
  if (isset($variables['node']->field_module_category)) {
    $module_category = field_view_field('node', $variables['node'], 'field_module_category');
    if (isset($module_category[0]['#options']['entity']->tid)) {
      $term = taxonomy_term_load($module_category[0]['#options']['entity']->tid);
      $module_graphic = field_view_field('taxonomy_term', $term, 'field_module_graphic', 'default');

      $variables['module_header_graphic'] = $module_graphic;
    }
  }
  $variables['feedback'] = t('Feedback');
}

/**
 * Implements hook_process_page().
 *
 * @see page.tpl.php
 */
function ssd_process_page(&$variables) {
  $variables['navbar_classes'] = implode(' ', $variables['navbar_classes_array']);
}

function ssd_block_list_alter(&$blocks) {
 // dpm($blocks);
}

/**
 * Implements hook_preprocess_region().
 */
function ssd_preprocess_region(&$variables) {
  global $theme;
  static $wells;
  if (!isset($wells)) {
    foreach (system_region_list($theme) as $name => $title) {
      $wells[$name] = theme_get_setting('bootstrap_region_well-' . $name);
    }
  }

  switch ($variables['region']) {
    // @todo is this actually used properly?
    case 'content':
      $variables['theme_hook_suggestions'][] = 'region__no_wrapper';
      break;

    case 'help':
     // $variables['content'] = _bootstrap_icon('question-sign') . $variables['content'];
      $variables['classes_array'][] = 'alert';
      $variables['classes_array'][] = 'alert-info';
      break;
  }
  if (!empty($wells[$variables['region']])) {
    $variables['classes_array'][] = $wells[$variables['region']];
  }
}

/**
 * Overrides theme_menu_link().
 */
function ssd_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#title'] .= ' <span class="caret"></span>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements hook_preprocess_field()
 */
 
function ssd_preprocess_field(&$variables) {
  $element = $variables['element'];
  if ($element['#field_name'] == 'field_updated') {
    $variables['classes_array'][] = 'container';
  }
}

/**
 * Overrides theme_menu_local_task().
 */
function ssd_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];
  $classes = array();

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));

    $classes[] = 'active';
  }

  return '<li class="' . implode(' ', $classes) . '">' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Overrides theme_menu_local_tasks().
 */
function ssd_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="tabs--primary nav nav-tabs">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }

  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs--secondary pagination pagination-sm">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}
  
/**
 * Overrides theme_menu_tree().
 */
function ssd_menu_tree(&$variables) {
  return '<ul class="menu nav">' . $variables['tree'] . '</ul>';
}

/**
 * mirabot_ssd theme wrapper function for the primary menu links.
 */
function ssd_menu_tree__primary(&$variables) {
  return '<ul class="menu nav navbar-nav nav-primary">' . $variables['tree'] . '</ul>';
}

/**
 * mirabot_ssd theme wrapper function for the secondary menu links.
 */
function ssd_menu_tree__secondary(&$variables) {
  return '<ul class="menu nav navbar-nav secondary">' . $variables['tree'] . '</ul>';
}


function ssd_glossify_links($vars) {
  global $base_url;
  drupal_add_css(drupal_get_path('module', 'glossify') . '/glossify.css');

  if ($vars['type'] == 'taxonomy') {
    $path = 'taxonomy/term/' . $vars['id'];
  }
  else {
    $path = 'node/' . $vars['id'];
  }

  $tip = decode_entities(strip_tags($vars['tip']));
  $text = check_plain($vars['text']);
  $img_tag = '<img src = "' . $base_url . '/' . drupal_get_path('theme', 'ssd') . '/img/info.png" />';
  $opts = array(
    'language' => $vars['language'],
    'html' => true,
    'attributes' => array(
      'class' => array(
        'glossify-link',
      ),
      'data-title' => $text,
      'title' => $tip,
      'data-placement' => 'top',
      'data-trigger' => 'hover',
      'data-html' => 'true',
      'data-toggle' => 'popover',
      'data-container' => 'body',
      'data-content' => $tip,
    ),
  );
  
  if($vars['tip']) {
    return l($text . $img_tag, $path, $opts);
  }
  else {
    return l($text . $img_tag, $path, array('language' => $vars['language'], 'html' => true, 'attributes' => array ('class' => array('glossify-link'))));
  }
}

/**
* Process variables for search-result.tpl.php.
*/
function ssd_preprocess_search_result(&$variables) {
  // Remove user name from search results.
  unset($variables['info_split']['user']);
  $variables['info'] = implode(' - ', $variables['info_split']);
}

function ssd_username_alter(&$name, $account) {
  if ($account->uid && ($user = user_load($account->uid)) && !empty($user->field_full_name[LANGUAGE_NONE][0]['value'])) {
    $name = $user->field_full_name[LANGUAGE_NONE][0]['value'];
  }
}

/**
 * Preprocess variables for librejs-inline-license.tpl.php
 */
function ssd_preprocess_librejs_inline_license(&$variables) {
  $variables['author'] = t('Electronic Frontier Foundation');
}
