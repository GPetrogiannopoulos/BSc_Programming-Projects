<?php
    session_start();
    include("connect.php");

    $question_id = $_COOKIE['questionid']; 

    $sql = "UPDATE question_pool SET approved='1' where question_id='$question_id'; ";
    $output = mysqli_query($conn,$sql);

    header("Location: modspage.html");
?>