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
	//echo $Rname;
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
	
	//please enter ingredienf for #1, if nothing used, please select nothing
	if($IName1 == '0' && $numstepsagain >= 1){
		echo "<br />";
		echo "Please enter ingredient 1, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName2 == '0' && $numstepsagain >= 2){
		echo "<br />";
		echo "Please enter ingredient 2, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName3 == '0' && $numstepsagain >= 3){
		echo "<br />";
		echo "Please enter ingredient 3, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName4 == '0' && $numstepsagain >= 4){
		echo "<br />";
		echo "Please enter ingredient 4, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}if($IName5 == '0' && $numstepsagain >= 5){
		echo "<br />";
		echo "Please enter ingredient 5, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}if($IName6 == '0' && $numstepsagain >= 6){
		echo "<br />";
		echo "Please enter ingredient 6, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName7 == '0' && $numstepsagain >= 7){
		echo "<br />";
		echo "Please enter ingredient 7, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName8 == '0' && $numstepsagain >= 8){
		echo "<br />";
		echo "Please enter ingredient 8, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName9 == '0' && $numstepsagain >= 9){
		echo "<br />";
		echo "Please enter ingredient 9, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	if($IName10 == '0' && $numstepsagain >= 10){
		echo "<br />";
		echo "Please enter ingredient 10, if no ingredient is needed, please select 'Nothing'";
		$numberOfErrors++;
	}
	//end check ingredient set
	
	
	echo "<br />";
	if($IName1 != '0' && $ingredamount1 <= 0 && $numstepsagain >= 1){
		echo "<br />";
		echo "Please enter an amount of ingredient 1, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName2 != '0' && $ingredamount2 <= 0 && $numstepsagain >= 2){
		echo "<br />";
		echo "Please enter an amount of ingredient 2, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName3 != '0' && $ingredamount3 <= 0 && $numstepsagain >= 3){
		echo "<br />";
		echo "Please enter an amount of ingredient 3, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName4 != '0' && $ingredamount4 <= 0 && $numstepsagain >= 4){
		echo "<br />";
		echo "Please enter an amount of ingredient 4, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName5 != '0' && $ingredamount5 <= 0 && $numstepsagain >= 5){
		echo "<br />";
		echo "Please enter an amount of ingredient 5, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName6 != '0' && $ingredamount6 <= 0 && $numstepsagain >= 6){
		echo "<br />";
		echo "Please enter an amount of ingredient 6, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName7 != '0' && $ingredamount7 <= 0 && $numstepsagain >= 7){
		echo "<br />";
		echo "Please enter an amount of ingredient 7, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName8 != '0' && $ingredamount8 <= 0 && $numstepsagain >= 8){
		echo "<br />";
		echo "Please enter an amount of ingredient 8, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName9 != '0' && $ingredamount9 <= 0 && $numstepsagain >= 9){
		echo "<br />";
		echo "Please enter an amount of ingredient 9, if option 'Nothing' is selected, add any amount you would like";
		$numberOfErrors++;
	}
		if($IName10 != '0' && $ingredamount10 <= 0 && $numstepsagain >= 10){
			echo "<br />";
		echo "Please enter an amount of ingredient 10, if option 'Nothing' is selected, add any amount you would like";
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
				if($numstepsagain >= 1){
		if(isset($Recipe_id_recieved)){
			//step 1
			//echo $IName1;
			//if ($IName1 == '0')
			//$queryaddstep1 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step1', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery1 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName1'";
			 
			 if(mysqli_query($conn, $ingredientidquery1)){
					$resultingidquery1 = mysqli_query($conn, $ingredientidquery1);

				$fields_num = mysqli_num_fields($resultingidquery1);


					while($ingidrow1 = mysqli_fetch_row($resultingidquery1)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow1 as $ingidcell1)
						$id_for_recipe_step1 = $ingidcell1;	
						//echo $id_for_recipe_step1;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 1";
					echo "<br />";
					//echo $Step1;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery1;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount1;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep1 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step1', '$id_for_recipe_step1', '$ingredamount1', $Recipe_id_recieved)";
				//echo '$queryaddstep1';	
					
				}
		
		
		
		
		//will this work end
			
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
				if($numstepsagain >= 2){
		if(isset($Recipe_id_recieved)){
			//step 2
			//echo $IName2;
			//if ($IName2 == '0')
			//$queryaddstep2 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step2', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery2 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName2'";
			 
			 if(mysqli_query($conn, $ingredientidquery2)){
					$resultingidquery2 = mysqli_query($conn, $ingredientidquery2);

				$fields_num = mysqli_num_fields($resultingidquery2);


					while($ingidrow2 = mysqli_fetch_row($resultingidquery2)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow2 as $ingidcell2)
						$id_for_recipe_step2 = $ingidcell2;	
						//echo $id_for_recipe_step2;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 2";
					echo "<br />";
					//echo $Step2;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery2;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount2;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep2 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step2', '$id_for_recipe_step2', '$ingredamount2', $Recipe_id_recieved)";
				//echo '$queryaddstep2';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep2;
		if(mysqli_query($conn, $queryaddstep2)){
		echo 'successfully added step2';
		
		} else 
		{
			echo 'failed to add step2';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 3){
		if(isset($Recipe_id_recieved)){
			//step 3
			//echo $IName3;
			//if ($IName3 == '0')
			//$queryaddstep3 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step3', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery3 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName3'";
			 
			 if(mysqli_query($conn, $ingredientidquery3)){
					$resultingidquery3 = mysqli_query($conn, $ingredientidquery3);

				$fields_num = mysqli_num_fields($resultingidquery3);


					while($ingidrow3 = mysqli_fetch_row($resultingidquery3)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow3 as $ingidcell3)
						$id_for_recipe_step3 = $ingidcell3;	
						//echo $id_for_recipe_step3;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 3";
					echo "<br />";
					//echo $Step3;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery3;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount3;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep3 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step3', '$id_for_recipe_step3', '$ingredamount3', $Recipe_id_recieved)";
				//echo '$queryaddstep3';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep3;
		if(mysqli_query($conn, $queryaddstep3)){
		echo 'successfully added step3';
		
		} else 
		{
			echo 'failed to add step3';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 4){
		if(isset($Recipe_id_recieved)){
			//step 4
			//echo $IName4;
			//if ($IName4 == '0')
			//$queryaddstep4 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step4', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery4 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName4'";
			 
			 if(mysqli_query($conn, $ingredientidquery4)){
					$resultingidquery4 = mysqli_query($conn, $ingredientidquery4);

				$fields_num = mysqli_num_fields($resultingidquery4);


					while($ingidrow4 = mysqli_fetch_row($resultingidquery4)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow4 as $ingidcell4)
						$id_for_recipe_step4 = $ingidcell4;	
						//echo $id_for_recipe_step4;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 4";
					echo "<br />";
					//echo $Step4;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery4;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount4;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep4 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step4', '$id_for_recipe_step4', '$ingredamount4', $Recipe_id_recieved)";
				//echo '$queryaddstep4';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep4;
		if(mysqli_query($conn, $queryaddstep4)){
		echo 'successfully added step4';
		
		} else 
		{
			echo 'failed to add step4';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 5){
		if(isset($Recipe_id_recieved)){
			//step 5
			//echo $IName5;
			//if ($IName5 == '0')
			//$queryaddstep5 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step5', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery5 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName5'";
			 
			 if(mysqli_query($conn, $ingredientidquery5)){
					$resultingidquery5 = mysqli_query($conn, $ingredientidquery5);

				$fields_num = mysqli_num_fields($resultingidquery5);


					while($ingidrow5 = mysqli_fetch_row($resultingidquery5)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow5 as $ingidcell5)
						$id_for_recipe_step5 = $ingidcell5;	
						//echo $id_for_recipe_step5;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 5";
					echo "<br />";
					//echo $Step5;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery5;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount5;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep5 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step5', '$id_for_recipe_step5', '$ingredamount5', $Recipe_id_recieved)";
				//echo '$queryaddstep5';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep5;
		if(mysqli_query($conn, $queryaddstep5)){
		echo 'successfully added step5';
		
		} else 
		{
			echo 'failed to add step5';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 6){
		if(isset($Recipe_id_recieved)){
			//step 6
			//echo $IName6;
			//if ($IName6 == '0')
			//$queryaddstep6 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step6', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery6 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName6'";
			 
			 if(mysqli_query($conn, $ingredientidquery6)){
					$resultingidquery6 = mysqli_query($conn, $ingredientidquery6);

				$fields_num = mysqli_num_fields($resultingidquery6);


					while($ingidrow6 = mysqli_fetch_row($resultingidquery6)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow6 as $ingidcell6)
						$id_for_recipe_step6 = $ingidcell6;	
						//echo $id_for_recipe_step6;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 6";
					echo "<br />";
					//echo $Step6;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery6;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount6;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep6 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step6', '$id_for_recipe_step6', '$ingredamount6', $Recipe_id_recieved)";
				//echo '$queryaddstep6';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep6;
		if(mysqli_query($conn, $queryaddstep6)){
		echo 'successfully added step6';
		
		} else 
		{
			echo 'failed to add step6';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 7){
		if(isset($Recipe_id_recieved)){
			//step 7
			//echo $IName7;
			//if ($IName7 == '0')
			//$queryaddstep7 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step7', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery7 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName7'";
			 
			 if(mysqli_query($conn, $ingredientidquery7)){
					$resultingidquery7 = mysqli_query($conn, $ingredientidquery7);

				$fields_num = mysqli_num_fields($resultingidquery7);


					while($ingidrow7 = mysqli_fetch_row($resultingidquery7)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow7 as $ingidcell7)
						$id_for_recipe_step7 = $ingidcell7;	
						//echo $id_for_recipe_step7;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 7";
					echo "<br />";
					//echo $Step7;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery7;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount7;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep7 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step7', '$id_for_recipe_step7', '$ingredamount7', $Recipe_id_recieved)";
				//echo '$queryaddstep7';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep7;
		if(mysqli_query($conn, $queryaddstep7)){
		echo 'successfully added step7';
		
		} else 
		{
			echo 'failed to add step7';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 8){
		if(isset($Recipe_id_recieved)){
			//step 8
			//echo $IName8;
			//if ($IName8 == '0')
			//$queryaddstep8 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step8', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery8 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName8'";
			 
			 if(mysqli_query($conn, $ingredientidquery8)){
					$resultingidquery8 = mysqli_query($conn, $ingredientidquery8);

				$fields_num = mysqli_num_fields($resultingidquery8);


					while($ingidrow8 = mysqli_fetch_row($resultingidquery8)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow8 as $ingidcell8)
						$id_for_recipe_step8 = $ingidcell8;	
						//echo $id_for_recipe_step8;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 8";
					echo "<br />";
					//echo $Step8;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery8;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount8;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep8 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step8', '$id_for_recipe_step8', '$ingredamount8', $Recipe_id_recieved)";
				//echo '$queryaddstep8';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep8;
		if(mysqli_query($conn, $queryaddstep8)){
		echo 'successfully added step8';
		
		} else 
		{
			echo 'failed to add step8';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 9){
		if(isset($Recipe_id_recieved)){
			//step 9
			//echo $IName9;
			//if ($IName9 == '0')
			//$queryaddstep9 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step9', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery9 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName9'";
			 
			 if(mysqli_query($conn, $ingredientidquery9)){
					$resultingidquery9 = mysqli_query($conn, $ingredientidquery9);

				$fields_num = mysqli_num_fields($resultingidquery9);


					while($ingidrow9 = mysqli_fetch_row($resultingidquery9)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow9 as $ingidcell9)
						$id_for_recipe_step9 = $ingidcell9;	
						//echo $id_for_recipe_step9;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 9";
					echo "<br />";
					//echo $Step9;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery9;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount9;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep9 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step9', '$id_for_recipe_step9', '$ingredamount9', $Recipe_id_recieved)";
				//echo '$queryaddstep9';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep9;
		if(mysqli_query($conn, $queryaddstep9)){
		echo 'successfully added step9';
		
		} else 
		{
			echo 'failed to add step9';
		}
		
		//end insert steps
		}
				if($numstepsagain >= 10){
		if(isset($Recipe_id_recieved)){
			//step 10
			//echo $IName10;
			//if ($IName10 == '0')
			//$queryaddstep10 = "insert into STEP (STEP_DESC, recipe_id) values ('$Step10', '$Recipe_id_recieved')";	
		//will this work
		
		//get ingredient id for step
			 $ingredientidquery10 = "select Ingredient_id from INGREDIENT where Ingredient_name = '$IName10'";
			 
			 if(mysqli_query($conn, $ingredientidquery10)){
					$resultingidquery10 = mysqli_query($conn, $ingredientidquery10);

				$fields_num = mysqli_num_fields($resultingidquery10);


					while($ingidrow10 = mysqli_fetch_row($resultingidquery10)) {	
					
				// $row is array... foreach( .. ) puts every element
						foreach($ingidrow10 as $ingidcell10)
						$id_for_recipe_step10 = $ingidcell10;	
						//echo $id_for_recipe_step10;
					}
					//insert step w/ ingred and amount
					echo "<br />";
					//echo "here is step 10";
					echo "<br />";
					//echo $Step10;
					
					echo "<br />";
					//echo "here is ing id";
					echo "<br />";
					//echo $ingredientidquery10;
					
										echo "<br />";
					//echo "here is ing amount";
					echo "<br />";
					//echo $ingredamount10;
					
										echo "<br />";
					//echo "here is here is re";
					echo "<br />";
					//echo $Recipe_id_recieved;
					$queryaddstep10 = "insert into STEP (STEP_DESC, ingredient_id, ingredient_amount, recipe_id) values ('$Step10', '$id_for_recipe_step10', '$ingredamount10', $Recipe_id_recieved)";
				//echo '$queryaddstep10';	
					
				}
		
		
		
		
		//will this work end
			
		} 
		//echo $queryaddstep10;
		if(mysqli_query($conn, $queryaddstep10)){
		echo 'successfully added step10';
		
		} else 
		{
			echo 'failed to add step10';
		}
		
		//end insert steps
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

	
