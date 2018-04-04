<!DOCTYPE html>
<html>
        <link rel="stylesheet"  href="https://v4-alpha.getbootstrap.com/dist/css/bootstrap.min.css">
        <link rel="stylesheet" href="style/style.css">
        <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.5.2/jquery.min.js"></script>
        <script type="text/javascript" src="js/source.js"></script>
        <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyCST44SST5iTCxqz8CidH4ciquIVUhMVDA" type="text/javascript"></script>
        <script>getResponse()</script>
	<head>
		  <title>ADS-B</title>
	</head>
	   
	<body>
		<div class="row">
			<div class="col-md-6">
				<div class="row">
						<div class="md-col-6 col-md-offset-5">
							<div id="button"><input type="submit" id="go_button" value="Show Last Flight Destination"></div>
						</div>
						<div class="md-col-6 col-md-offset-5">
							<div id="aircraftimage"><img id="myImage" src="/img/question_mark.png" width="180" height="45"></div>
						</div>
				</div>
				<div class="row">
					<div class="table-responsive"><table class="table" id="flightdata" border="1" cellspacing="1" cellpadding="1"></table></div>
				</div>
			</div>
			<div id="izmir_adsb" class="col-md-6"></div>
		</div>
	</body>
</html>
