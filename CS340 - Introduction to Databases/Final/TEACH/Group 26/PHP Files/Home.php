<?php session_start();
	$nick = $_SESSION['login_user'];
	//include('session.php');
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
<!-- end Style-->
<div>
<?php
	include 'connectvarsEECS.php'; 
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	
	//query to execute
	$query = "select U.USERNAME, r.RECIPE_NAME, r.RECIPE_COST from RECIPE r, USER U where r.USER_ID = U.USER_ID LIMIT 0,10";
	$result = mysqli_query($conn, $query);
	if (!$result) {
		die("Query to show fields from table failed");
	}
	
	//number of fields
	$fields_num = mysqli_num_fields($result);
	echo "<h1>Popular Recipes: $table </h1>";
	echo "<table id='t01' border='1'><tr>";
	
	//table headers
	echo "<th><b>User</b></th>";	
	echo "<th><b>Recipe Name</b></th>";
	echo "<th><b>Total Cost</b></th>";
	echo "</tr>\n";

	//table content
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		$i=1;
		foreach($row as $cell)
			if ($i == 2 || $i == 5 || $i == 8 || $i == 11 || $i == 14 || $i == 17 || $i == 20 || $i == 23 || $i == 26 || $i == 29){
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

	mysqli_free_result($result);
	mysqli_close($conn);
?>
</div>
<? 
	
    include("footer.php");
?>
</html>

	
