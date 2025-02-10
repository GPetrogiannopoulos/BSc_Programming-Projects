<?php
    session_start();
    include("connect.php");

    $question_id = $_COOKIE['questionid'];
   
    $question="";
    $level="";
    $options="";
    $option1="";
    $option2="";
    $option3="";
    $option4="";
    $answers="";

   
    if(isset($_POST["add_question"])){
        $question =$_POST["add_question"];
        $sql = "UPDATE question_pool SET question='$question' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
    }
    if(isset($_POST["level"])){
        $level =$_POST["level"];
        $sql = "UPDATE question_pool SET level='$level' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
    }
    if(isset($_POST["option1"])){
        $option1 =$_POST["option1"];
        $option1=str_replace(' ', '_', $option1);
        $sql = "UPDATE question_pool SET opt1='$option1' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
        
    }
    if(isset($_POST["option2"])){
        $option2 =$_POST["option2"];
        $option2=str_replace(' ', '_', $option2);
        $sql = "UPDATE question_pool SET opt2='$option2' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
        
    }
    if(isset($_POST["option3"])){
        $option3 =$_POST["option3"];
        $option3=str_replace(' ', '_', $option3);
        $sql = "UPDATE question_pool SET opt3='$option3' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
        
    }
    if(isset($_POST["option4"])){
        $option4 =$_POST["option4"];
        $option4=str_replace(' ', '_', $option4);
        $sql = "UPDATE question_pool SET opt4='$option4' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
        
    }
    if(isset($_POST["add_answers"])){
        $answers =$_POST["add_answers"];
        $answers=str_replace(' ', '_', $answers);
        $sql = "UPDATE question_pool SET answer='$answers' where question_id='$question_id'; ";
        $output = mysqli_query($conn,$sql);
        
    }

   
    echo "
    <script type='text/javascript'>
        window.location.replace('modspage.html');
    </script>
    ";
    
?>