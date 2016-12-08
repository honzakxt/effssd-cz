<?php
/**
 * @file
 * Contains the administration pages for Raven.
 */

/**
 * Returns supported PHP error levels and their labels.
 *
 * @return array
 *   An array containing supported PHP error levels and their labels.
 */
function raven_get_error_levels() {
  foreach (drupal_error_levels() as $level => $label) {
    $levels[$level] = $label[0];
  }
  return $levels;
}

/**
 * Returns set settings form for Raven.
 *
 * @param array $form
 *   The form definition.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form definition.
 */
function raven_settings_form(array $form, array &$form_state) {
  // Show message if library cannot be loaded.
  _raven_get_client();

  $form['raven_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Raven logging'),
    '#description' => t('Enable logging to send reports to Sentry server.'),
    '#default_value' => variable_get('raven_enabled', FALSE),
  );

  $form['raven_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logging settings'),
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_enabled"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_dsn'] = array(
    '#type' => 'textfield',
    '#title' => t('Sentry DSN'),
    '#description' => t('Sentry DSN credentials for current site.'),
    '#default_value' => variable_get('raven_dsn', ''),
  );

  $form['raven_settings']['raven_connection_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connection settings'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_enabled"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_connection_settings']['raven_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#description' => t('Connection timeout in seconds.'),
    '#default_value' => variable_get('raven_timeout', 2),
  );

  $form['raven_settings']['raven_connection_settings']['raven_ssl'] = array(
    '#type' => 'radios',
    '#title' => t('SSL Verification'),
    '#default_value' => variable_get('raven_ssl', 'verify_ssl'),
    '#options' => array(
      'verify_ssl' => t('Verify SSL'),
      'ca_cert' => t('Verify against a CA certificate'),
      'no_verify_ssl' => t("Don't verify SSL (not recommended)"),
    ),
  );
  $form['raven_settings']['raven_connection_settings']['raven_ca_cert'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to CA certificate'),
    '#default_value' => variable_get('raven_ca_cert', ''),
    '#description' => t('Path to the CA certificate file of the Sentry server specified in the DSN.'),

    // Only visible when 'raven_ssl' set to ca_cert.
    '#states' => array(
      'visible' => array(
        ':input[name=raven_ssl]' => array('value' => 'ca_cert'),
      ),
    ),
  );

  $form['raven_settings']['raven_exception_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable exception handler'),
    '#description' => t('Check to handle uncaught exceptions.'),
    '#default_value' => variable_get('raven_exception_handler', TRUE),
  );

  $form['raven_settings']['raven_fatal_error_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable fatal error handler'),
    '#description' => t('Check to handle fatal PHP errors.'),
    '#default_value' => variable_get('raven_fatal_error_handler', TRUE),
  );

  $form['raven_settings']['raven_fatal_error_handler_memory'] = array(
    '#type' => 'textfield',
    '#title' => t('Reserved memory'),
    '#description' => t('Reserved memory for fatal error handler (KB).'),
    '#default_value' => variable_get('raven_fatal_error_handler_memory', 2.5 * 1024),
    '#size' => 10,
  );

  $form['raven_settings']['raven_js_handler'] = array(
    '#type' => 'fieldset',
    '#title' => t('JavaScript handler'),
  );

  $form['raven_settings']['raven_js_handler']['raven_js_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable JavaScript error handler'),
    '#description' => t('Check to send JavaScript exceptions to Sentry server (if user has the <a target="_blank" href="@url"><em>send JavaScript errors to Sentry</em> permission</a>).', array('@url' => url('admin/people/permissions', array('fragment' => 'module-raven')))),
    '#default_value' => variable_get('raven_js_enabled', FALSE),
  );

  $form['raven_settings']['raven_js_handler']['raven_public_dsn'] = array(
    '#type' => 'textfield',
    '#title' => t('Sentry Public DSN'),
    '#description' => t('Sentry public DSN credentials for current site.'),
    '#default_value' => variable_get('raven_public_dsn', ''),
  );

  $raven_js_library = libraries_load('raven-js');

  $form['raven_settings']['raven_js_handler']['raven_js_source'] = array(
    '#type' => 'radios',
    '#title' => t('Raven.js source'),
    '#options' => drupal_map_assoc(array('library', 'cdn')),
    '#default_value' => variable_get('raven_js_source', 'cdn'),
  );

  $form['raven_settings']['raven_js_handler']['raven_js_source']['library'] = array(
    '#type' => 'radio',
    '#title' => t('Use local Raven.js library'),
    '#return_value' => 'library',
    '#description' => t('Missing, download it to <em>libraries/raven-js</em> from <a target="_blank" rel="noreferrer" href="@url">@url</a>.', array('@url' => $raven_js_library['download url'])),
    '#disabled' => empty($raven_js_library['installed']),
  );

  if ($raven_js_library['installed']) {
    $form['raven_settings']['raven_js_handler']['raven_js_source']['library']['#description'] = t('Version %version installed.', array('%version' => $raven_js_library['version']));
  }

  $form['raven_settings']['raven_js_handler']['raven_js_source']['cdn'] = array(
    '#type' => 'radio',
    '#title' => t('Use Raven.js CDN'),
    '#return_value' => 'cdn',
    '#description' => t('Define URL below.'),
  );

  $form['raven_settings']['raven_js_handler']['raven_js_cdn_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Raven.js CDN URL'),
    '#description' => t('Check latest version at <a target="_blank" rel="noreferrer" href="@url">@url</a>.', array('@url' => 'https://docs.getsentry.com/hosted/clients/javascript/')),
    '#default_value' => variable_get('raven_js_cdn_url', RAVEN_JS_CDN_URL),
  );

  $form['raven_settings']['raven_error_handler'] = array(
    '#type' => 'fieldset',
    '#title' => t('PHP error handler'),
  );

  $form['raven_settings']['raven_error_handler']['raven_error_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable error handler'),
    '#description' => t('Check to handle PHP errors.'),
    '#default_value' => variable_get('raven_error_handler', TRUE),
  );

  $form['raven_settings']['raven_error_handler']['raven_error_levels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Error levels'),
    '#description' => t('Check error levels to handle.'),
    '#default_value' => variable_get('raven_error_levels', array()),
    '#options' => raven_get_error_levels(),
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_error_handler"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_watchdog_handler'] = array(
    '#type' => 'fieldset',
    '#title' => t('Watchdog handler'),
  );

  $form['raven_settings']['raven_watchdog_handler']['raven_watchdog_handler'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable watchdog handler'),
    '#description' => t('Check to handle watchdog messages (except PHP and page-not-found errors).'),
    '#default_value' => variable_get('raven_watchdog_handler', FALSE),
  );

  $form['raven_settings']['raven_watchdog_handler']['raven_watchdog_page_not_found'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable page-not-found watchdog handler'),
    '#description' => t('Check to handle page-not-found watchdog messages.'),
    '#default_value' => variable_get('raven_watchdog_page_not_found', FALSE),
  );

  $_watchdog_levels = watchdog_severity_levels();
  $watchdog_levels = array();
  foreach ($_watchdog_levels as $level => $label) {
    $watchdog_levels[$level + 1] = $label;
  }
  $form['raven_settings']['raven_watchdog_handler']['raven_watchdog_levels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Message levels'),
    '#description' => t('Check message levels to handle.'),
    '#default_value' => variable_get('raven_watchdog_levels', array()),
    '#options' => $watchdog_levels,
    '#states' => array(
      'disabled' => array(
        ':input[name="raven_watchdog_handler"]' => array('unchecked' => TRUE),
      ),
    ),
  );

  $form['raven_settings']['raven_stack'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable stacktraces'),
    '#description' => t('Enable it to add stacktraces to reports.'),
    '#default_value' => variable_get('raven_stack', TRUE),
  );

  $form['raven_settings']['raven_trace'] = array(
    '#type' => 'checkbox',
    '#title' => t('Reflection tracing in stacktraces'),
    '#description' => t('Check this to enable reflection tracing (function calling arguments) in stacktraces. Warning: This setting allows sensitive data to be logged by Sentry!'),
    '#default_value' => variable_get('raven_trace', FALSE),
  );

  $form['raven_settings']['raven_trace_user'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable reflection tracing for user watchdog messages'),
    '#description' => t('Check this to enable reflection tracing of user watchdog messages. This is disabled by default to avoid logging user passwords.'),
    '#default_value' => variable_get('raven_trace_user', FALSE),
  );

  return system_settings_form($form);
}
