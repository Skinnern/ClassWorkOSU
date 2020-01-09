<? session_start(); ?>
<!DOCTYPE html>
<html>
	<head>
		<style type=”text/css”>

		table {
			border-collapse: collapse;
			width: 100%;
		}

		th, td {
			padding: 8px;
			text-align: left;
			border-bottom: 1px solid #ddd;
		}

		tr:hover{background-color:#f5f5f5}
	</style>
	</head>
	<body>

<h2>Recipes</h2>
<?php
include 'connectvarsEECS.php'; 
	$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
	if (!$conn) {
		die('Could not connect: ' . mysql_error());
	}
	echo "<h1>List of the most popular user recipes.</h1>";

echo "<table id='t01' border='1'><tr>";
	for($i=0; $i<$fields_num; $i++) {	
		$field = mysqli_fetch_field($result);	
		echo "<th><b>$field->name</b></th>";
	}
	echo "</tr>\n";
	while($row = mysqli_fetch_row($result)) {	
		echo "<tr>";	
		// $row is array... foreach( .. ) puts every element
		// of $row to $cell variable	
		foreach($row as $cell)		
			echo "<td>$cell</td>";	
		echo "</tr>\n";
	}
?>
</body>
</html>
