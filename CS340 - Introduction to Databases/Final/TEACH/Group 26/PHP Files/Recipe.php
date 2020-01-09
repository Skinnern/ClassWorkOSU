<? session_start(); ?>
<!DOCTYPE html>
<!-- Recipe -->
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
<!-- end Style-->
<div>
<?php
	//recipe steps
	include 'connectvarsEECS.php'; 
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	$searchitem = $_GET["name"];
	$query = "select S.STEP_DESC, I.INGREDIENT_NAME, S.INGREDIENT_AMOUNT from RECIPE R, STEP S, INGREDIENT I where R.RECIPE_ID=S.RECIPE_ID and S.INGREDIENT_ID = I.INGREDIENT_ID and R.RECIPE_NAME like '$searchitem';";
	$querycost = "select RECIPE_COST from RECIPE WHERE RECIPE_NAME LIKE '$searchitem';";
	
	//cost query
	$resultcost = mysqli_query($conn, $querycost);
	if (!$resultcost) {
		die("Query to show fields from table failed");
	} else{
		while($rowcost = mysqli_fetch_row($resultcost)) {	
		echo "";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		foreach($rowcost as $cellcost)		
			echo "<h2>This Recipe's Total Cost Is Roughly: $cellcost Dollars</h2>";	
		echo "\n";
	}
		
		
	}
	
	//end cost query
	$result = mysqli_query($conn, $query);
	if (!$result) {
		die("Query to show fields from table failed");
	}
	$fields_num = mysqli_num_fields($result);
	echo "<h1>Steps: $table </h1>";
	echo "<table id='t01' border='1'><tr>";

	echo "<th><b>Step Description</b></th>";
	echo "<th><b>Ingredient Used</b></th>";
	echo "<th><b>Amount(In ounces)</b></th>";
	
	echo "</tr>\n";
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		foreach($row as $cell)		
			echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
	
	//Comments
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	$query = "Select U.USERNAME, C.COMMENT from COMMENT C, RECIPE R, USER U where C.RECIPE_ID = R.RECIPE_ID and C.USER_ID = U.USER_ID and R.RECIPE_NAME like '$searchitem';";
	$result = mysqli_query($conn, $query);
	if (!$result) {
		die("Query to show fields from table failed");
	}
	$fields_num = mysqli_num_fields($result);
	//echo "<h1>Comments: $table </h1>";
	echo "<table id='t01' border='1'><tr>";
	//table headers
	//for($i=0; $i<$fields_num; $i++) {	
	//	$field = mysqli_fetch_field($result);	
	//	echo "<th><b>$field->name</b></th>";
	//}
	
	echo "<th><b>User</b></th>";
	echo "<th><h>Comment</b></th>";
	echo "</tr>\n";
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		foreach($row as $cell)		
			echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
	//get recipe id to pass as get
	$queryfortheget = "select recipe_id from RECIPE where recipe_name = '$searchitem'";

$resultget = mysqli_query($conn, $queryfortheget);
		if (!$resultget) {
			die("Query to show fields from table failed");
		}




		while($rowget = mysqli_fetch_row($resultget)) {	
					
				// $row is array... foreach( .. ) puts every element
				foreach($rowget as $cellget)				
				$nickgetresult = $cellget;	
				}
	
	//end get request

	mysqli_free_result($result);
	mysqli_close($conn);
?>
</div>
<div>
	<?php if(isset($_SESSION['login_user'])){ ?>

		<form action="AddComment.php?nickget=<?php echo $nickgetresult; ?>" method="post">
			<label for="commenttext">Leave a Comment</label>
			<p>
			</p>
			<input type="text" id="commenttext" name="commenttext" placeholder="Type in comment here...">
			<input type="submit" value="Submit">
		</form>
	<?php }?>

</div>



<? 
    include("footer.php");
?>
</html>

	
