<?php
session_start();

if(isset($_SESSION['name'])){
echo 'welcome, '.$_SESSION['name'];
} else{
echo "Please log in";
}
?>