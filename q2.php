<?php
	include "pw.php";
	$servername = "localhost";
	$username = "root";
	$dbname = "test";

	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);

	// Check connection
	if ($conn->connect_error) 
	{
		die("Database connection failed: " . $conn->connect_error);
	}
	include "util.php";
	echo $team_id.",".$aws_account_id[0].",".$aws_account_id[1].",".$aws_account_id[2]."\n";
	$query = "select tid, sentiment, text from tweet where uid=".$_GET["userid"]." and ts=\"".str_replace("+", " ", $_GET["tweet_time"])."\" order by tid";
	$result = mysqli_query($conn, $query);
	while($row = mysqli_fetch_array($result)) 
	{
		echo $row['tid'].":".$row['sentiment'].":".$row['text']."\n";
	}
?>
