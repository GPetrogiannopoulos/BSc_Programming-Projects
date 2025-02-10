<?php
    session_start();
    include("connect.php");

            // single
        $question = "Which of the chess pieces below can promote to queen?";
        $level = "Easy";
        $type = "single";
        $options = "knight,rook,pawn";
        $answer = "pawn";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);
   
        $question = "Which piece cant draw a straight line while moving?";
        $level = "Easy";
        $type = "single";
        $options = "rook,kinght,pawn,bishop";
        $answer = "knight";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

        $question = "a player cant move any of his pieces ,that results in:";
        $level = "Easy";
        $type = "single";
        $options = "defeat,win,draw";
        $answer = "draw";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

        $question = "The Queen can move like the rest of the pieces , except one, which is the:";
        $level = "Easy";
        $type = "single";
        $options = "pawn,rook,knight,king,bishop";
        $answer = "knight";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

            // multiple
        $question = "The Queen can move like a:";
        $level = "Easy";
        $type = "multiple";
        $options = "pawn,rook,knight,king,bishop";
        $answer = "pawn,rook,king,bishop";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);
            // truefalse
        $question = "Pawns promote to any piece, except the King, when they reach the other end of the board.";
        $level = "Easy";
        $type = "truefalse";
        $options = "True,False";
        $answer = "True";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

        $question = "A draw can occur when both players move the same piece to the same place three times in a row";
        $level = "Easy";
        $type = "truefalse";
        $options = "True,False";
        $answer = "True";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

        $question = "You can Checkmate with just a Rook and a bishop";
        $level = "Easy";
        $type = "truefalse";
        $options = "True,False";
        $answer = "False";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

        $question = "You must start out the game by moving a Pawn out first";
        $level = "Easy";
        $type = "truefalse";
        $options = "True,False";
        $answer = "False";
        $sql = "insert into question_pool (question,level,type,options,answer) values ('$question','$level','$type','$options','$answer')";
        $output = mysqli_query($conn,$sql);

?>