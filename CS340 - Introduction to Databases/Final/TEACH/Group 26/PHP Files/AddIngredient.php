<?php session_start(); ?>
<!DOCTYPE html>
<!-- Add Student to Table User -->
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
<h2> Add new Ingredient</h2>
<form action="insertIngredient.php" method="post">
    <p>
        <label for="IName">Ingredient Name:</label>
		<p>
			</p>
        <input type="text" name="IName" id="IName"  placeholder="Ingredient Name...">
    </p>
	<p>
        <label for="cost">Ingredient Cost (in ounces):</label>
		<p>
			</p>
        <input type="text" name="cost" id="cost"  placeholder="Ingredient Cost...">
    </p>
    <input type="submit" value="Submit">
</form>
</div>
<br />
<div>
<h2>OR</h2>
</div>
<br />
<div>
<?php
include 'connectvarsEECS.php'; 
		$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
		if (!$conn) {
			die('Could not connect: ' . mysql_error());
		}
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>
<h2> Update Existing Ingredient</h2>
<form action="updateingredient.php" method="post">
    <p>
        <label for="INameU">Ingredient Name:</label>
		<p>
			</p>
        <select name="INameU" id="INameU">
				<option value = "0" selected = "selected">Select...</option>
				<?php
				while($row = mysqli_fetch_row($result)) {	
					
				// $row is array... foreach( .. ) puts every element
				foreach($row as $cell)
				echo "<option>";				
				echo "$cell";	
				echo "</option>\n";
				}
				?>
			</select>
    </p>
	<p>
        <label for="newcost"> New Cost (In ounces):</label>
		<p>
			</p>
        <input type="text" name="newcost" id="newcost"  placeholder="Ingredient Cost...">
    </p>
    <input type="submit" value="Submit">
</form>
</div>


</body>
</html>
