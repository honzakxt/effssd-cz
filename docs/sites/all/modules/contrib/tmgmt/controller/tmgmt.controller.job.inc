<?php

/**
 * @file
 * Contains the job entity controller class.
 */

/**
 * Controller class for the job entity.
 *
 * @ingroup tmgmt_job
 */
class TMGMTJobController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    /* @var $entity TMGMTJob */
    /* @var $unchanged_entity TMGMTJob */
    $unchanged_entity = $entity->identifier() ? entity_load_unchanged($entity->entityType(), $entity->identifier()) : FALSE;
    $entity->changed = REQUEST_TIME;
    $return = parent::save($entity, $transaction);

    // If the target language was changes, and the job was not processed yet:
    // update all job items. The reason: there already could be existing
    // (outdated) translations for the current source; they should be reloaded
    // to match new target language.
    if ($unchanged_entity && $entity->state == TMGMT_JOB_STATE_UNPROCESSED
      && !empty($entity->target_language)
      && $entity->target_language != $unchanged_entity->target_language) {
      foreach ($entity->getItems() as $job_item) {
        // Clear job data and call TMGMTJobItem::getData(). This will resave the
        // job item.
        $job_item->data = array();
        $job_item->getData();
      }
    }

    return $return;
  }

  /**
   * {@inheritdoc}
   */
  public function delete($ids, $transaction = NULL) {
    parent::delete($ids, $transaction);
    // Since we are deleting one or multiple jobs here we also need to delete
    // the attached job items and messages.
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'tmgmt_job_item')
      ->propertyCondition('tjid', $ids)
      ->execute();
    if (!empty($result['tmgmt_job_item'])) {
      $controller = entity_get_controller('tmgmt_job_item');
      // We need to directly query the entity controller so we can pass on
      // the transaction object.
      $controller->delete(array_keys($result['tmgmt_job_item']), $transaction);
    }
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'tmgmt_message')
      ->propertyCondition('tjid', $ids)
      ->execute();
    if (!empty($result['tmgmt_message'])) {
      $controller = entity_get_controller('tmgmt_message');
      // We need to directly query the entity controller so we can pass on
      // the transaction object.
      $controller->delete(array_keys($result['tmgmt_message']), $transaction);
    }
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'tmgmt_remote')
      ->propertyCondition('tjid', $ids)
      ->execute();
    if (!empty($result['tmgmt_remote'])) {
      $controller = entity_get_controller('tmgmt_remote');
      $controller->delete(array_keys($result['tmgmt_remote']), $transaction);
    }
  }

}
