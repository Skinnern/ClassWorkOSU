<?php session_start(); ?>
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
echo "<h1>Frequently Asked Questions</h1>";
echo "<h2>Here is where We would place the Questions we were frequently asked, if we had any.</h2>";

echo '<a href="About.php">About Us</a>';
echo "\n";
echo '<a href="Contact.php">Contact us</a>';
?>
<? 
    include("footer.php");
?>
</html>
