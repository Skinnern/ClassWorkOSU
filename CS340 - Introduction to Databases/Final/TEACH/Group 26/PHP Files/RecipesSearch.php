<?php session_start(); ?>
<!DOCTYPE html>
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
  <form action="SearchResults.php" method="post">
    <label for="Searchitem">Search for</label>
	<p>
	</p>
    <input type="text" id="Searchitem" name="Searchitem" placeholder="Item to search for...">
	<p>
	</p>
	<br />
    <label for="Locationof">Under</label>
	<p>
	</p>
	<select name="Locationof" id="Locationof">
		<option value = "0" selected = "selected">Select...</option>
		<option value = "1" >Recipes</option>
		<option value = "2" >Users</option>
		<option value = "3" >Ingredients</option>
		<option value = "4" >Costs</option>
	</select>
	<? 
    $Locationof = $_POST['Locationof'];
	echo $Locationof;
	?>
    

    
    <input type="submit" value="Submit">
  </form>
</div>


<!-- end Style-->
<? 
    include("footer.php");
?>
</html>