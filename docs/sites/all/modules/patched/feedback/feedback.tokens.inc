<?php

/**
 * @file
 * Builds placeholder replacement tokens for feedback-related data.
 */

/**
 * Implements hook_token_info().
 */
function feedback_token_info() {
  $types = array(
    'feedback' => array(
      'name' => t('Feedback'),
      'description' => t('Tokens for feedback posted on the site.'),
      'needs-data' => 'feedback',
    ),
  );

  $tokens = array(
    'feedback' => array(
      'url' => array(
        'name' => t("URL"),
        'description' => t("The URL where feedback was submitted."),
      ),
      'useragent' => array(
        'name' => t("User agent"),
        'description' => t("The user agent string."),
      ),
      'message' => array(
        'name' => t("Message"),
        'description' => t("The message submitted."),
      ),
    ),
  );

  return array(
    'types' => $types,
    'tokens' => $tokens,
  );
}

/**
 * Implements hook_tokens().
 */
function feedback_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
  }
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'feedback' && !empty($data['feedback'])) {
    $feedback = $data['feedback'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'uid':
          $replacements[$original] = $feedback->uid;
          break;

        case 'url':
          $replacements[$original] = url($feedback->url, $url_options);
          break;

        case 'useragent':
          $replacements[$original] = $feedback->useragent;
          break;

        case 'message':
          $replacements[$original] = $sanitize ? check_plain($feedback->message) : $feedback->message;
          break;

        // Default values for the chained tokens handled below.
        case 'author':
          if ($feedback->uid == 0) {
            $name = variable_get('anonymous', t('Anonymous'));
          }
          else {
            $account = user_load($feedback->uid == 0);
            $name = $account->name;
          }
          $replacements[$original] = $sanitize ? filter_xss($name) : $name;
          break;
      }
    }

    if ($author_tokens = token_find_with_prefix($tokens, 'author')) {
      $author = user_load($feedback->uid);
      $replacements += token_generate('user', $author_tokens, array('user' => $author), $options);
    }
  }

  return $replacements;
}
