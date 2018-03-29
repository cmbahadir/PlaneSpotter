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

##Logging File Creation##
with open('/home/pi/adsb_log/adsblog.log','a') as logfile:
	logfile.write("Hex     Mode  Sqwk  Flight   Alt    Spd  Hdg    Lat      Long   Sig  Msgs   Ti\n")

	while True:
	        u = p.stdout.readline()
		logtime = time.strftime("%H:%M:%S")
		logfile.write(logtime)
	        logfile.write(":")
		logfile.write(u)
		logfile.write("\n")
	        hex=u[7:13]
        	print "hex:", hex
	        flight=u[27:33]
        	print "flight:",flight
	        altitude=u[36:41]
        	print "altitude:", altitude
	        speed=u[43:46]
        	print "speed:", speed
	        lat=u[48:51]
        	print "lat:", lat
	        lon=u[51:60]
        	print lon
	        track=u[62:69]
        	print track
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
                'flight':flight,
                'altitude':altitude,
                'speed':speed,
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
	logfile.close
