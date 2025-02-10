<?php
    session_start();
    include("connect.php");

    $question_id = $_COOKIE['questionid']; 

    $sql = "DELETE FROM question_pool where question_id='$question_id'; ";
    $output = mysqli_query($conn,$sql);

    header("Location: modspage.html");
?>