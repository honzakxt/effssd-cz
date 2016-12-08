<?php

/**
 * Implementation of specially named hook_ctools_content_types()
 */
$plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'no title override' => TRUE,
    'title' => t('Front page links'),
    'description' => t('Front page link to Index'),
    'category' => t('Custom'),
  );

function ssd_library_front_page_links_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = '';  
  $block->content = '<h2>'. l('Index', 'index', array("attributes" => array("class" => "mylink"))) .'</h2>';
  return $block;
}
