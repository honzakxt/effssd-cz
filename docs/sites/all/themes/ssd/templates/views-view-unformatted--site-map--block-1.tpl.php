<?php
/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
global $base_path;
?>
<h3>
  <img src="<?php print $base_path . $directory; ?>/img/play-c-index.png" /> <br />
  <?php print t("Playlists"); ?>
</h3>
<?php foreach ($rows as $id => $row): ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>