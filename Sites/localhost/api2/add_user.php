<?php

include('../db.php'); // Подключение к базе данных

$login = $_GET['login'];
// $pass = $_POST['pass'];
$pass = '12345';
$date_created = '2018-10-07';
// $img_path = 'default.jpg';
// if (strlen($pass) < 3 || strlen($login) < 3) {
if ( strlen($login) < 3) {
    header('Location: ../index.php');
} else {
    $query = "INSERT INTO users (login, pass, date_created )
              VALUES ( '$login', '$pass', '$date_created')
              ";

    $result = mysqli_query($link, $query);

    if( $result ){
        echo "Успешно";
    }else{
        echo "Произошла ошибка";
    }




    // if ($result) {
    //     header('Location: ../index.php');
    // } else {
    //     header('Location: ../index.php');
    // }
}