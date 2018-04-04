var fxml_url = 'https://cmbahadir:pass@flightxml.flightaware.com/json/FlightXML2/';
var flights = null;
var lat = null;
var lon = null;
var ident = null;


function getFlight(callback)
{
    $.ajax({
    type: 'GET',
    url: '../get_flight.php',
    success: function(response){
            callback(response);
        }       
    }); 
}

function getResponse(){
    getFlight(function(d){
        flights = JSON.parse(d);
        ident = flights[0].FLIGHT;
        lat = flights[0].LAT;
        lon = flights[0].LON;
	changeImage();
        initMap(lat,lon);
	insertIntoTable();
    });
}


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
        new google.maps.Size(20,20),
        null, /* origin is 0,0 */
        null, /* anchor is bottom center of the scaled image */
        new google.maps.Size(20,20)
	);
		
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
    
    map.addListener('zoom_changed', function() {
	console.log("zoom changed to:" + map.getZoom());	
	var zoom = map.getZoom();
	var relative = (zoom < 9) ? 15 : (100/zoom);
	console.log("relative" + relative);	
	marker.setIcon(
		new google.maps.MarkerImage(
			"/img/plane_generic.png",
			null,
			null,
			null,
			new google.maps.Size(relative,relative)
    		));
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

function insertIntoTable()
{
	var part = document.getElementById("flightdata");
	var headrow = part.insertRow(0);
       	headrow.insertCell(0).innerText = "Time";
        headrow.insertCell(1).innerText = "Hex Code";
        headrow.insertCell(2).innerText = "Squawk";
        headrow.insertCell(3).innerText = "Flight";
        headrow.insertCell(4).innerText = "Altitude";
        headrow.insertCell(5).innerText = "Speed";
        headrow.insertCell(6).innerText = "Heading";
        headrow.insertCell(7).innerText = "Lattitude";
        headrow.insertCell(8).innerText = "Longtitude";
        headrow.insertCell(9).innerText = "Track";
        headrow.insertCell(10).innerText = "Messages";
        headrow.insertCell(11).innerText = "Seen";
	if (flights.length > 0)
	{
	for(a=0; a<flights.length; a++)
	{
		var datarow = part.insertRow(a+1);
		datarow.insertCell(0).innerText = flights[a].Date;
		datarow.insertCell(1).innerText = flights[a].HEX;
		datarow.insertCell(2).innerText = flights[a].SQUAWK;
		datarow.insertCell(3).innerText = flights[a].FLIGHT;
		datarow.insertCell(4).innerText = flights[a].ALTITUDE;
		datarow.insertCell(5).innerText = flights[a].SPEED;
		datarow.insertCell(6).innerText = flights[a].HEADING;
		datarow.insertCell(7).innerText = flights[a].LAT;
		datarow.insertCell(8).innerText = flights[a].LON;
		datarow.insertCell(9).innerText = flights[a].TRACK;
		datarow.insertCell(10).innerText = flights[a].MESSAGES;
		datarow.insertCell(11).innerText = flights[a].SEEN;
	}
	}
}
