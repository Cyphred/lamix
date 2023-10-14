import time
import OPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)

from w1thermsensor import W1ThermSensor
temp_sensor = W1ThermSensor()

# PA0
relay_pin=13 

# PA3
mq3_pin=15 

GPIO.setup(mq3_pin, GPIO.IN)
GPIO.setup(relay_pin, GPIO.OUT)

def loop():
    gas=GPIO.input(mq3_pin)
    temp = temp_sensor.get_temperature()

    print(f"Temperature: {temp}")
    print(f"Gas: {gas}")

    print(GPIO.HIGH)

    time.sleep(1)

def set_relay(state):
    if state is True:
        GPIO.output(relay_pin, GPIO.LOW)
    else:
        GPIO.output(relay_pin, GPIO.HIGH)

while True:
    loop()
