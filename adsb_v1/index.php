<?php

	include("connect.php"); 	
	
	$link=Connection();

	$result=mysql_query("SELECT * FROM `ADSBDATA` ORDER BY `timeStamp` DESC",$link);
?>

<html>
   <head>
      <title>ADS-B</title>
   </head>
<body>
   <h1>ADS-B Receiver by CMB</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp;</td>
			<td>&nbsp;Hex&nbsp;</td>
			<td>&nbsp;Flight&nbsp;</td>
			<td>&nbsp;Altitude&nbsp;</td>
			<td>&nbsp;Speed&nbsp;</td>
			<td>&nbsp;Latitude&nbsp;</td>
			<td>&nbsp;Longtitude&nbsp;</td>
			<td>&nbsp;Track&nbsp;</td>
			<td>&nbsp;Messages&nbsp;</td>
			<td>&nbsp;Seen&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysql_fetch_array($result)) {
		        printf("<tr>
				<td> &nbsp;%s </td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				</tr>",  
		           $row["timeStamp"], 
				   $row["HEX"],
				   $row["FLIGHT"],
				   $row["ALTITUDE"],
				   $row["SPEED"],
				   $row["LAT"],
				   $row["LON"],
				   $row["TRACK"],
				   $row["MESSAGES"],
				   $row["SEEN"]
				   );
		     }
		     mysql_free_result($result);
		     mysql_close();
		  }
      ?>

   </table>
</body>
</html>