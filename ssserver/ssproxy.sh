#!/bin/bash

if [ $# == 0 ] || [ $1 == "start" ]; then
    if [ ! -e /var/run/shadowsocks.pid ]; then
        sudo ssserver -qq -p 8080 -k "mypwd" -m aes-256-cfb --user nobody -d start
    fi
elif [ $1 == "stop" ]; then
    sudo ssserver -d stop
else
    echo "Usage: ssproxy.sh [start|stop]"
fi
