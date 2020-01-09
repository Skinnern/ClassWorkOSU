<?php
// Establishing Connection with Server by passing server_name, user_id and password as a parameter
include 'connectvarsEECS.php'; 
$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
session_start();// Starting Session
// Storing Session
$user_check=$_SESSION['login_user'];
// SQL Query To Fetch Complete Information Of User
$ses_sql=mysql_query("select username from User where username='$user_check'", $conn);
$row = mysql_fetch_assoc($ses_sql);
$login_session =$row['username'];
if(!isset($login_session)){
mysql_close($connection); // Closing Connection
header('Location: home.php'); // Redirecting To Home Page
}
?>