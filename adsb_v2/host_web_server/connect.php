<?php

	function Connection(){
		$server="localhost:3306";
		$user="cmbahadir";
		$pass="kW8rb9!0";
		$db="adsb";
	   	
		$connection = mysql_connect($server, $user, $pass);

		if (!$connection) {
	    	die('MySQL ERROR: ' . mysql_error());
		}
		
		mysql_select_db($db) or die( 'MySQL ERROR: '. mysql_error() );

		return $connection;
	}
?>
