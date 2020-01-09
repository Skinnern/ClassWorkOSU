<?php session_start(); ?>
<!DOCTYPE html>
<!-- new account -->
<html>
<? 
    include("header.php");
?>

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
<h2>Add User</h2>
<?php
// change the value of $dbuser and $dbpass to your username and password
	include 'connectvarsEECS.php'; 
	
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}

	
	
	
// Escape user inputs for security
	$username = mysqli_real_escape_string($conn, $_POST['username']);
	$email = mysqli_real_escape_string($conn, $_POST['email']);
	$password = mysqli_real_escape_string($conn, $_POST['password']);
	
	//end age	
	
//check for unique username
	$numberOfErrors = 0;
	$queryUnique = "select username from Users where username = '$username'";
	//check not empty
	if(empty($username) == true){
		echo "
		please enter a username\n";
		$numberOfErrors++;
	}
	 if(empty($email) == true){
		echo "
		please enter an email\n";
		$numberOfErrors++;
	}
	 if(empty($password) == true){
		echo "
		please enter a password\n";
		$numberOfErrors++;
	}
	
	//if we have errors, do not let the user proceed
	if($numberOfErrors < 1) {
		if(mysqli_query($conn, $queryUnique)){
			//echo "Connected.";
			//fbsql_affected_rows
			$result = mysqli_query($conn, $queryUnique);
			
			//testing rows retrieved
			if (mysqli_num_rows($result) > 0) {
				echo "
				Error: username already exists in database, please retry with a different user";
				mysqli_close($conn);		
			} else{
				// attempt insert query 
				$passwordenc=md5($password);
				$query = "INSERT INTO USER (username, email, password) VALUES ('$username', '$email', '$passwordenc')";
				if(mysqli_query($conn, $query)){
					echo "New User added successfully!";
				} else{
					echo "ERROR: Could not able to execute $query. " . mysqli_error($conn);
				}
			}
			
		} else{
			echo "ERROR: Could not able to execute $queryUnique. " . mysqli_error($conn);
		}
	}
// close connection
mysqli_close($conn);
?>
<div>
<? 
    include("footer.php");
?>
</html>

	
