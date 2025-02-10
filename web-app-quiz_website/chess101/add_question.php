<?php
    session_start();
    include("connect.php");
   
    $question="";
    $type="";
    $level="";
    $option1="";
    $option2="";
    $option3="";
    $option4="";
    $answers="";

        if(isset($_POST["add_question"])){
            $question =$_POST["add_question"];
        }
        if(isset($_POST["type"])){
            $type =$_POST["type"];
        }
        if(isset($_POST["level"])){
            $level =$_POST["level"];
        }
        if(isset($_POST["option1"])){
            $option1 =$_POST["option1"];
            $option1=str_replace(' ', '_', $option1);
            
        }
        if(isset($_POST["option2"])){
            $option2 =$_POST["option2"];
            $option2=str_replace(' ', '_', $option2);
            
        }
        if(isset($_POST["option3"])){
            $option3 =$_POST["option3"];
            $option3=str_replace(' ', '_', $option3);
            
        }
        if(isset($_POST["option4"])){
            $option4 =$_POST["option4"];
            $option4=str_replace(' ', '_', $option4);
            
        }
        if(isset($_POST["add_answers"])){
            $answers =$_POST["add_answers"];
            $answers=str_replace(' ', '_', $answers);
            
        }
        
        $sql = "insert into question_pool (question,level,type,opt1,opt2,opt3,opt4,answer,approved) values ('$question','$level','$type','$option1','$option2','$option3','$option4','$answers','0')";
        $output = mysqli_query($conn,$sql);
        // question_pool -> approved is 0 because it has not been approved by a moderator
        echo "<script type='text/javascript'>
        alert('question request sent!');
        window.location.replace('add_question.html');
        </script>";
?>




