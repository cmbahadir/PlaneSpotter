<!DOCTYPE html>
<html>
	<link rel="stylesheet" href="style/style.css">
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.5.2/jquery.min.js"></script>
	<script type="text/javascript" src="js/source.js"></script>
	<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCST44SST5iTCxqz8CidH4ciquIVUhMVDA&callback=initMap" type="text/javascript"></script>
	<head>
      <title>ADS-B</title>
	</head>
	<body>
		<h1 id="header">ADS-B Receiver by CMB</h1>
                <div id="izmir_adsb"></div>
                <div id="tablevebuton">
                        <div id="button">
							<input type="submit" id="go_button" value="Show Last Flight Destination">
                        </div>
						
						<div id="aircraftimage">
                             <img id="myImage" onload="changeImage()" src="/img/question_mark.png" width="180" height="45">
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
                                                        $row["Date"], 
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
                <script>google.maps.event.addDomListener(window, 'load', initMap(lat,lon));</script>
	</body>
</html>
