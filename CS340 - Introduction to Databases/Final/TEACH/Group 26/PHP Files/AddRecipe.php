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
  <form action="BuildRecipe.php" method="post">
    <label for="Stepnum">How Many Steps will Be Needed</label>
	<p>
	</p>
	<select name="Stepnum" id="Stepnum">
		<option value = "0" selected = "selected">Number of Steps...</option>
		<option value = "1" >1 Step</option>
		<option value = "2" >2 Steps</option>
		<option value = "3" >3 Steps</option>
		<option value = "4" >4 Steps</option>
		<option value = "5" >5 Steps</option>
		<option value = "6" >6 Steps</option>
		<option value = "7" >7 Steps</option>
		<option value = "8" >8 Steps</option>
		<option value = "9" >9 Steps</option>
		<option value = "10" >10 Steps</option>
	</select>
	<? 
    $Stepnum = $_POST['Stepnum'];
	echo $Stepnum;
	?>    
    <input type="submit" value="Submit">
  </form>
</div>


<!-- end Style-->
<? 
    include("footer.php");
?>
</html>