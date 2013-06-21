<?php

function db_result_assoc($result) {
  if ($result && mysql_num_rows($result) > 0) {
    // The mysql_fetch_row function has an optional second parameter $row
    // but that can't be used for compatibility with Oracle, DB2, etc.
    $array = mysql_fetch_assoc($result);
    return $array;
  }
  return FALSE;
}

/**
 * Determine how many result rows were found by the preceding query.
 *
 * @param $result
 *   A database query result resource, as returned from db_query().
 * @return
 *   The number of result rows.
 */
function db_num_rows($result) {
  if ($result) {
    return mysql_num_rows($result);
  }
}

?>