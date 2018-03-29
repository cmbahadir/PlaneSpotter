<?php
   	include("connect.php");
   	
   	$link=Connection();

	

	/*$hex1 = isset($_POST['hex1']) ? $_POST['hex1'] : '';
	$hex1 = !empty($_POST['hex1']) ? $_POST['hex1'] : '';
	
	$flight1 = isset($_POST['flight1']) ? $_POST['flight1'] : '';
	$flight1 = !empty($_POST['flight1']) ? $_POST['flight1'] : '';
	
	$altitude1 = isset($_POST['altitude1']) ? $_POST['altitude1'] : '';
	$altitude1 = !empty($_POST['altitude1']) ? $_POST['altitude1'] : '';
	
	$speed1 = isset($_POST['speed1']) ? $_POST['speed1'] : '';
	$speed1 = !empty($_POST['speed1']) ? $_POST['speed1'] : '';
	
	$lat1 = isset($_POST['lat1']) ? $_POST['lat1'] : '';
	$lat1 = !empty($_POST['lat1']) ? $_POST['lat1'] : '';
	
	$lon1 = isset($_POST['lon1']) ? $_POST['lon1'] : '';
	$lon1 = !empty($_POST['lon1']) ? $_POST['lon1'] : '';
	
	$track1 = isset($_POST['track1']) ? $_POST['track1'] : '';
	$track1 = !empty($_POST['track1']) ? $_POST['track1'] : '';
	
	$messages1 = isset($_POST['messages1']) ? $_POST['messages1'] : '';
	$messages1 = !empty($_POST['messages1']) ? $_POST['messages1'] : '';
	
	$seen1 = isset($_POST['seen1']) ? $_POST['seen1'] : '';
	$seen1 = !empty($_POST['seen1']) ? $_POST['seen1'] : '';*/


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