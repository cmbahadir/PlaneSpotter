/*http://stackoverflow.com/questions/16338774/show-a-moving-marker-on-the-map*/

/*var counter = 0;
interval = window.setInterval(function() { 
  counter++;
  // just pretend you were doing a real calculation of
  // new position along the complex path
  var pos = new google.maps.LatLng(35, -110 + counter / 100);
  marker.setPosition(pos);
  if (counter >= 1000) {
    window.clearInterval(interval);   
  }
}, 10);*/

var isOpen = false;
var deviceID;
var accountID;
var displayNameOfVehicle;
var maps = {};
var lt_markers = {};
var lt_polyLine = {};
function drawMap(jsonData, mapObj, device, deleteMarker) {
    var oldposition = null;
    var oldimage = null;
    var arrayOflatLng = [];

    var lat = jsonData[0].latitude;
    var lng = jsonData[0].longitude;
    //alert(jsonData[0].imagePath);

    var myLatLng = new google.maps.LatLng(lat, lng);

    if (deleteMarker == true) {
        if (lt_markers["marker" + device] != null) {
            oldimage = lt_markers["marker" + device].getIcon().url;
            oldposition = lt_markers["marker" + device].getPosition();
            lt_markers["marker" + device].setMap(null);
            lt_markers["marker" + device] = null;
        }
        else {
            console.log('marker is null');
            oldimage = new google.maps.MarkerImage(jsonData[0].imagePath,
                                                     null,
                                                     null,
                                                      new google.maps.Point(5, 17), //(15,27),
                                                     new google.maps.Size(30, 30));
            oldposition = myLatLng;
        }
    }


    var image = new google.maps.MarkerImage(jsonData[0].imagePath,
                                                     null,
                                                     null,
                                                      new google.maps.Point(5, 17), //(15,27),
                                                     new google.maps.Size(30, 30));
    lt_markers["marker" + device] = new google.maps.Marker({
        position: myLatLng,
        icon: image,
        title: jsonData[0].address
    });
    if (oldposition == myLatLng) {
        alert('it is same');
        lt_markers["marker" + device].setMap(mapObj);
        mapObj.panTo(myLatLng);
    }
    else {
        alert('it is not same');
        var markMarker = null;
        var i = 10;
        for (i = 10; i <= 100; i + 10) {
            //-------
            //  setTimeout(function() {
            if (markMarker != null) {
                markMarker.setMap(null);
                markMarker = null;
            }
            alert('inside the loop');
            var intermediatelatlng = mercatorInterpolate(mapObj, oldposition, myLatLng, i / 100);
            alert('Intermediate Latlng is :' + intermediatelatlng);
            arrayOflatLng.push(intermediatelatlng);

            var flightPath = new google.maps.Polyline({
                path: arrayOflatLng,
                strokeColor: "#FFFFFF",
                strokeOpacity: 1.0,
                strokeWeight: 1
            });
            flightPath.setMap(mapObj);
            if (i != 100) {
                markMarker = new google.maps.Marker({
                    position: intermediatelatlng,
                    icon: image,
                    title: jsonData[0].address,
                    map: mapObj
                });

            }
            else {
                markMarker = new google.maps.Marker({
                    position: intermediatelatlng,
                    icon: oldimage,
                    title: jsonData[0].address,
                    map: mapObj
                });                
            }
            mapObj.panTo(intermediatelatlng);
            //--------
            //   }, 1000);
        }
    }

}
function mercatorInterpolate(map, latLngFrom, latLngTo, fraction) {
    // Get projected points
    var projection = map.getProjection();
    var pointFrom = projection.fromLatLngToPoint(latLngFrom);
    var pointTo = projection.fromLatLngToPoint(latLngTo);
    // Adjust for lines that cross the 180 meridian
    if (Math.abs(pointTo.x - pointFrom.x) > 128) {
        if (pointTo.x > pointFrom.x)
            pointTo.x -= 256;
        else
            pointTo.x += 256;
    }
    // Calculate point between
    var x = pointFrom.x + (pointTo.x - pointFrom.x) * fraction;
    var y = pointFrom.y + (pointTo.y - pointFrom.y) * fraction;
    var pointBetween = new google.maps.Point(x, y);
    // Project back to lat/lng
    var latLngBetween = projection.fromPointToLatLng(pointBetween);
    return latLngBetween;
}