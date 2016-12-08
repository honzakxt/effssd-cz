<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <?php print $title; ?>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <div<?php if ($classes_array[$id]) { print ' id="category-parent-' . $id . '" class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
    <div class="connect-bar">&nbsp;</div>
  </div>
<?php endforeach; ?>
