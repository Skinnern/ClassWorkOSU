<?php session_start(); ?>
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
<!-- end Style-->
<?php
	include 'connectvarsEECS.php'; 
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	$Searchitem = mysqli_real_escape_string($conn, $_POST['Searchitem']);
	$Locationof = $_POST['Locationof'];

	//$Location = mysqli_real_escape_string($conn, $_POST['Location']);
	//query to execute
	//echo $Searchitem;
	//echo $Locationof;
	if ($Locationof == '1'){
	$query = "select Recipe_name from RECIPE where Recipe_name like '%$Searchitem%' LIMIT 0,20";	
	}
	if ($Locationof == '2'){
	$query = "select U.USERNAME, R.RECIPE_NAME from USER U, RECIPE R where R.USER_ID = U.USER_ID and U.USERNAME like '%$Searchitem%' LIMIT 0,20";
	}
	if ($Locationof == '3'){
	$query = "select I.Ingredient_name, R.RECIPE_NAME from INGREDIENT I, RECIPE R, STEP S where I.INGREDIENT_ID = S.INGREDIENT_ID and S.RECIPE_ID = R.RECIPE_ID and I.INGREDIENT_NAME LIKE '%$Searchitem%' LIMIT 0,20";	
	}
	if ($Locationof == '4'){
	$query = "select RECIPE_COST, RECIPE_NAME from RECIPE where RECIPE_COST <= $Searchitem LIMIT 0,20";	
	}

	
	$result = mysqli_query($conn, $query);
	
	echo "<div>";
	if (!$result) {
		die("Query to show fields from table failed");
	}
	
	//number of fields
	$fields_num = mysqli_num_fields($result);
	echo "<h1>Search Results for $Searchitem $table </h1>";
	echo "<table id='t01' border='1'><tr>";
	
	//table headers
	if ($Locationof == '1'){
	echo "<td><b>Recipe Name</b></td>";
	}	
	if ($Locationof == '2'){
	echo "<td><b>User</b></td>";
	echo "<td><b>Recipe</b></td>";
	}	
	if ($Locationof == '3'){
	echo "<td><b>Ingredient</b></td>";
	echo "<td><b>Recipe</b></td>";
	}	
	if ($Locationof == '4'){
	echo "<td><b>Cost</b></td>";
	echo "<td><b>Recipe</b></td>";
	}	
	//echo "<td><b>Recipe Name</b></td>";
	//echo "<td><b>Total Cost</b></td>";
	//echo "</tr>\n";
	
	//table content
	/*
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		foreach($row as $cell)		
			echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
	*/
	//wowowowowowowowo
	
	
	if ($Locationof == '1'){
	//begin
	while($row = mysqli_fetch_row($result)) {		
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		foreach($row as $cell)		
			?>
			<td><a href="Recipe.php?name=<?php echo $cell; ?>"><?php echo $cell; ?></a></td>
			<?php
		echo "</tr>\n";
	}
	//end
	}	
	//end if recipe
	if ($Locationof == '2'){
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		$i=1;
		foreach($row as $cell)
			if($i == 2 || $i == 4|| $i == 6|| $i == 8|| $i == 10|| $i == 12|| $i == 14|| $i == 16|| $i == 18|| $i == 20|| $i == 22| $i == 24|| $i == 26|| $i == 28|| $i == 30 || $i == 32|| $i == 34|| $i == 36|| $i == 38|| $i == 40|| $i == 42){
				//echo "<td>$cell</td>";
				?>
				<td><a href="Recipe.php?name=<?php echo $cell; ?>"><?php echo $cell; ?></a></td>
				<?php
				$i++;				
			}else{
				echo "<td>$cell</td>";
				$i++;
			}
		echo "</tr>\n";
	}
		//end massive if
			//echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
	//if ingred
	if ($Locationof == '3'){
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		$i=1;
		foreach($row as $cell)
			if($i == 2 || $i == 4|| $i == 6|| $i == 8|| $i == 10|| $i == 12|| $i == 14|| $i == 16|| $i == 18|| $i == 20|| $i == 22| $i == 24|| $i == 26|| $i == 28|| $i == 30 || $i == 32|| $i == 34|| $i == 36|| $i == 38|| $i == 40|| $i == 42){
				//echo "<td>$cell</td>";
				?>
				<td><a href="Recipe.php?name=<?php echo $cell; ?>"><?php echo $cell; ?></a></td>
				<?php
				$i++;				
			}else{
				echo "<td>$cell</td>";
				$i++;
			}
		echo "</tr>\n";
	}
		//end massive if
			//echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
		
	if ($Locationof == '4'){
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		$i=1;
		foreach($row as $cell)
			if($i == 2 || $i == 4|| $i == 6|| $i == 8|| $i == 10|| $i == 12|| $i == 14|| $i == 16|| $i == 18|| $i == 20|| $i == 22| $i == 24|| $i == 26|| $i == 28|| $i == 30 || $i == 32|| $i == 34|| $i == 36|| $i == 38|| $i == 40|| $i == 42){
				//echo "<td>$cell</td>";
				?>
				<td><a href="Recipe.php?name=<?php echo $cell; ?>"><?php echo $cell; ?></a></td>
				<?php
				$i++;				
			}else{
				echo "<td>$cell</td>";
				$i++;
			}
		echo "</tr>\n";
	}
		//end massive if
			//echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
	
	
	
	
	//wowowowowoowowowowowow
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	mysqli_free_result($result);
	mysqli_close($conn);
	echo "</div>"
?>
<? 
    include("footer.php");
?>
</html>

	
