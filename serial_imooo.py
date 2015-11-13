import serial
import re
import time
import numpy as np
arduino = serial.Serial('COM6',9600)

while(1):

	s = arduino.readline()
	imu_reg = re.compile(r' AB (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*) (-*[0-9]*.[0-9]*)')
	m = imu_reg.match(s)
	if m is not None:
		acc_x = float(m.group(1))
		acc_y = float(m.group(2))
		acc_z = float(m.group(3))
		gyr_x = float(m.group(4))
		gyr_y = float(m.group(5))
		gyr_z = float(m.group(6))
		com_x = float(m.group(7))
		com_y = float(m.group(8))
		com_z = float(m.group(9))
		roll = float(m.group(10))
		pitch = float(m.group(11))
		yaw = float(m.group(12))
		print roll,' ',pitch,' ',yaw