import serial
import requests

ser = serial.Serial('/dev/ttyACM0', 2400, timeout=120)

URL = "http://dummy:ipass@boezemail.nl:8123/json.htm"

while True:

	line = ser.readline().decode('ascii')

	if line == "1\n":
		PARAMS = {"type":"devices", "rid":12674}
		r = requests.get(url = URL, params = PARAMS)
		data = r.json()
		result = data['result'][0]['Data']
		ser.write(result.encode('ascii') + b"\n")
	if line == "2\n":
                PARAMS = {"type":"devices", "rid":7}
                r = requests.get(url = URL, params = PARAMS)
                data = r.json()
                result = data['result'][0]['Data']
                ser.write(result.encode('ascii') + b"\n")
	if line == "3\n":
                PARAMS = {"type":"devices", "rid":10}
                r = requests.get(url = URL, params = PARAMS)
                data = r.json()
                result = data['result'][0]['Data']
                ser.write(result.encode('ascii') + b"\n")
	if line == "4\n":
                PARAMS = {"type":"devices", "rid":8}
                r = requests.get(url = URL, params = PARAMS)
                data = r.json()
                result = data['result'][0]['Data']
                ser.write(result.encode('ascii') + b"\n")

	if line == "5\n":
                PARAMS = {"type":"devices", "rid":15}
                r = requests.get(url = URL, params = PARAMS)
                data = r.json()
                result = data['result'][0]['Data']
                ser.write(result.encode('ascii') + b"\n")
