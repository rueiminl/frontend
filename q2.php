<?php
	$conn = new mysqli("localhost", "root", "wolken", "test");
	if ($conn->connect_error) 
	{
		die("Database connection failed: " . $conn->connect_error);
	}
	$conn->set_charset("utf8");
	echo "Wolken,5534-0848-5100,0299-6830-9164,4569-9487-7416\n";
	$result = mysqli_query($conn, "select tid, sentiment, text from tweet where uid=".$_GET["userid"]." and ts=\"".$_GET["tweet_time"]."\" order by tid");
	while($row = mysqli_fetch_array($result)) 
	{
		echo $row['tid'].":".$row['sentiment'].":".$row['text']."\n";
	}
?>
