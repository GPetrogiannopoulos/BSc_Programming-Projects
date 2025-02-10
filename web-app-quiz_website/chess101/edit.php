<?php
    session_start();
    include("connect.php");

    $firstname = $_POST['firstname'];
    $lastname = $_POST['lastname'];
    $dob = $_POST['dob'];
    $gender = $_POST['gender'];
    $username = $_SESSION["username"];
    $password = $_POST['password'];
    $confirm_password = $_POST['confirm-password'];
    $email = $_POST['email'];

    if($password === $confirm_password){
        if(!empty($firstname)){
            $sql = "UPDATE users SET firstname='$firstname' where username='$username' ";
            $output = mysqli_query($conn,$sql);
        }
        if(!empty($lastname)){
            $sql = "UPDATE users SET lastname='$lastname' where username='$username'";
            $output = mysqli_query($conn,$sql);
        }
        if(!empty($dob)){
            $sql = "UPDATE users SET dob='$dob' where username='$username'";
            $output = mysqli_query($conn,$sql);
        }
        if(!empty($gender)){
            $sql = "UPDATE users SET gender='$gender' where username='$username'";
            $output = mysqli_query($conn,$sql);
        }
        if(!empty($password)){
            $sql = "UPDATE users SET password='$password' where username='$username'";
            $output = mysqli_query($conn,$sql);
        }
        if(!empty($email)){
            $sql = "UPDATE users SET email='$email' where username='$username'";
            $output = mysqli_query($conn,$sql);
        }
        if(!empty($_FILES["photo"]["name"])){
            $path = "Pictures/";
            $path .= $username;
            $path .= $_FILES["photo"]["name"];
            $filename = $_FILES["photo"]["tmp_name"];
            $sql = "UPDATE users SET photo='$path' where username='$username'";
            $output = mysqli_query($conn,$sql);
            move_uploaded_file($filename, $path);
        }

        //move_uploaded_file($filename, $path);
        header("location: profile.php");  // after a succesfull edit , prompt the user to the profile page 
    }else{
        echo "<script type='text/javascript'>
            alert('passwords dont match , try again');
        </script>";
    }
?>