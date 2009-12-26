#!/usr/bin/env python
"""
Filename: lottery.py
Description: a programme for allocate lottery
Author: Amos Kong <kongjianjun@gmail.com>
Date: Dec 12, 2009
"""
import random, sys, time

# Configure parameter
num_person = 50  # Number of total persons
num_1 = 1        # Number of 1th prize
num_2 = 3        # Number of 2nd prize
num_3 = 5        # Number of 3rd prize
num_all = num_1 + num_2 + num_3

def get_result():
    r = random.Random(time.time())
    result = r.sample(xrange(1, num_person+1), num_all)
    print "1. %s" % result[0:num_1]
    print "2. %s" % result[num_1:num_1+num_2]
    print "3. %s" % result[num_1+num_2:num_all]


# Main
if len(sys.argv) == 2:
    if sys.argv[1] == '-h':
        print "lottery [-h] [num_person]"
        exit(0)
    num_person = int(sys.argv[1])
if not num_all <= num_person:
    print "num_person should less than %s" % num_all
    print "lottery [-h] [num_person]"
    exit(1) 

get_result()
