<?php

include('../db.php'); // Подключение к базе данных

$findbylogin = $_REQUEST['findbylogin'];
$newlogin = $_REQUEST['newlogin'];
$findbyid;
$query = "SELECT * FROM users";
$result = mysqli_query($link, $query);

$users = [];
while ($row = mysqli_fetch_assoc($result)) {
    $users[] = $row;
}


var_dump ($_REQUEST);
foreach ($users as $user) {
    if ($user['login'] == $findbylogin) {
            $findbyid = $user['id'];
            var_dump ($findbyid);
        echo 
        "<div>
            <h2>{$user['id']}</h2>
            <i>{$user['login']}</i>
        </div>";
        $query = "UPDATE `users` 
        SET `login` = ('$newlogin')
        WHERE `id` = ('$findbyid')";

        $result = mysqli_query($link, $query);


        }
    }   



