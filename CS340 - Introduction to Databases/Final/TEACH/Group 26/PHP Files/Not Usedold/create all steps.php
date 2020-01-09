	<!-- Step 1 -->
	<?php if($Stepnum >= 1) {?>
		<label for="Step1">Step 1:</label>
		<p>
			</p>
			<input type="text" id="Step1" name="Step1" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step1" id="Step1">
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
	<?php if($Stepnum >= 2) {?>
		<label for="Step2">Step 2:</label>
		<p>
			</p>
			<input type="text" id="Step2" name="Step2" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step2" id="Step2">
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
	<?php if($Stepnum >= 3) {?>
		<label for="Step3">Step 3:</label>
		<p>
			</p>
			<input type="text" id="Step3" name="Step3" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step3" id="Step3">
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
	<?php if($Stepnum >= 4) {?>
		<label for="Step4">Step 4:</label>
		<p>
			</p>
			<input type="text" id="Step4" name="Step4" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step4" id="Step4">
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
	<?php if($Stepnum >= 5) {?>
		<label for="Step5">Step 5:</label>
		<p>
			</p>
			<input type="text" id="Step5" name="Step5" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step5" id="Step5">
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
	<?php if($Stepnum >= 6) {?>
		<label for="Step6">Step 6:</label>
		<p>
			</p>
			<input type="text" id="Step6" name="Step6" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step6" id="Step6">
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
	<?php if($Stepnum >= 7) {?>
		<label for="Step7">Step 7:</label>
		<p>
			</p>
			<input type="text" id="Step7" name="Step7" placeholder="Enter Step Instructions...">
		<!-- Dropdown -->
		<br />
		<span class="tab"></span><label for="Locationof">Ingredient (optional)</label>
		<br />
			<span class="tab"></span><select name="Step7" id="Step7">
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