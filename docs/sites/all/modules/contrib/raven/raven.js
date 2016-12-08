/**
 * @file
 * Configures Raven.js with the public DSN, options and context.
 */

(function () {

  "use strict";

  Raven.config(Drupal.settings.raven.dsn, Drupal.settings.raven.options).install();
  Raven.setUserContext(Drupal.settings.raven.user);

})();
