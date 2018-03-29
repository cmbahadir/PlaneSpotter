<?php

	include("connect.php"); 	
	
	$link=Connection();
	session_start();

	$result=mysql_query("SELECT * FROM `ADSBDATA`WHERE LAT!='0' OR LON!='0' and SQUAWK!='0' ORDER BY `timeStamp` DESC",$link);
	$lat1=mysql_query("SELECT LAT FROM `ADSBDATA`where LAT!=0 or LON!=0 ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$lon1=mysql_query("SELECT LON FROM `ADSBDATA` WHERE LAT!=0 or LON!=0 ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$modes1=mysql_query("SELECT HEX FROM `ADSBDATA` where LAT!=0 or LON!=0 ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$flight1=mysql_query("SELECT FLIGHT FROM `ADSBDATA` where LAT!=0 or LON!=0 ORDER BY `timeStamp` DESC LIMIT 1",$link);
	$lat = mysql_fetch_array($lat1);
	$lon = mysql_fetch_array($lon1);
	$modes = mysql_fetch_array($modes1);
	$indent = mysql_fetch_array($flight1);
?>

<html>
   <head>
      <title>ADS-B</title>
		<style>
			body {
  				padding: 1rem;
				margin: 5px;
			}
			#izmir_adsb {
				width:50%;
				height:50em;
				float:left;
				border-radius: 10px;
			}
			#tab{
				width:48%;
				cursor:pointer;
				border:0.5px solid black;
				border-collapse:collapse;
				border-radius: 10px;
				overflow-y: auto;
				float:right;
			}
			table {
            	width:50%;
				height:100rem;
            	border-collapse: collapse;
			}
			td, th {
  				width: 15rem;
  				height: 2rem;
  				border: 1px solid #ccc;
  				text-align: center;
				cursor:pointer;
			}
			#go_button{
		    	color:#08233e;
		    	font:2.4em Futura, ‘Century Gothic’, AppleGothic, sans-serif;
		    	font-size:90%;
		    	padding:14px;
		    	background-color:rgba(135,206,250,1);
		    	border:1px solid #000080;
		    	border-radius:10px;
		    	border-bottom:1px solid #9f9f9f;
		    	box-shadow:inset 0 1px 0 rgba(255,255,255,0.5);
		    	cursor:pointer;
		    	display:block;
		    	width:48%;
				float:right;
				margin-bottom: 0.5cm;
			}
			#header{
				text-align:center;
				font-family: "Times New Roman", Times, serif;
			}
		</style>
	  	<script src="http://maps.googleapis.com/maps/api/js"></script>
	   <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.5.2/jquery.min.js"></script>
		<script type="text/javascript">	
			
		var fxml_url = 'http://cmbahadir:pass@flightxml.flightaware.com/json/FlightXML2/';	
		var ident = "<?php echo $indent[0] ?>";
		console.log(ident);
			
		var lat = "<?php echo $lat[0] ?>";
		console.log(lat);
		var lon = "<?php echo $lon[0] ?>";
		console.log(lon);
		var modes = "<?php echo $modes[0] ?>";
		console.log(modes);

		var contentString = String(ident);
			
		$(document).ready(function() {
			$('#go_button').click(function() {
			$.ajax({
				type: 'GET',
				url: fxml_url + 'FlightInfoEx',
				data: { 'ident': ident, 'howMany': 10, 'offset': 0 },
				success : function(result) {
					if (result.error) {
						console.log(ident);
						alert('Failed to fetch flight: ' + result.error);
						return;
					}
					for (flight of result.FlightInfoExResult.flights) {
						if (flight.actualdeparturetime > 0) {
							// display some textual details about the flight.
							$('#results').html('Flight ' + flight.ident + ' from ' + flight.origin + ' to ' + flight.destination);
							console.log(flight.origin);
							return;
						}
					}
					alert('Did not find any useful flights');
				},
				error: function(data, text) { alert('Failed to fetch flight: ' + data); },
				dataType: 'jsonp',
				jsonp: 'jsonp_callback',
				xhrFields: { withCredentials: true }
				});
			});
		});
		
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
			
		function makeTableScroll() {
           	// Constant retrieved from server-side via JSP
           	var maxRows = 10;
           	var table = document.getElementById('adsbdata_table');
           	var wrapper = table.parentNode;
           	var rowsInTable = table.rows.length;
           	var height = 0;
           	if (rowsInTable > maxRows) {
           	    for (var i = 0; i < maxRows; i++) {
           	        height += table.rows[i].clientHeight;
           	    }
           	    wrapper.style.height = height + "px";
           	}
        }
	</script> 
</head>
   
<body onload="makeTableScroll();">
   <h1 id="header">ADS-B Receiver by CMB</h1>
	
		<div id="izmir_adsb"></div>
	
		<div id="tablevebuton">
			
			<div id="button">
    			<input type="submit" id="go_button" value="Show Last Flight Destination">
			</div>
	
			<div id="tab" class="adsbdata">
   				<table id="adsbdata_table" border="1" cellspacing="1" cellpadding="1">
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
	  						</table>
	  			</div>
		</div>
	<script>google.maps.event.addDomListener(window, 'load', initialize(lat,lon));</script>
</body>	
</html>

