#!/usr/bin/python
# -*- coding: utf-8 -*-
import requests
import serial
import serial.tools.list_ports

# ser = serial.Serial('dev/ttyACM0', 9600)

while True:
    ports = list(serial.tools.list_ports.comports())

    for p in ports:
        p = str(p)
        p = p.split('-')

        if 'ttyACM' in p[1]:
            print p

            read_serial = ser.readline()

            message = read_serial.split(':')

            if(len(message) == 3):
                id = message[0]
                word = message[1]
                value = message[2]
                value = value.decode().strip()
                r = requests.post('http://localhost:3333/create-measurement', json={"sensor_id":id, "word": word, "value": value})
              print r.status_code

