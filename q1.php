<?php
	$X = "6876766832351765396496377534476050002970857483815262918450355869850085167053394672634315391224052153";
	$XY = $_GET["key"];
	include "util.php";
	echo bcdiv($XY, $X)."\n";
	echo $team_id.",".$aws_account_id[0].",".$aws_account_id[1].",".$aws_account_id[2]."\n";
	echo date('Y-m-d H:i:s')."\n";
?>
