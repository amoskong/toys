#!/bin/bash
# test page: http://zhidao.baidu.com/question/21631338.html

f=".tmp.txt"
f2=".tmp2.txt"

wget $1 -O $f2 >/dev/null 2>/dev/null
iconv -f gb2312 -t utf-8 $f2 > $f 2>/dev/null

sed -i -e 's/<[^>]*>//g;/<!--/d' $f 
sed -i -e 's/&nbsp;//g;s/&deg;C//g;s/^\s*//g;/^$/d' $f 

sed -e "s/[^\-\.+_a-zA-Z0-9@]/\n/g" $f |grep @|grep ^[a-zA-Z0-9]|grep [a-zA-Z0-9]$ |sort -u | tee
rm -rf $f $f2
