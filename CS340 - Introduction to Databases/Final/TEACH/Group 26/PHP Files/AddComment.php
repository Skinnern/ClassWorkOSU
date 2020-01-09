<?php session_start(); ?>
<html>
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

<h2>Add Comment</h2>
<?php
// change the value of $dbuser and $dbpass to your username and password
	include 'connectvarsEECS.php'; 
	
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}

	
	
	
// Escape user inputs for security
	$commenttext = mysqli_real_escape_string($conn, $_POST['commenttext']);
	
	//end age	
	
//check for unique Ingredient
	$numberOfErrors = 0;
	$recipe_from = $_GET['nickget'];
	$CurrUser = $_SESSION['login_user'];
	if (isset($CurrUser)){
	} else{
	echo "this is so wonky";
	}
	$queryUnique = "select user_id from USER where username = '$CurrUser' LIMIT 1";
	//check not empty
	 if(empty($CurrUser) == true){
		echo "
		please login before commenting\n";
		$numberOfErrors++;
	}if(empty($commenttext) == true){
		echo "
		please enter a comment before submitting\n";
		$numberOfErrors++;
	}
	$result = mysqli_query($conn, $queryUnique);
	while($row = mysqli_fetch_row($result)) {		
		// $row is array... foreach( .. ) puts every element
		foreach($row as $cell)		
			$id = $cell;	
	}
	if($numberOfErrors < 1) {
		if(mysqli_query($conn, $queryUnique)){
			//echo "Connected.";
			//fbsql_affected_rows
			$result = mysqli_query($conn, $queryUnique);
				// attempt insert query 
				$query = "INSERT INTO COMMENT (user_id, recipe_id, Comment) VALUES ('$id', $recipe_from, '$commenttext')";
				if(mysqli_query($conn, $query)){
					echo "New Comment added successfully!";
				} else{
					echo "ERROR: Could not able to execute $query. " . mysqli_error($conn);
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

	
