<?php
    session_start();
    include("connect.php");

    $firstname = $_POST['firstname'];
    $lastname = $_POST['lastname'];
    $dob = $_POST['dob'];
    $gender = $_POST['gender'];
    $username = $_POST['username'];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm-password'];
    $email = $_POST['email'];
    
    $path = "Pictures/";
    $path .= $username;
    $path .= $_FILES["photo"]["name"];
    $filename = $_FILES["photo"]["tmp_name"];
   
    if (isset($_FILES['photo']['error']) !== UPLOAD_ERR_OK) {
        echo ("Upload failed with error code " . isset($_FILES['photo']['error']));
    }

    // check whether a user with the same email exists
    $sql = "select * from users where email = '$email' limit 1;";    
    $check_mail = mysqli_query($conn, $sql);
     // check whether a user with the same username exists
    $sql = "select * from users where username = '$username' limit 1;";    
    $check_user = mysqli_query($conn, $sql);

    if (mysqli_num_rows($check_mail) == 0) { // a user with the same email address does not exist
        if((mysqli_num_rows($check_user) == 0)){
            if($password === $confirm_password){
                $sql = "insert into users (firstname,lastname,dob,gender,username,password,email,photo,role) values ('$firstname','$lastname','$dob','$gender','$username','$password','$email','$path','user')";
                $output = mysqli_query($conn,$sql);
                move_uploaded_file($filename, $path);
                header("location: index.html");  // after a succesfull sign up , prompt the user to the login screen 
                $_SESSION["logged"] = "false";
            }else{
                echo "<script type='text/javascript'>
                    alert('passwords dont match , try again');
                </script>";
            }
        }else{
            echo "<script type='text/javascript'>
                alert('this username already exists');
            </script>";
        }
    }else{
        echo "<script type='text/javascript'>
            alert('this email already exists');
        </script>";
    }
?>