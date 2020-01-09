<?php session_start();
	//$_SESSION['login_user']='Nick';
	$nick = 'Nick';
?>
<!DOCTYPE html>
<!-- Recipe-->
<html>
<? 
    include("header.php");
?>
<!-- Style -->
<style>
<?php include 'index.css'; ?>
</style>
<div class="topnav">
  <a href="Home.php">Home</a>
  <a href="RecipesSearch.php">Recipe Search</a>
  <a href="AddRecipe.php">Add Recipe</a>
  <a href="AddIngredient.php">Add Ingredient</a>  
  <a href="About.php">About</a>
    
  <?php if(!isset($_SESSION['login_user'])){ ?>
  <a href="LoginPage.php">Login</a>
  <a href="Account.php">Create Account</a>
  <?php } else{?>
  <a href="logout2.php">Logout</a>
  <?php } ?>
</div>
<div>
<?php

$error=''; // Variable To Store Error Message
if (isset($_POST['submit'])) {
if (empty($_POST['username']) || empty($_POST['password'])) {
$error = "Username or Password is invalid";
}
else
{
// Define $username and $password
$username=$_POST['username'];
$password=$_POST['password'];
// Establishing Connection with Server by passing server_name, user_id and password as a parameter
include 'connectvarsEECS.php'; 
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	//echo "$username";
	//echo "$password";
	$passwordenc=md5($password);
	$query = "select * from USER where PASSWORD='$passwordenc' AND USERNAME='$username'";
	$result = mysqli_query($conn, $query);
	$row_count = $result->num_rows;
//set session if logged in
	if ($row_count > 0) {
		$loginname = $username;
		$_SESSION['login_user']=$loginname; // Initializing Session
		echo "logged in as: ".$_SESSION['login_user'];
	} else {
		$error = "Username or Password is invalid";
	}
	mysql_close($conn); // Closing Connection
	}
}
//echo session_id();
?>
</div>