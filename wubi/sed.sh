#!/bin/bash

#./a.py $@
#iconv -f gb2312 -t utf-8 /tmp/wubi.txt >/tmp/wubi2.txt

sed -i -e '1,/<form name="form1" method="post"/d' /tmp/wubi.txt
sed -i -e '1,/<\/form>/d' /tmp/wubi.txt
sed -i -e '/<br>/,$d' /tmp/wubi.txt
sed -i -e 's/<\/tr><tr>/\r\n/g' /tmp/wubi.txt
sed -i -e '1,/汉语拼音/d' /tmp/wubi.txt
sed -i -e 's/、/\t/g' /tmp/wubi.txt
sed -i -e 's/<\/td><td>/\t/g' /tmp/wubi.txt
sed -i -e 's/<[^>]*>//g;/<!--/d' /tmp/wubi.txt
sed -i -e 's/&nbsp;//g;s/&deg;C//g;s/^\s*//g;/^$/d' /tmp/wubi.txt
#rm -rf   /tmp/wubi.txt

