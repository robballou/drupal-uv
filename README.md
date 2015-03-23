# UV (UnViews)

Goal: To make a coder-friendly Views alternative. Essentially provide a query
object and pass it to a display.

```php
$unview = new NodeUV('blog_post');
$unview
  ->published(FALSE)
  ->user($user->uid)
  ->sortByCreated();

if ($unview->hasResults()) {
  return $unview->display('table')
    ->addItem('title', 'Request')
    ->addItem('created', 'Created', array(
      'formatter' => 'format_date',
      'formatter_args' => array('short'),
    ))
    ->generate();
}
```

Currently works with EntityFieldQueries, but I would like to get this working
with other query objects. Also need more time getting displays working.
