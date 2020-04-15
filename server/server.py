import requests
import serial
import serial.tools.list_ports


while True:
    ports = list(serial.tools.list_ports.comports())

    for port in ports:
        port = str(port)
        port = port.split('-')
        port[0] = port[0].strip()
        if 'ttyACM' in port[1]:

          ser = serial.Serial(port[0], 9600)

          read_serial = ser.readline()

          message = read_serial.split(':')

          if len(message) == 3:
              try:
                  id = message[0]
                  word = message[1]
                  value = message[2]
                  value = value.decode().strip()
                  r = \
                      requests.post('http://app-mobilis:3333/create-measurement'
                                    , json={'sensor_id': id, 'word': word,
                                    'value': value})
                  print r.status_code
              except requests.exceptions.ConnectionError:
                  print 'Connection refused'
