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
	$numstepsagain = $_GET["numstepsagain"];
// change the value of $dbuser and $dbpass to your username and password
	include 'connectvarsEECS.php'; 
	
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}

	
	
	
// Escape user inputs for security
	$Rname = mysqli_real_escape_string($conn, $_POST['Rname']);
	echo $Rname;
	//oh boy, if loop, we need to use the numstepsagain to get the values we want for here
	if($numstepsagain >= 1){
		$Step1 = mysqli_real_escape_string($conn, $_POST['Step1']);
		$IName1 = mysqli_real_escape_string($conn, $_POST['Iname1']);
		$ingredamount1 = mysqli_real_escape_string($conn, $_POST['ingredamount1']);
		//echo $Step1;
		//echo $IName1;
		//echo $ingredamount1;
	}
	if($numstepsagain >= 2){
		$Step2 = mysqli_real_escape_string($conn, $_POST['Step2']);
		$IName2 = mysqli_real_escape_string($conn, $_POST['Iname2']);
		$ingredamount2 = mysqli_real_escape_string($conn, $_POST['ingredamount2']);
		//echo $Step2;
		//echo $IName2;
		//echo $ingredamount2;
	}
	if($numstepsagain >= 3){
		$Step3 = mysqli_real_escape_string($conn, $_POST['Step3']);
		$IName3 = mysqli_real_escape_string($conn, $_POST['Iname3']);
		$ingredamount3 = mysqli_real_escape_string($conn, $_POST['ingredamount3']);
		//echo $Step3;
		//echo $IName3;
		//echo $ingredamount3;
	}
	if($numstepsagain >= 4){
		$Step4 = mysqli_real_escape_string($conn, $_POST['Step4']);
		$IName4 = mysqli_real_escape_string($conn, $_POST['Iname4']);
		$ingredamount4 = mysqli_real_escape_string($conn, $_POST['ingredamount4']);
		//echo $Step4;
		//echo $IName4;
		//echo $ingredamount4;
	}
	if($numstepsagain >= 5){
		$Step5 = mysqli_real_escape_string($conn, $_POST['Step5']);
		$IName5 = mysqli_real_escape_string($conn, $_POST['Iname5']);
		$ingredamount5 = mysqli_real_escape_string($conn, $_POST['ingredamount5']);
		//echo $Step5;
		//echo $IName5;
		//echo $ingredamount5;
	}
	if($numstepsagain >= 6){
		$Step6 = mysqli_real_escape_string($conn, $_POST['Step6']);
		$IName6 = mysqli_real_escape_string($conn, $_POST['Iname6']);
		$ingredamount6 = mysqli_real_escape_string($conn, $_POST['ingredamount6']);
		//echo $Step6;
		//echo $IName6;
		//echo $ingredamount6;
	}
	if($numstepsagain >= 7){
		$Step7 = mysqli_real_escape_string($conn, $_POST['Step7']);
		$IName7 = mysqli_real_escape_string($conn, $_POST['Iname7']);
		$ingredamount7 = mysqli_real_escape_string($conn, $_POST['ingredamount7']);
		//echo $Step7;
		//echo $IName7;
		//echo $ingredamount7;
	}
	if($numstepsagain >= 8){
		$Step8 = mysqli_real_escape_string($conn, $_POST['Step8']);
		$IName8 = mysqli_real_escape_string($conn, $_POST['Iname8']);
		$ingredamount8 = mysqli_real_escape_string($conn, $_POST['ingredamount8']);
		//echo $Step8;
		//echo $IName8;
		//echo $ingredamount8;
	}
	if($numstepsagain >= 9){
		$Step9 = mysqli_real_escape_string($conn, $_POST['Step9']);
		$IName9 = mysqli_real_escape_string($conn, $_POST['Iname9']);
		$ingredamount9 = mysqli_real_escape_string($conn, $_POST['ingredamount9']);
		//echo $Step9;
		//echo $IName9;
		//echo $ingredamount9;
	}
	if($numstepsagain >= 10){
		$Step10 = mysqli_real_escape_string($conn, $_POST['Step10']);
		$IName10 = mysqli_real_escape_string($conn, $_POST['Iname10']);
		$ingredamount10 = mysqli_real_escape_string($conn, $_POST['ingredamount10']);
		//echo $Step10;
		//echo $IName10;
		//echo $ingredamount10;
	}
	
	//end age	
	
