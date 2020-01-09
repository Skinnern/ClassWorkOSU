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
<h2>Add Ingredient</h2>
<?php
// change the value of $dbuser and $dbpass to your username and password
	include 'connectvarsEECS.php'; 
	
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}

	
	
	
// Escape user inputs for security
	$INameU = mysqli_real_escape_string($conn, $_POST['INameU']);
	$newcost = mysqli_real_escape_string($conn, $_POST['newcost']);
	
	//end age	
	
//check for unique Ingredient
	$numberOfErrors = 0;
	$queryUnique = "select Ingredient_name from INGREDIENT where Ingredient_name = '$INameU'";
	//check not empty
	echo $INameU;
	if(empty($INameU) == true){
		echo "
		please enter a Name for the item\n";
		$numberOfErrors++;
	}
	 if(empty($newcost) == true){
		echo "
		please enter a cost per ounce\n";
		$numberOfErrors++;
	}

	
	//if we have errors, do not let the user proceed
	if($numberOfErrors < 1) {
		if(mysqli_query($conn, $queryUnique)){
			//echo "Connected.";
			//fbsql_affected_rows
			$result = mysqli_query($conn, $queryUnique);
			
			//testing rows retrieved
			if (mysqli_num_rows($result) < 0) {
				echo "
				Error: ingredient does not exist in database";
				mysqli_close($conn);		
			} else{
				// attempt insert query 
				$query = "update INGREDIENT set Ingredient_cost = '$newcost' where Ingredient_name like '$INameU'";
				if(mysqli_query($conn, $query)){
					echo " was updated successfully!";
					$queryupdate = "call Update_Recipe_Costs();";
					if(mysqli_query($conn, $query)){
					echo "all costs updated successfully!";
				} else{
					echo "ERROR: Could not able to execute $query. " . mysqli_error($conn);
				}
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

	
