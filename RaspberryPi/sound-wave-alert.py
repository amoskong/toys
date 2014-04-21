#!/usr/bin/python
import RPi.GPIO as GPIO
import time, sys


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
echoport = 23
trigport = 24

#GPIO.setmode(GPIO.BCM)
#echoport = 11
#trigport = 8


def read_port(n=22):
    ret = GPIO.input(n)
    if ret == GPIO.HIGH:
        return 'on'
    else:
        return 'off'

def set_port(n=24, status='on'):
    if status == 'on':
        GPIO.output(n, GPIO.HIGH)
    elif status == 'off':
        GPIO.output(n, GPIO.LOW)

def test():
    # trigger device to send out the wave by a TTL
    set_port(trigport, 'on')
    time.sleep(0.000012)
    #time.sleep(0.1)
    set_port(trigport, 'off')

    # check the feedback TTL time
    while True:
        if read_port(echoport) == 'on':
            t0 = time.time()
            break

    while True:
        if read_port(echoport) == 'off':
            t1 = time.time()
            break

    # sound speed = 340M/s
    return round((t1 - t0) * 340 / 2, 2)


GPIO.setup(trigport, GPIO.OUT)
set_port(trigport, 'off')
GPIO.setup(echoport, GPIO.IN)

GPIO.setup(8, GPIO.OUT)
num = 8
for i in range(100000):
    time.sleep(0.1)
    t = test() / 10
    if t < 0.05:
        # alert by a buzzer if distance is shorter than 50cm
        # the shorter distance, the quicker alerts
        GPIO.output(num, GPIO.HIGH)
        time.sleep(0.01)
        GPIO.output(num, GPIO.LOW)
        time.sleep(t)

GPIO.cleanup()

