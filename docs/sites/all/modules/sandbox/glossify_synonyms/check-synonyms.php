#!/usr/bin/env drush
$rows = db_query("SELECT field_synonym_value, CONCAT('https://ssd.eff.org/', language, '/taxonomy/term/', entity_id, '/edit') AS url FROM field_data_field_synonym WHERE field_synonym_value IN (SELECT name_field_value FROM field_data_name_field WHERE bundle = 'terms')");
foreach ($rows as $row) {
  echo $row->url, ' ', $row->field_synonym_value, "\n";
}
