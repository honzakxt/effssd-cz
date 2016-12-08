<?php
/**
 * @file
 * ssd_library.entityqueue_default.inc
 */

/**
 * Implements hook_entityqueue_default_queues().
 */
function ssd_library_entityqueue_default_queues() {
  $export = array();

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'ssd_site_map_playlists';
  $queue->label = 'Site Map: Playlists';
  $queue->language = 'en';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'playlist' => 'playlist',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 1,
  );
  $export['ssd_site_map_playlists'] = $queue;

  return $export;
}
