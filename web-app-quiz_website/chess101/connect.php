<?php
    $dbhost = "localhost";
    $dbusername = "root";
    $dbpassword = "";
    $dbname = "chess101";

    if (!$conn = mysqli_connect($dbhost, $dbusername, $dbpassword, $dbname)) {
        die("Connection failed.");
    }
?>