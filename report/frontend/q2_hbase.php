<?php
	include "util.php";
	echo $team_id.",".$aws_account_id[0].",".$aws_account_id[1].",".$aws_account_id[2]."\n";
	$tweet_time = $_GET["tweet_time"];

	$url = "http://localhost:1025/tweet/".$_GET["userid"]."_".str_replace(" ", "%20", $_GET["tweet_time"])."_*";
	$opts = array(
		'http'=>array(
			'method'=>"GET",
			'header'=> "Accept: application/json\r\n"
		)
	);
	$context = stream_context_create($opts);
	$file = file_get_contents($url, false, $context);

	$result = json_decode($file);
	foreach ($result->Row as $row)
	{
		$column = array();
		foreach ($row->Cell as $cell)
		{
			$column[base64_decode($cell->{'column'})] = base64_decode($cell->{'$'});
		}
		echo $column["tweet_id:"].":".$column["sentiment:"].":".$column["text:"]."\n";
	}
?>
