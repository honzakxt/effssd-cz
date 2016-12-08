<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<div class="page-wrapper">
<header id="navbar" role="banner" class="navbar">
  <div class="container">
    <!-- EFF Header -->
    <div id="top-eff-header">
      <a href="https://www.eff.org/">
        <img src="<?php print $eff_logo_small; ?>" alt="EFF" />
        <?php print t("A Project of the Electronic Frontier Foundation"); ?>
      </a>
    </div>

    <div class="search-form-header">
      <?php print $search_form; ?>
    </div>
    
    <?php if (!empty($page['language_switcher'])): ?>
    <div id="language-switcher" class="">
      <button type="button" class="menu-hamburger" data-toggle="collapse" data-target=".language-switcher-collapse">
        <?php print t('Language'); ?>
      </button> 
      <?php print render($page['language_switcher']); ?>
     </div>
    <?php endif; ?>

    <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
    <button type="button" class="menu-hamburger" data-toggle="collapse" data-target=".navbar-collapse">
      <?php print t('Menu'); ?>
    </button>
  </div> 
</header>
<header id="nav-expanded">
  <div class="container">
    <div class="row">
      <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
        <div class="navbar-collapse collapse">
          <nav role="navigation">
            <?php if (!empty($primary_nav)): ?>
              <?php print render($primary_nav); ?>
            <?php endif; ?>
            <?php if (!empty($secondary_nav)): ?>
              <?php print render($secondary_nav); ?>
            <?php endif; ?>
            <?php if (!empty($page['navigation'])): ?>
              <?php print render($page['navigation']); ?>
            <?php endif; ?>
          </nav>
        </div>
      <?php endif; ?>
    </div>
   </div>
</header>
<header role="banner" id="page-header" class="container">

  <?php if ($logo): ?>
    <div id ="top-logo">
      <div id="top-logo-inner">
        <a class="logo" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="img-responsive" />
        </a>
      </div>
    </div>
  <?php endif; ?>
  
  <?php if ($is_front): ?>
    <p class="lead slogan"><?php print $tagline; ?></p>
  <?php endif; ?>

  <?php print render($page['header']); ?>

  <?php if (!empty($tabs)): ?>
    <?php print render($tabs); ?>
  <?php endif; ?>

</header> <!-- /#page-header -->

<?php if (isset($node)): ?>
  <div class="container-main clearfix">
<?php endif; ?>
  
  <div class="<?php print $global_container; ?> ">

    <?php if (!empty($page['sidebar_first'])): ?>
      <aside class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

    <section class="container-full-width">
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <a id="main-content"></a>
      <?php if ($playlist_graphic): ?>
        <div class="header-graphic">
          <?php print $playlist_graphic; ?>
        </div>
      <?php else: ?>
        <?php if ($module_header_graphic): ?>
          <div class="header-graphic">
            <?php print render($module_header_graphic); ?>
          </div>
        <?php endif; ?>
      <?php endif; ?>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title) && !$is_playlist): ?>

        <?php if (!$global_container): ?>
          <div class="container">
        <?php endif; ?>

        <h1 class="page-header"><?php print $title; ?></h1>

        <?php if (!$global_container): ?>
          </div>
        <?php endif; ?>

      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($page['help'])): ?>
        <?php print render($page['help']); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
    </section>

    <?php if (!empty($page['sidebar_second'])): ?>
      <aside class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>
  </div>
<?php if (isset($node)): ?>
  </div> <!-- /.container-main -->
<?php endif; ?>

</div>

<footer class="footer clearfix">
  <div class="container">
    <div id="eff-footer">
      <a href="https://www.eff.org/">
        <img src="<?php print $eff_logo_small; ?>" alt="EFF" />
        <?php print t("A Project of the Electronic Frontier Foundation"); ?>
      </a>
    </div>
    <?php print render($page['footer']); ?>
    <?php if (menu_get_object()): ?>
      <span id="feedback-button" class="feedback-link"><?php print $feedback; ?></span>
    <?php endif; ?>
    <a href="https://www.eff.org/copyright"><img src="<?php print $base_path . $directory; ?>/img/cc-by-logo.png" alt="Creative Commons" width="60px" /></a>
  </div>
</footer>
