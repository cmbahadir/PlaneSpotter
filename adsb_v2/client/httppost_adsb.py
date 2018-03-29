import urllib2 
import urllib
import time
import sys
from subprocess import Popen, PIPE, STDOUT

sys.stdout.flush()
time.sleep(0.5)
cmd='/home/pi/dump1090/dump_interactive.sh'
p=Popen(cmd, shell=False, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
time.sleep(0.5)

while True:
	u = None
	u = p.stdout.readline()
	hex=u[7:13]
	print "hex:", hex
	squawk=u[15:18]
	print "squawk:", squawk
	flight=u[27:33]
	print "flight:",flight
	altitude=u[36:41]
	print "altitude:", altitude
	speed=u[43:46]
	print "speed:", speed
	heading=u[48:51]
	print "heading:", heading
	lat=u[51:60]
	print "lat:", lat
	lon=u[62:69]
	print "lon:", lon
	track=u[70:72]
	print "track:", track
	messages=u[72:74]
	print "messages:", messages
	print messages
	seen=u[77:80]
	headers = {'User-Agent' : 'Mozilla/5.0' }
	receiveddata=u.strip()

	print "------------------RECEIVED ADSB DATA-----------------"

	print receiveddata
	print "\n"

	query_args = { 
		'hex':hex,
		'squawk':squawk,
		'flight':flight,
		'altitude':altitude,
		'speed':speed,
		'heading':heading,
		'lat':lat,
		'lon':lon,
		'track':track,
		'messages':messages,
		'seen':seen
		}
 
	url = 'http://www.selftronics.com/add.php'
 
	data = urllib.urlencode(query_args)
 
	if not messages:
		exit
	else:
		request = urllib2.Request(url, data, headers);
		response = urllib2.urlopen(request).read();

		print "--------------REQUEST-------------------\n"
		print request
		print "\n"


		print "--------------RESPONSE------------------\n"
		print response
		print "\n"
