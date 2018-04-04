<?php
   	include("connect.php");
   	
   	$link=Connection();

	$hex=$_POST["hex"];
	$squawk=$_POST["squawk"];
	$flight=$_POST["flight"];
	$altitude=$_POST["altitude"];
	$speed=$_POST["speed"];
	$heading=$_POST["heading"];
	$lat=$_POST["lat"];
	$lon=$_POST["lon"];
	$track=$_POST["track"];
	$messages=$_POST["messages"];
	$seen=$_POST["seen"];

	$query = "INSERT INTO `ADSBDATA` (`HEX`,`SQUAWK`, `FLIGHT`, `ALTITUDE`,`SPEED`,`HEADING`, `LAT`,`LON`,`TRACK`,`MESSAGES`,`SEEN`) 
		VALUES ('".$hex."','".$squawk."','".$flight."','".$altitude."','".$speed."','".$heading."','".$lat."','".$lon."','".$track."','".$messages."','".$seen."')"; 
   	
   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
