<?php
    include("connect.php");
    session_start();
    $_SESSION["logged"] = "false";

    $username=$_POST['username'];
    $password=$_POST['password'];

    $sql = "select * from users where username = '$username' and password ='$password';";
    $find_credentials = mysqli_query($conn,$sql);

    if (mysqli_num_rows($find_credentials) == 1) { 
        $row = mysqli_fetch_assoc($find_credentials);
       
        $_SESSION["username"] = $username;
        $_SESSION["role"] = $row['role'];
        $_SESSION["logged"] = "true";
        
        header("location: profile.php");         
    }
    else {
        echo "wrong username or password";
    }
?>