//check for unique Ingredient
	$numberOfErrors = 0;
	$queryUnique = "select recipe_name from RECIPE where recipe_name = '$Rname'";
	//check not empty
	if(empty($Rname) == true){
		echo "
		please enter a Name for the recipe\n";
		$numberOfErrors++;
	}
	//echo "$IName1";
	//echo "$ingredamount1";
	echo "<br />";
	if($IName1 != '0' && $ingredamount1 <= 0 && $numstepsagain >= 1){
		echo "<br />";
		echo "Please enter an amount of ingredient 1";
		$numberOfErrors++;
	}
		if($IName2 != '0' && $ingredamount2 <= 0 && $numstepsagain >= 2){
		echo "<br />";
		echo "Please enter an amount of ingredient 2";
		$numberOfErrors++;
	}
		if($IName3 != '0' && $ingredamount3 <= 0 && $numstepsagain >= 3){
		echo "<br />";
		echo "Please enter an amount of ingredient 3";
		$numberOfErrors++;
	}
		if($IName4 != '0' && $ingredamount4 <= 0 && $numstepsagain >= 4){
		echo "<br />";
		echo "Please enter an amount of ingredient 4";
		$numberOfErrors++;
	}
		if($IName5 != '0' && $ingredamount5 <= 0 && $numstepsagain >= 5){
		echo "<br />";
		echo "Please enter an amount of ingredient 5";
		$numberOfErrors++;
	}
		if($IName6 != '0' && $ingredamount6 <= 0 && $numstepsagain >= 6){
		echo "<br />";
		echo "Please enter an amount of ingredient 6";
		$numberOfErrors++;
	}
		if($IName7 != '0' && $ingredamount7 <= 0 && $numstepsagain >= 7){
		echo "<br />";
		echo "Please enter an amount of ingredient 7";
		$numberOfErrors++;
	}
		if($IName8 != '0' && $ingredamount8 <= 0 && $numstepsagain >= 8){
		echo "<br />";
		echo "Please enter an amount of ingredient 8";
		$numberOfErrors++;
	}
		if($IName9 != '0' && $ingredamount9 <= 0 && $numstepsagain >= 9){
		echo "<br />";
		echo "Please enter an amount of ingredient 9";
		$numberOfErrors++;
	}
		if($IName10 != '0' && $ingredamount10 <= 0 && $numstepsagain >= 10){
			echo "<br />";
		echo "Please enter an amount of ingredient 10";
		$numberOfErrors++;
	}
	if(!isset($_SESSION['login_user'])){
		echo "<br />";
		echo "Please login to create a recipe";
		$numberOfErrors++;
	}
	
	
	
	 //if(empty($cost) == true){
	//	echo "
		//please enter a cost per ounce\n";
		//$numberOfErrors++;
	//}

	
	//if we have errors, do not let the user proceed
	if($numberOfErrors <= 0) {
		
		$userstuff = $_SESSION['login_user'];
		//echo $userstuff;
		$queryuserstuff = "select user_id from USER where username = '$userstuff'";
//lookup user id to submit

$resultuser = mysqli_query($conn, $queryuserstuff);
	if (!$resultuser) {
		die("Query to show fields from table failed");
	}
	
	//number of fields
	$fields_num = mysqli_num_fields($resultuser);


		while($row = mysqli_fetch_row($resultuser)) {	
					
				// $row is array... foreach( .. ) puts every element
				foreach($row as $cell)
				$user_id_recieved = $cell;	
				}
		
		
//end lookup
		if(mysqli_query($conn, $queryUnique)){
			//echo "Connected.";
			//fbsql_affected_rows
			$resultunique = mysqli_query($conn, $queryUnique);
			
			//testing rows retrieved
			if (mysqli_num_rows($resultunique) > 0) {
				echo "
				Error: That recipe name already exists in database, please try something else";
				mysqli_close($conn);		
			} else{
				// attempt insert query
				//NEED TO GET USER ID, THEN USE THAT TO INSERT USER_ID, RECIPE_NAME	
				//echo $user_id_recieved;
				//echo $Rname;
				
				$query = "INSERT INTO RECIPE (RECIPE_NAME, USER_ID) VALUES ('$Rname', '$user_id_recieved')";
				if(mysqli_query($conn, $query)){
					echo "New Recipe added successfully!";
				} else{
					echo "ERROR: Could not execute $query. " . mysqli_error($conn);
				}
			}
			
		} else{
			echo "ERROR: Could not able to execute $queryUnique. " . mysqli_error($conn);
		}
		
		
		//get recipe ID to use for our steps
				$queryRecipe = "select Recipe_id from RECIPE where RECIPE_NAME = '$Rname'";
		
				if(mysqli_query($conn, $queryRecipe)){
					$resultquery = mysqli_query($conn, $queryRecipe);

				$fields_num = mysqli_num_fields($resultquery);


					while($row2 = mysqli_fetch_row($resultquery)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($row2 as $cell2)
						$Recipe_id_recieved = $cell2;	
					}
				}
				//echo $Recipe_id_recieved;
		//end get recipe ID
		
		//Insert steps
		//huh, guess i just gotta user error checking to make sure my steps are valid, but anyway
		
		if(isset($Recipe_id_recieved)){
			//step 1
			echo $IName1;
			if ($IName1 == '0')
			$queryaddstep1 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step1', '$Recipe_id_recieved')";	
			
		} else {
			
			//get ingredient id for step
			 $ingredientidquery1 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName1'";
			 
			 if(mysqli_query($conn, $ingredientidquery1)){
					$resultingidquery1 = mysqli_query($conn, $ingredientidquery1);

				$fields_num = mysqli_num_fields($resultingidquery1);


					while($ingidrow1 = mysqli_fetch_row($resultingidquery1)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow1 as $ingidcell1)
						$id_for_recipe_step1 = $ingidcell1;	
						echo $id_for_recipe_step1;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					echo "here is step 1";
					echo "<br />";
					echo $Step1;
					
					echo "<br />";
					echo "here is ing id";
					echo "<br />";
					echo $ingredientidquery1;
					
										echo "<br />";
					echo "here is ing amount";
					echo "<br />";
					echo $ingredamount1;
					
										echo "<br />";
					echo "here is here is re";
					echo "<br />";
					echo $Recipe_id_recieved;
					$queryaddstep1 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step1', '$ingredientidquery1', '$ingredamount1', $Recipe_id_recieved)";
				//echo '$queryaddstep1';	
					
				}
			 
			 
			 //end get ingredient step
			 
			 
			 //insert step with ingredient
			 
		} 
		//echo $queryaddstep1;
		if(mysqli_query($conn, $queryaddstep1)){
		echo 'successfully added step1';
		
		} else 
		{
			echo 'failed to add step1';
		}
		
		//end insert steps
		
	}
// close connection
mysqli_close($conn);


?>
<div>
<? 
    include("footer.php");
?>
</html>

	
