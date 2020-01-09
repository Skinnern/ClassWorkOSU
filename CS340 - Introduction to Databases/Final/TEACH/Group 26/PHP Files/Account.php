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
<h2> Add new User</h2>
<form action="insertUser.php" method="post">
    <p>
        <label for="username">Username:</label>
		<p>
			</p>
        <input type="text" name="username" id="username"  placeholder="Username...">
    </p>
	   <p>
        <label for="email">Email:</label>
		<p>
			</p>
        <input type="text" name="email" id="email"  placeholder="Email...">
    </p>
	    <p>
        <label for="password">Password:</label>
		<p>
			</p>
        <input type="text" name="password" id="password"  placeholder="Password...">
    </p>
    <input type="submit" value="Submit">
</form>
</div>
</body>
</html>
