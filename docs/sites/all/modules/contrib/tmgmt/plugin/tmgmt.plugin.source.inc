<?php

/**
 * @file
 * Contains the abstract source base plugin class.
 */

/**
 * Default controller class for source plugins.
 *
 * @ingroup tmgmt_source
 */
abstract class TMGMTDefaultSourcePluginController extends TMGMTPluginBase implements TMGMTSourcePluginControllerInterface {

  /**
   * {@inheritdoc}
   */
  public function getExistingTranslationData(TMGMTJobItem $job_item) {
    $data = array();
    foreach (tmgmt_flatten_data($this->getData($job_item)) as $key => $value) {
      if (isset($value['#translation']['#text'])) {
        $data[$key]['#text'] = $value['#translation']['#text'];
      }
    }
    return tmgmt_unflatten_data($data);
  }

  /**
   * {@inheritdoc}
   */
  public function getLabel(TMGMTJobItem $job_item) {
    return t('@plugin item unavailable (@item)', array('@plugin' => $this->pluginInfo['label'], '@item' => $job_item->item_type . ':' . $job_item->item_id));
  }

  /**
   * {@inheritdoc}
   */
  public function getUri(TMGMTJobItem $job_item) {
    return array(
      'path' => '',
      'options' => array(),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function getItemTypes() {
    return isset($this->pluginInfo['item types']) ? $this->pluginInfo['item types'] : array();
  }

  /**
   * {@inheritdoc}
   */
  public function getItemTypeLabel($type) {
    $types = $this->getItemTypes();
    if (isset($types[$type])) {
      return $types[$type];
    }
    return '';
  }

  /**
   * {@inheritdoc}
   */
  public function getType(TMGMTJobItem $job_item) {
    return ucfirst($job_item->item_type);
  }

  /**
   * {@inheritdoc}
   */
  public function getExistingLangCodes(TMGMTJobItem $job_item) {
    return array();
  }

}
