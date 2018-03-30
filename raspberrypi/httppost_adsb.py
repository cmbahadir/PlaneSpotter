
import urllib2 
import urllib
import time
import sys
from array import *
from subprocess import Popen, PIPE, STDOUT

sys.stdout.flush()
time.sleep(0.5)
cmd='/home/pi/dump1090/dump_interactive.sh'
p=Popen(cmd, shell=False, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
time.sleep(0.5)
i=0
list=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
logfile=open('/home/pi/adsb_log/adsblog.log','a')
logfile.write("Hex     Mode  Sqwk  Flight   Alt    Spd  Hdg    Lat      Long   Sig  Msgs   Ti\n")

while True:
	u = None
	u = p.stdout.readline()
	hex=u[7:13]
	print "hex:", hex
	squawk=u[21:25]
	print "squawk:", squawk
	flight=u[27:33]
	print "flight:",flight
	altitude=u[36:41]
	print "altitude:", altitude
	speed=u[43:46]
	print "speed:", speed
	heading=u[48:51]
	print "heading:", heading
	lat=u[53:60]
	print "lat:", lat
	lon=u[62:69]
	print "lon:", lon
	track=u[71:74]
	print "track:", track
	messages=u[77:81]
	print "messages:", messages
	seen=u[84:85]
	headers = {'User-Agent' : 'Mozilla/5.0' }
	receiveddata=u.strip()

	list[i]=messages

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
 
	#url = 'http://www.selftronics.com/add.php'
    	url = 'http://localhost/add.php'
	data = urllib.urlencode(query_args)
	print 'squawk:',squawk
	 
	if not messages:
		exit
	else:
		if track in ['rtl'] or not squawk or list[i+1]==list[i]:
		        exit
		elif i==15:
			i=0
		else:
			request = urllib2.Request(url, data, headers);
			response = urllib2.urlopen(request).read();

			print "--------------REQUEST-------------------\n"
			print data
			print "\n"


			#print "--------------RESPONSE------------------\n"
			#print response
			#print "\n"

			i=i+1  ##incremention of the index

			logtime = time.strftime("%H:%M:%S") ##Getting the systemtime for logging
        	        logfile.write(logtime)
                	logfile.write(":")
	                logfile.write(data)
        	        logfile.write("\n")

logfile.close()
