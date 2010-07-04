#!/usr/bin/env python
#coding=utf-8
#author: Jianjun Kong
#website:http://kongove.cn

import urllib,cookielib,urllib2,httplib
import sys,string,os

web_url = "http://qq.ip138.com/"
web_url += "wb/wb.asp?"
str=string.join(sys.argv[1:],'')

def init():
    cookie = cookielib.CookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cookie))

    exheaders = [("User-Agent","Firefox/3.05 (X11; Linux x86_64; U;en)"),("Connection","Keep-Alive"),("Referer","http://qq.ip138.com/"),("Accept","text/html,application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg,image/gif, image/x-xbitmap, */*;q=0.1"),("Accept-Charset","iso-8859-1,utf-8, utf-16, *;q=0.1"),("Cookie2","$Version=1"),]

    opener.addheaders = exheaders
    urllib2.install_opener(opener)
    return opener

def search(opener):
    global web_url,str

    body = (("querykey",str.decode('utf-8').encode('gb2312')),)
    ret  = opener.open(web_url,urllib.urlencode(body)) 
    str=ret.read()
    str=str.decode('gb2312').encode('utf-8')
    f=open("/tmp/wubi.tmp","w")
    f.write("%s" %(str))
    f.close()

def main(argv=None):
    opener=init()
    search(opener)

    cmds='''
sed -i -e '1,/<form name="form1" method="post"/d' /tmp/wubi.tmp;
sed -i -e '1,/<\/form>/d' /tmp/wubi.tmp;
sed -i -e '/<br>/,$d' /tmp/wubi.tmp;
sed -i -e 's/<\/tr><tr>/\r\n/g' /tmp/wubi.tmp;
sed -i -e '1,/汉语拼音/d' /tmp/wubi.tmp;
sed -i -e 's/、/\t/g' /tmp/wubi.tmp;
sed -i -e 's/<\/td><td>/\t/g' /tmp/wubi.tmp;
sed -i -e 's/<[^>]*>//g;/<!--/d' /tmp/wubi.tmp;
sed -i -e 's/&nbsp;//g;s/&deg;C//g;s/^\s*//g;/^$/d' /tmp/wubi.tmp
'''
    cmd="sed -i -e '1,/<form name=\"form1\" method=\"post\"/d' /tmp/wubi.tmp;\
    sed -i -e '1,/<\/form>/d' /tmp/wubi.tmp;\
    sed -i -e '/\<br\>/,$d' /tmp/wubi.tmp;\
    sed -i -e 's/<\/tr><tr>/\\r\\n/g' /tmp/wubi.tmp;\
    sed -i -e '1,/汉语拼音/d' /tmp/wubi.tmp;\
    sed -i -e 's/、/\\t/g' /tmp/wubi.tmp;\
    sed -i -e 's/<\/td><td>/\\t/g' /tmp/wubi.tmp;\
    sed -i -e 's/<[^>]*>//g;/<!--/d' /tmp/wubi.tmp;\
    sed -i -e 's/&nbsp;//g;s/&deg;C//g;s/^\s*//g;/^$/d' /tmp/wubi.tmp"

    os.system(cmd)
    print  "序号\t汉字\t五笔\t拼音"
    #exit()
    f=open("/tmp/wubi.tmp","r")
    print f.read(),
    f.close()

if __name__ == "__main__":
    sys.exit(main())
