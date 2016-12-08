Raven Sentry client for Drupal
==============================

[![Build Status](https://travis-ci.org/mfb/raven.svg?branch=7.x-1.x)](https://travis-ci.org/mfb/raven)

Raven module integrates the
[Sentry-php](https://github.com/getsentry/sentry-php) and
[Raven.js](https://github.com/getsentry/raven-js) clients for
[Sentry](https://getsentry.com/) into Drupal.

[Sentry](https://getsentry.com/) is a realtime event logging and
aggregation platform. It specializes in monitoring errors and extracting
all the information needed to do a proper post-mortem without
any of the hassle of the standard user feedback loop.


## Features

This module logs errors in a few ways:

* Register error handler for uncaught exceptions
* Register error handler for PHP errors
* Register error handler for fatal errors
* Handle watchdog messages
* Handle JavaScript exceptions via Raven.js.

You can choose which errors you want to catch by enabling
desired error handlers and selecting error levels.


## Installation for Drupal 7

Download and install the [Libraries API 2](http://drupal.org/project/libraries)
module, [X Autoload 5](http://drupal.org/project/xautoload) module, and the
Raven module as normal. Then download the
[Sentry-php client library](https://github.com/getsentry/sentry-php/releases),
[Monolog](https://github.com/Seldaek/monolog/releases), and
[PSR Log](https://github.com/php-fig/log/releases).

Unpack and rename the Sentry library directory to `sentry-php` and
place it inside the `sites/all/libraries` directory.
Make sure the path to the library files
becomes like this: `sites/all/libraries/sentry-php/lib/Raven/Client.php`.

Likewise rename the PSR Log library directory to `log` and the Monolog
library directory to `monolog`.

Optionally download [Raven.js](https://github.com/getsentry/raven-js/releases),
unpack and place inside the `sites/all/libraries` directory, renaming the
directory to `raven-js`.


## Dependencies

* The [Sentry-php client library](https://github.com/getsentry/sentry-php)
installed in `sites/all/libraries`
* The [Monolog library](https://github.com/Seldaek/monolog)
installed in `sites/all/libraries`
* The [PSR Log library](https://github.com/php-fig/log)
installed in `sites/all/libraries`
* [Libraries API 2](http://drupal.org/project/libraries)
* [X Autoload 5](http://drupal.org/project/xautoload)
* Optional: [Raven.js](https://github.com/getsentry/raven-js)
installed in `sites/all/libraries`


## Information for developers

You can attach an extra information to error reports (logged in user details,
modules versions, etc). See `raven.api.php` for examples.


## Sponsors

This project was originally sponsored by [Seenta](http://seenta.ru/) and is
now sponsored by [EFF](https://www.eff.org/).
