var fxml_url = 'https://cmbahadir:pass@flightxml.flightaware.com/json/FlightXML2/';
var flights = null;
var lat = null;
var lon = null;
var ident = null;

$(document).ready(function()
{
	        $.ajax({
			type: 'GET',
        	        url: '../get_flight.php',
	                async: true,
                	success: function(response){
	                        console.log(response);
				flights = JSON.parse(response);
				ident = flights[0].FLIGHT;
			    	lat = flights[0].LAT;
				lon = flights[0].LON;
        	        }               
        	});
	
});

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
                        alert('No flight returned from flightaware...');
                },
                error: function(data, text) { alert('Server error failed to fetch flight: ' + data); },
                dataType: 'jsonp',
                jsonp: 'jsonp_callback',
                xhrFields: { withCredentials: true }
                });
        });
});

function initMap(lat,lon) {
    var planeIcon = new google.maps.MarkerImage(
        "/img/plane_generic.png",
        null, /* size is determined at runtime */
        null, /* origin is 0,0 */
        null, /* anchor is bottom center of the scaled image */
        new google.maps.Size(42, 42));
		
	if (lat != null && lon !=null)
	{
		var location = new google.maps.LatLng(lat,lon);
	}
	else
	{
		var location = "{lat: -34.397, lng: 150.644}";
	}
    
    var mapCanvas = document.getElementById('izmir_adsb');
	
    var map_options = {
      center: location,
      zoom: 11,
      mapTypeId: google.maps.MapTypeId.ROADMAP,
      zoomControl: false
    }

    var map = new google.maps.Map(mapCanvas, map_options);
    var infowindow = new google.maps.InfoWindow(
	{
    	content: ident
	});

    var marker = new google.maps.Marker({
                         position: location,
                         map: map,
                                 icon: planeIcon
                                 });

	marker.addListener('click', function() {
		infowindow.open(map, marker);
    });
}


function changeImage() {
        var image = document.getElementById('myImage');
                if (ident.indexOf("PGT") > -1) {
                        image.src = "/img/A319large.png";
                } 
                else if (ident.indexOf("SX") > -1) {
                        image.src = "/img/A319large.png";
                } 
                else if (ident.indexOf("TK") > -1) {
                        image.src = "/img/A319large.png";
                } 
                else {
                        image.src = "/img/A319large.png";
                }
}

function makeTableScroll()
{
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
