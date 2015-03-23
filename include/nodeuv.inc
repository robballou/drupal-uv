<?php
/**
 * NodeUV
 */

/**
 * Query and display nodes
 */
class NodeUV extends UV {
  /**
   * Constructor
   */
  public function __construct($bundle = NULL) {
    parent::__construct();

    $this->query->entityCondition('entity_type', 'node');
    if ($bundle) {
      $this->setBundle($bundle);
    }
    return $this;
  }

  /**
   * Set the bundle for this query
   */
  public function setBundle($bundle) {
    $this->query->entityCondition('bundle', $bundle);
    return $this;
  }

  /**
   * Show published/unpublished content
   */
  public function published($status = TRUE) {
    $status = $status ? 1 : 0;
    $this->query->propertyCondition('status', $status);
    return $this;
  }

  /**
   * Show content created by a specific user
   */
  public function user($uid = NULL) {
    global $user;
    if (!$uid) {
      if (!is_object($uid)) {
        $uid = $user->uid;
      }
      elseif (is_object($uid) && isset($uid->uid)) {
        $uid = $uid->uid;
      }
    }

    if ($uid) {
      $this->query->propertyCondition('uid', $uid);
    }
    return $this;
  }

  /**
   * Sort by the created date, newest first
   *
   * @param string $direction
   *   Defaults to DESC.
   */
  public function sortByCreated($direction = 'DESC') {
    $this->query->propertyOrderBy('created', $direction);
    return $this;
  }

  /**
   * Sort by node title
   */
  public function sortByTitle($direction = 'ASC') {
    $this->query->propertyOrderBy('title', $direction);
    return $this;
  }

  /**
   * Sort by the updated date, most recent first
   *
   * @param string $direction
   *   Defaults to DESC.
   */
  public function sortByUpdated($direction = 'DESC') {
    $this->query->propertyOrderBy('updated', $direction);
    return $this;
  }
}
