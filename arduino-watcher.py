import serial
import re
import redis

# Initialize connection with redis server
redis_server = redis.Redis(host="localhost", port=6379, decode_responses=True)

# Make sure it's the only ttyUSB device attached
arduino=serial.Serial("/dev/ttyUSB0", 9600)
arduino_buffer=""

while True:
    # Read from serial
    line = arduino.readline().decode("utf-8")

    # Strip the line of newline characters
    stripped = line.rstrip("\r\n")

    # Split the data
    ph, ethanol, temp = map(float, stripped.split(','))

    # Save values to redis
    redis_server.set("ph", ph)
    redis_server.set("ethanol", ethanol)
    redis_server.set("temp", temp)
