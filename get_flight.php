 <?php
    	include("connect.php"); 
    	$link=Connection();
	//session_start();

    	$result=mysql_query("SELECT * FROM `ADSBDATA`WHERE LAT!='0' OR LON!='0' and SQUAWK!='0' ORDER BY `Date` DESC",$link);
	$rows = array();
	while($r = mysql_fetch_assoc($result)) {
		$rows[] = $r;
	}
	echo json_encode($rows);
?>
