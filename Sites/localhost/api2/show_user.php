<?php

include('../db.php'); // Подключение к базе данных

$showbyid = $_REQUEST['showbyid'];
$query = "SELECT * FROM users";
$result = mysqli_query($link, $query);

$users = [];
while ($row = mysqli_fetch_assoc($result)) {
    $users[] = $row;
}


// var_dump ($_REQUEST);
foreach ($users as $user) {
    if ($user['id'] == $showbyid) {
        // var_dump ($user['login']);    
        
    echo 
    "<div>
        <h2>{$user['id']}</h2>
        <i>{$user['login']}</i>
    </div>";
    }
    else {
        
    }
}