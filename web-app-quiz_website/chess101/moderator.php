<?php
    session_start();
    include("connect.php");

    $selected_question_id = $_COOKIE['questionid']; 

?>

<!doctype html>

<html lang="en">
    
  <head>
  	<title>Moderator</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

	<link href="https://fonts.googleapis.com/css?family=Lato:300,400,700&display=swap" rel="stylesheet">

	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
	
	<link rel="stylesheet" href="css/style.css">

	</head>

	<body>  
        <div class="topnav"> 
            <a href="index.html">Home</a>
            <a href="basics.html" >basics</a>
            <a href="more.html">more</a>
            <a href="login.html">login</a>  
            <a href="signup.html">sign up</a>      
            <a href="quiz.php">quiz</a> 
            <a href="profile.php">Profile</a>
            <a href="adminpage.php">Admin</a>
            <a class="active" href="modspage.html">Moderator</a>
            		  
        </div>
           
		<div class="container"> 
            <div class="row justify-content-center">
                    
            <?php
                    $sql = "select * from question_pool where question_id='$selected_question_id';";
                    $questions = mysqli_query($conn,$sql);
                    $i=0;
                    while($row = mysqli_fetch_array($questions)){
                ?>
            
                <div class="col-md-7 col-lg-4">
                    <div class="login-wrap p-4 p-md-3 ">
                        <div class="row justify-content-center align-items-center">
                            <h3 class="text-center mb-4"><b>Question: <?php echo $i; ?></h3></b></h3>
                        </div>
                        <div class="<?php echo $row['question_id']; ?>" onclick = "get_question_id(this.className)" >

                                    <li>Question:<br>
                                    <?php echo $row["question"]; ?><br>
                                    <li>Level:&nbsp&nbsp
                                    <?php echo $row["level"]; ?><br>
                                    <li>Type:&nbsp&nbsp 
                                    <?php echo $row["type"]; ?><br>
                                    <li>Options:<br>
                                    <?php echo $row["opt1"]; ?><br>
                                    <?php echo $row["opt2"]; ?><br>
                                    <?php echo $row["opt3"]; ?><br>
                                    <?php echo $row["opt4"]; ?><br>
                                    <li>Answer:<br>
                                    <?php echo $row["answer"]; ?><br>
                                    <li>Approved:
                                    <?php echo $row["approved"]; ?><br>
                                    <p hidden id="question-id" value="<?php echo $row['question_id']; ?>"> <?php echo $row['question_id']; ?></p>
                        </div>                       
                    </div>       
                </div>
           

                    <div class="col-md-7 col-lg-8">
                        <div class="login-wrap p-4 p-md-3">
                            <div class="align-items-center justify-content-center">
                                <h3 class="text-center mb-4"><b>Edit question</h3></b></h3>
                                    <b>Question:</b><br>
                                    
                                    <form action="edit-question.php" method="post">
                                        <div class="form-group">
                                            <textarea style="width:100%" name="add_question" maxlength="249" placeholder="type question....."></textarea>
                                            
                                            <br><b>Level:</b><br> 
                                            <input type="radio" id="add_single" name="level" value="easy"> Easy <br>
                                            <input type="radio" id="add_multiple" name="level" value="medium"> Medium <br>
                                            <input type="radio" id="add_truefalse" name="level" value="hard"> Hard <br>

                                            <br><b>Options:</b><br> 
                                            Option 1:<br><input type="text" name="option1" id="option1" value="">
                                            <br>Option 2:<br><input type="text" name="option2" id="option2" value="">
                                            <br>Option 3:<br><input type="text" name="option3" id="option3" value="">
                                            <br>Option 4:<br><input type="text" name="option4" id="option4" value=""><br>

                                            <br><b>Answers:</b><br> 
                                            <textarea style="width:100%" name="add_answers" maxlength="149" placeholder="type answers....."></textarea>
                                        </div>
                                        <div class="form-group">
                                            <button id='submit' class="form-control btn btn-primary rounded submit px-3">Send request</button>
                                        </div>
                                    </form>
   
                            </div>
                        </div>            
                    </div>
            <?php 
                $i++;    
                }                         
            ?>

        </div>        

	</body>
</html>
