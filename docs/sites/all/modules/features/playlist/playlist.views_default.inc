<?php
/**
 * @file
 * playlist.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function playlist_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'front_page_playlists';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Front page playlists';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'container';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'slideshow';
  $handler->display->display_options['style_options']['slideshow_type'] = 'flexslider_views_slideshow';
  $handler->display->display_options['style_options']['slideshow_skin'] = 'default';
  $handler->display->display_options['style_options']['skin_info'] = array(
    'class' => 'default',
    'name' => 'Default',
    'module' => 'views_slideshow',
    'path' => '',
    'stylesheets' => array(),
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_playlist_banner_bg' => 0,
    'field_playlist_banner_title' => 0,
    'field_playlist_banner_subtitle' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['hide_on_single_slide'] = 1;
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_playlist_banner_bg' => 0,
    'field_playlist_banner_title' => 0,
    'field_playlist_banner_subtitle' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Front page banner background */
  $handler->display->display_options['fields']['field_playlist_banner_bg']['id'] = 'field_playlist_banner_bg';
  $handler->display->display_options['fields']['field_playlist_banner_bg']['table'] = 'field_data_field_playlist_banner_bg';
  $handler->display->display_options['fields']['field_playlist_banner_bg']['field'] = 'field_playlist_banner_bg';
  $handler->display->display_options['fields']['field_playlist_banner_bg']['label'] = '';
  $handler->display->display_options['fields']['field_playlist_banner_bg']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_playlist_banner_bg']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_playlist_banner_bg']['settings'] = array(
    'image_style' => 'full-width',
    'image_link' => 'content',
  );
  /* Field: Content: Front banner title */
  $handler->display->display_options['fields']['field_playlist_banner_title']['id'] = 'field_playlist_banner_title';
  $handler->display->display_options['fields']['field_playlist_banner_title']['table'] = 'field_data_field_playlist_banner_title';
  $handler->display->display_options['fields']['field_playlist_banner_title']['field'] = 'field_playlist_banner_title';
  $handler->display->display_options['fields']['field_playlist_banner_title']['label'] = '';
  $handler->display->display_options['fields']['field_playlist_banner_title']['element_label_type'] = 'h1';
  $handler->display->display_options['fields']['field_playlist_banner_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_playlist_banner_title']['type'] = 'title_linked';
  $handler->display->display_options['fields']['field_playlist_banner_title']['settings'] = array(
    'title_style' => 'h1',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Field: Content: Front banner subtitle */
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['id'] = 'field_playlist_banner_subtitle';
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['table'] = 'field_data_field_playlist_banner_subtitle';
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['field'] = 'field_playlist_banner_subtitle';
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['label'] = '';
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['element_type'] = 'h2';
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['type'] = 'title_linked';
  $handler->display->display_options['fields']['field_playlist_banner_subtitle']['settings'] = array(
    'title_style' => 'h2',
    'title_link' => 'content',
    'title_class' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'playlist' => 'playlist',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'front-page-playlists';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['block_caching'] = '4';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Tips, Tools and How-tos for Safer Online Communications';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['row_options']['item_length'] = 'rss';
  $handler->display->display_options['path'] = 'playlist.xml';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'block' => 'block',
    'default' => 0,
  );
  $handler->display->display_options['sitename_title'] = 1;
  $translatables['front_page_playlists'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Page'),
    t('Block'),
    t('Feed'),
  );
  $export['front_page_playlists'] = $view;

  return $export;
}
