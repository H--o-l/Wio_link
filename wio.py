# Import libraries for parsing the JSON output by the Wio Link
# Also import the Initial State Python library so we can stream
# the Wio Link readings to a visualization
import urllib2
import json
import os
import glob
import time
from ISStreamer.Streamer import Streamer

#### Wio Link Information ####
# The access token for your Wio Link
WIO_ACCESS_TOKEN = file("wio.token", "r").readline()[:-1] # "Wio_API_Access_Token_Here"

### Initial State Information ###
# The name your bucket will appear with in Initial State
BUCKET_NAME = ":seedling: Wio"
# The hidden bucket key that associates the data w/a particular bucket
BUCKET_KEY = file("bucket.token", "r").readline()[:-1] # "wiolink"
# Initial State access key - found under "Account"
IS_ACCESS_KEY = file("initial_state.token", "r").readline()[:-1] # "Initial_State_Access_Key_Here"

# Time between sensor readings
SLEEP_TIME_SEC = (5 * 60)

def get_reading(sensor,signal):
	# Function to fetch the JSON from a particular Wio API URL
	api_reading_url = "https://us.wio.seeed.io/v1/node/" + sensor + "/" + signal + "?access_token=" + WIO_ACCESS_TOKEN
	print api_reading_url
	f = urllib2.urlopen(api_reading_url)
	json_reading = f.read()
	f.close()
	return json.loads(json_reading)

def send_sleep(sleep_time_sec):
	api_reading_url = "https://us.wio.seeed.io/v1/node/pm/sleep/" + str(sleep_time_sec) + "?access_token=" + WIO_ACCESS_TOKEN
	print api_reading_url
	f = urllib2.urlopen(api_reading_url, "")
	json_reading = f.read()
	f.close()
	return json.loads(json_reading)
	

def read_and_send(sensor_name, sensor_type, sensor_return, display_name):
	reader = get_reading(sensor_name,sensor_type)
	if (reader != False):
		try:
			value = reader[sensor_return]
			print display_name + ": " + str(value)
			streamer.log(":fire: " + display_name,str(value))
		except KeyError:
			print "Error reading " + display_name + ": " + str(reader['error'])
			streamer.log("Error ",str(reader['error']))

def set_asleep(sleep_time_sec):
	reader = send_sleep(sleep_time_sec)
	if (reader != False):
		try:
			value = reader['result']
			streamer.log(":fire: Sleeping and init",'0')
			print "Wio set asleep for " + str(sleep_time_sec) + " sec: " + value
		except KeyError:
			print "Error in setting Wio asleep: " + reader['error']
			streamer.log("Error ",str(reader['error']))

def try_wakeup():
	while True:
		try:
			print "Try wio up"
			read_and_send('GroveAirqualityA0', 'quality', 'quality', 'Air quality')	
		except urllib2.HTTPError:
			print "Wio still sleeping"
			time.sleep(10)
			continue
		streamer.log(":fire: Sleeping and init",'1')
		break


if __name__ == '__main__':
	# Initialize the Intial State streamer
	streamer = Streamer(bucket_name=BUCKET_NAME, bucket_key=BUCKET_KEY, access_key=IS_ACCESS_KEY)
	print "streaming to {0}, {1}, {2}".format(BUCKET_NAME, BUCKET_KEY, IS_ACCESS_KEY)
	streamer.log(":fire: Sleeping and init",'2')
	# Loop through reading and streaming each signal's value
	while True:
		try: 
			try_wakeup()
			read_and_send('GroveAirqualityA0', 'quality', 'quality', 'Air quality')
			read_and_send('GroveAirqualityA0', 'quality', 'quality', 'Air quality')
			read_and_send('GroveDigitalLightI2C0', 'lux', 'lux', 'Light')
			read_and_send('GroveDigitalLightI2C0', 'lux', 'lux', 'Light')
			read_and_send('GroveTempHumD0', 'temperature', 'celsius_degree', 'Temperatue')
			read_and_send('GroveTempHumD0', 'humidity', 'humidity', 'Humidity')
			read_and_send('GroveTempHumD0', 'humidity', 'humidity', 'Humidity')
			set_asleep(SLEEP_TIME_SEC)
			time.sleep(SLEEP_TIME_SEC + 20)
			
		except KeyboardInterrupt:
			break
