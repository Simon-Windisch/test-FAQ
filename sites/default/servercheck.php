<?php
include_once ('settings.php');

$database_status = "OK";
$database_error = "";
$uname = posix_uname();
$host_name = $uname["nodename"] . "." . rand(0, 999);

// Connect
$conn = @mysql_pconnect("$db_server","$db_username","$db_password") or $database_error = "Could not connect";

// Select Database
if (!$database_error) {
        @mysql_select_db($db_name,$conn) or $database_error = "Could not select database";
}

// Update Table
if (!$database_error) {
        $query = "DELETE FROM servercheck WHERE host_name = '" . mysql_escape_string($host_name) . "'";
        @mysql_query($query);
        $query = "INSERT INTO servercheck SET host_name = '" . mysql_escape_string($host_name) . "'";
        @mysql_query($query);
        $query = "SELECT host_name FROM servercheck WHERE host_name = '" . mysql_escape_string($host_name) . "' LIMIT 1";
        $result = @mysql_query($query);
        $row = @mysql_fetch_row($result);
        if (!$row[0]) {
                $database_error = "DELETE, INSERT, SELECT failed";
        }
}

if ($database_error) {
        $database_status = "FAILURE";
}

header("Content-type: text/plain");

echo "WebServer: OK -- static content\n";
echo "MySQLDatabase: ".$database_status." -- ".$database_error.$row[0]."\n";
?>