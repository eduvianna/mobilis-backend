import requests
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
while True:
	read_serial = ser.readline()
	print read_serial
	#message = read_serial.split(':')

	#if(len(message) == 3):
	#	id = message[0]
	#	word = message[1]
	#	value = message[2]
	#	value = value.decode().strip()
	#	r = requests.post('http://localhost:3333/create-measurement', json={"sensor_id":id, "word": word, "value": value})
	#	print r.status_code
