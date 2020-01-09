<?php
session_start();
session_unset();
session_destroy();
ob_start();
header("location:Home.php");
ob_end_flush(); 
include 'Home.php';
//include 'home.php';
exit();
?>