$(document).ready(function(){
    $(".all_user").submit(function(){
        var xhr = new XMLHttpRequest();
        console.log(".all_user");
        xhr.open("POST", "api2/all_user.php");
        xhr.send();
        console.log(xhr);
        xhr.onreadystatechange = function(){
            if( xhr.readyState == 4 && xhr.status == 200 ){
                alert(xhr.responseText);

                $(".otvet").append(xhr.responseText);
            }
        }
        return false;
    });

    $(".adduser").submit(function(){

        var xhr = new XMLHttpRequest();
        var id = this.children.id.value;
        var login = this.children.login.value;
        console.log(login);
        var date_created = this.children.date_created.value;
        xhr.open("GET", "api2/add_user.php?login=" + login);
        // xhr.open("GET", "/api2/add_user.php?login=" + login + "&date_created=" + date_created);

        xhr.send();

        xhr.onreadystatechange = function(){
            if( xhr.readyState == 4 && xhr.status == 200 ){
                alert( xhr.responseText );
            }
        }


        return false;
    });

    $(".show_user").submit(function(){
        var xhr = new XMLHttpRequest();
        console.log(".show_user");
        // var id = this.children.id.value;
        var showbyid = this.children.showbyid.value;
        console.log(showbyid);
        xhr.open("POST", "api2/show_user?showbyid=" + showbyid);
        // xhr.open("POST", "api2/show_user.php");
        xhr.send();
        console.log(xhr);
        xhr.onreadystatechange = function(){
            if( xhr.readyState == 4 && xhr.status == 200 ){
                // alert(xhr.responseText);

                $(".otvet2").append(xhr.responseText);
            }
        }
        return false;
    });

    $(".update_user").submit(function(){
        var xhr = new XMLHttpRequest();
        console.log(".update_user");
        var findbylogin = this.children.findbylogin.value;
        var newlogin = this.children.newlogin.value;
        // xhr.open("POST", "api2/update_user.php");
        xhr.open("POST", "api2/update_user.php?findbylogin=" + findbylogin + "&newlogin=" + newlogin);
        xhr.send();
        // console.log(xhr);
        xhr.onreadystatechange = function(){
            if( xhr.readyState == 4 && xhr.status == 200 ){
                // alert(xhr.responseText);

                $(".otvet3").append(xhr.responseText);
            }
        }
        return false;
    });
});