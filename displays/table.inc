<?php
/**
 * Table display.
 */

/**
 * Display results in a table.
 */
class UVTableDisplay extends UVDisplay {

  public $defaults = array(
    'header' => array(),
    'empty' => '',
  );

  /**
   * Generate the renderable array.
   */
  public function generate() {
    $this->setDefaults();
    $this->handleItems();

    $header = $this->options['header'];

    $rows = array();
    $this->uv->getResults();

    foreach (array_keys($this->uv->results) as $group) {
      $this_group = array_keys($this->uv->results[$group]);
      $load_multiple = $group . '_load_multiple';
      $load = $group . '_load';
      $access = $group . '_access';
      if (function_exists($load_multiple)) {
        $load_multiple($this_group);
      }

      foreach ($this_group as $result_id) {
        if (function_exists($load)) {
          $result = $load($result_id);
        }

        if ($result && function_exists($access)) {
          if (!$access('view', $result)) {
            continue;
          }
        }

        if ($result) {
          $rows[] = call_user_func($this->options['row_builder'], $result);
        }
      }
    }

    return array(
      'uv_display' => array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
        '#attributes' => array(),
        '#capation' => '',
        '#colgroups' => array(),
        '#sticky' => FALSE,
        '#empty' => $options['empty'],
      ),
    );
  }

  /**
   * Parse options.items into something useable for making the row.
   */
  public function handleItems() {
    if (isset($this->options['items']) && !isset($this->options['row_builder'])) {
      $this->options['row_builder'] = array($this, 'rowBuilder');

      $this->setDefaults();
      foreach ($this->options['items'] as $column) {
        if (isset($column['header'])) {
          $this->options['header'][] = $column['header'];
        }
      }
    }
  }

  /**
   * Build the row
   */
  public function rowBuilder($result) {
    $row = array();
    foreach ($this->options['items'] as $column) {
      if (isset($column['result_key'])) {
        $column_key = $column['result_key'];
        if (isset($result->$column_key)) {
          $row[] = $this->format($result->$column_key, $column);
        }
      }
    }
    return $row;
  }
}
