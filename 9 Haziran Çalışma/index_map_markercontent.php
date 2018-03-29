<?php

	include("connect.php"); 	
	
	$link=Connection();
	session_start();

	$result=mysql_query("SELECT * FROM `ADSBDATA` ORDER BY `timeStamp` DESC",$link);
	$lat1=mysql_query("SELECT LAT FROM `ADSBDATA` ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$lon1=mysql_query("SELECT LON FROM `ADSBDATA` ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$modes1=mysql_query("SELECT HEX FROM `ADSBDATA` ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$lat = mysql_fetch_array($lat1);
	$lon = mysql_fetch_array($lon1);
	$modes = mysql_fetch_array($modes1);
?>

<html>
   <head>
      <title>ADS-B</title>
		<style>
			td, th {
  			width: 8rem;
  			height: 2rem;
  			border: 1px solid #ccc;
  			text-align: center;
			}
			th {
  			background: lightblue;
  			border-color: white;
			}
			body {
  			padding: 1rem;
			margin: 5px;
			}
		</style>
   </head>
   
<body>
   <h1>ADS-B Receiver by CMB</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp;</td>
			<td>&nbsp;Hex&nbsp;</td>
			<td>&nbsp;Squawk&nbsp;</td>
			<td>&nbsp;Flight&nbsp;</td>
			<td>&nbsp;Altitude&nbsp;</td>
			<td>&nbsp;Speed&nbsp;</td>
			<td>&nbsp;Heading&nbsp;</td>
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
				<td> &nbsp;%s&nbsp;</td>
				<td> &nbsp;%s&nbsp;</td>
				</tr>",  
		           $row["timeStamp"], 
				   $row["HEX"],
				   $row["SQUAWK"],
				   $row["FLIGHT"],
				   $row["ALTITUDE"],
				   $row["SPEED"],
				   $row["HEADING"],
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
	  
	  	<div id="izmir_adsb" style="width:500px;height:380px;"></div>

	  	<script src="http://maps.googleapis.com/maps/api/js"></script>
		<script type="text/javascript">
			
		var lat = "<?php echo $lat[0] ?>";
		console.log(lat);
		var lon = "<?php echo $lon[0] ?>";
		console.log(lon);
		var modes = "<?php echo $modes[0] ?>";
		console.log(modes);
		var contentString = String(modes);
			
		function initialize(lat,lon) {
		    var location = new google.maps.LatLng(lat,lon);
		    var mapCanvas = document.getElementById('izmir_adsb');
		    var map_options = {
		      center: location,
		      zoom: 9,
		      mapTypeId: google.maps.MapTypeId.ROADMAP
		    }
			
		    var map = new google.maps.Map(mapCanvas, map_options);
			
			var infowindow = new google.maps.InfoWindow({
    						 content: contentString
  			});
		
		    var marker = new google.maps.Marker({
		        position: location,
		        map: map,
				icon: 'http://icons.iconarchive.com/icons/unclebob/spanish-travel/16/plane-icon.png'
		    });
			
			marker.addListener('click', function() {
    		infowindow.open(map, marker);
  			});	
			
		}
				
		google.maps.event.addDomListener(window, 'load', initialize(lat,lon));
		</script>
	   
   </table>
</body>	
</html>

