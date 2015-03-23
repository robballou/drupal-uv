<?php
/**
 * Base display
 */
abstract class UVDisplay {
  /**
   * Constuctor
   *
   * @param object $uv
   *   The parent UV object.
   * @param array $options
   *   Display options.
   */
  public function __construct($uv, array $options = array()) {
    $this->uv = $uv;
    $this->options = $options;

    return $this;
  }

  /**
   * Add an item to the display
   *
   * @param string $key
   *   The value within the result to display.
   * @param string $header
   *   The header value.
   * @param array $options
   *   An array of options.
   */
  public function addItem($key, $header, $options = array()) {
    $item = array(
      'result_key' => $key,
      'header' => $header,
      'options' => $options,
    );
    if (!isset($this->options['items'])) {
      $this->options['items'] = array();
    }
    $this->options['items'][] = $item;

    return $this;
  }

  public function format($value, $column) {
    if (isset($column['options'], $column['options']['formatter'])) {
      if (is_callable($column['options']['formatter'])) {
        $args = array();
        if (isset($column['options']['formatter_args'])) {
          $args = $column['options']['formatter_args'];
        }
        array_unshift($args, $value);
        $value = call_user_func_array($column['options']['formatter'], $args);
      }
    }
    return $value;
  }

  /**
   * Generate the renderable array to return.
   */
  abstract public function generate();

  /**
   * Set default values.
   */
  public function setDefaults() {
    foreach ($this->defaults as $key => $default) {
      if (!isset($this->options[$key])) {
        $this->options[$key][$default];
      }
    }
  }
}
