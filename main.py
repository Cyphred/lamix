import time
import OPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)

test_relay=13 # PA0
GPIO.setup(test_relay, GPIO.OUT)
relays=[test_relay]

def set_relay(pin, state):
    if state is True:
        GPIO.output(pin, GPIO.LOW)
    else:
        GPIO.output(pin, GPIO.HIGH)

def loop():
    set_relay(test_relay, True)
    time.sleep(1)
    set_relay(test_relay, False)
    time.sleep(1)

def kill_all_relays():
    for relay in relays:
        set_relay(relay, False)

while True:
    try:
        loop()
    except:
        kill_all_relays() # For safety, turn off all relays before exiting
        exit()
