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
<div>
<?php

$error=''; // Variable To Store Error Message
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

$Stepnum=$_POST['Stepnum'];
if ($Stepnum == 0) {
echo "please retry with a valid number of steps.";
} else{
?>
<form action="SubmitRecipefixed.php?numstepsagain=<?php echo $Stepnum; ?>" method="post">
		<label for="Rname">Recipe Name:</label>
		<p>
			</p>
			<input type="text" id="Rname" name="Rname" placeholder="Enter Recipe Name...">

	<!-- Step 1 -->
	<?php if($Stepnum >= 1) {?>
	<br />
	<br />
		<label for="Step1">Step 1:</label>
		<p>
			</p>
			<input type="text" id="Step1" name="Step1" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		
		<br />
		<span class="tab"></span><label for="Iname1">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname1" id="Iname1">
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
			<br />
		<span class="tab"></span><label for="ingredamount1">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount1" name="ingredamount1" placeholder="1...">
	<?php } ?>
	<!-- End Step 1 -->	
	<!-- Step 2 -->
	<?php if($Stepnum >= 2) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>		<br />
		<label for="Step2">Step 2:</label>
		
		<p>
			</p>
			<input type="text" id="Step2" name="Step2" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname2">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname2" id="Iname2">
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
			<br />
		<span class="tab"></span><label for="ingredamount2">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount2" name="ingredamount2" placeholder="2...">
	<?php } ?>
	<!-- End Step 2 -->	
	<!-- Step 3 -->
	<?php if($Stepnum >= 3) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>			<br />
		<label for="Step3">Step 3:</label>
		<p>
			</p>
			<input type="text" id="Step3" name="Step3" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname3">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname3" id="Iname3">
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
			<br />
		<span class="tab"></span><label for="ingredamount3">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount3" name="ingredamount3" placeholder="3...">
	<?php } ?>
	<!-- End Step 3 -->	
	<!-- Step 4 -->
	<?php if($Stepnum >= 4) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>		<br />
		<label for="Step4">Step 4:</label>
		<p>
			</p>
			<input type="text" id="Step4" name="Step4" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname4">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname4" id="Iname4">
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
			<br />
		<span class="tab"></span><label for="ingredamount4">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount4" name="ingredamount4" placeholder="4...">
	<?php } ?>
	<!-- End Step 4 -->	
	<!-- Step 5 -->
	<?php if($Stepnum >= 5) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>
		<label for="Step5">Step 5:</label>
		<p>
			</p>
			<input type="text" id="Step5" name="Step5" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname5">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname5" id="Iname5">
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
			<br />
		<span class="tab"></span><label for="ingredamount5">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount5" name="ingredamount5" placeholder="5...">
	<?php } ?>
	<!-- End Step 5 -->	
	<!-- Step 6 -->
	<?php if($Stepnum >= 6) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>  	<br />
		<label for="Step6">Step 6:</label>
		<p>
			</p>
			<input type="text" id="Step6" name="Step6" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname6">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname6" id="Iname6">
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
			<br />
		<span class="tab"></span><label for="ingredamount6">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount6" name="ingredamount6" placeholder="6...">
	<?php } ?>
	<!-- End Step 6 -->	
	<!-- Step 7 -->
	<?php if($Stepnum >= 7) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>		<br />
		<label for="Step7">Step 7:</label>
		<p>
			</p>
			<input type="text" id="Step7" name="Step7" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname7">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname7" id="Iname7">
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
			<br />
		<span class="tab"></span><label for="ingredamount7">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount7" name="ingredamount7" placeholder="7...">
	<?php } ?>
	<!-- End Step 7 -->	
	<!-- Step 8 -->
	<?php if($Stepnum >= 8) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>		<br />
		<label for="Step8">Step 8:</label>
		<p>
			</p>
			<input type="text" id="Step8" name="Step8" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname8">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname8" id="Iname8">
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
			<br />
		<span class="tab"></span><label for="ingredamount8">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount8" name="ingredamount8" placeholder="8...">
	<?php } ?>
	<!-- End Step 8 -->	
	<!-- Step 9 -->
	<?php if($Stepnum >= 9) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>		<br />
		<label for="Step9">Step 9:</label>
		<p>
			</p>
			<input type="text" id="Step9" name="Step9" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname9">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname9" id="Iname9">
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
			<br />
		<span class="tab"></span><label for="ingredamount9">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount9" name="ingredamount9" placeholder="9...">
	<?php } ?>
	<!-- End Step 9 -->	
	<!-- Step 10 -->
	<?php if($Stepnum >= 10) {
		$query = "select Ingredient_name from INGREDIENT";
		$result = mysqli_query($conn, $query);
		if (!$result) {
			die("Query to show fields from table failed");
		}
?>		<br />
		<label for="Step10">Step 10:</label>
		<p>
			</p>
			<input type="text" id="Step10" name="Step10" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Iname10">Ingredient (If none, select nothing from dropdown)</label>
		<br />
			<span class="tab"></span><select name="Iname10" id="Iname10">
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
			<br />
		<span class="tab"></span><label for="ingredamount10">Amount of Ingredient (in ounces):</label>
		<p>
			</p>
		<span class="tab"></span><input type="text" id="ingredamount10" name="ingredamount10" placeholder="10...">
	<?php } ?>
	<!-- End Step 10 -->	
	
	<input type="submit" value="Submit">

</form>
<?php
}
?>
</div>
</html>