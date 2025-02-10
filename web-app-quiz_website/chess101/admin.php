<?php
    session_start();
    include("connect.php");
        $username="";
        $username=$_POST["username"];
        $sql = "select * from users where username='$username'";
        $users = mysqli_query($conn,$sql);
        $row = mysqli_fetch_array($users);
        if (mysqli_num_rows($users) == 1) {
            if(isset($_POST["promote"])){

                $userrole = $row["role"];
                if($userrole=="user")
                {
                    $sql = "UPDATE users SET role='moderator' where username='$username' ";
                    $output = mysqli_query($conn,$sql);
                }
            }
            if(isset($_POST["demote"])){
                $userrole = $row["role"];
                if($userrole=="moderator")
                {
                    $sql = "UPDATE users SET role='user' where username='$username' ";
                    $output = mysqli_query($conn,$sql);
                }
            }
            if(isset($_POST["delete"])){
                $sql = "DELETE FROM users WHERE username='$username'; ";
                $output = mysqli_query($conn,$sql);
            }
        }
        echo "<script type='text/javascript'>
        window.location.replace('adminpage.html');
        </script>";

?>

