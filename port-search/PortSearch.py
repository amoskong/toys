#!/usr/bin/env python
#coding:utf-8
import telnetlib,sys,socket,time

verbose=1
if len(sys.argv) > 1:
	host=sys.argv[1]
else:
	host='127.0.0.1'
if len(sys.argv) > 2:
	MAX=int(sys.argv[2])
else:
	MAX=10000
if len(sys.argv) > 3:
	timeout=float(sys.argv[3])
else:
	timeout=0.1

open=[]


def check(port):
	msg=''
	status=0
	if verbose>0: print port
	try:

		#telnetlib.expect('1',timeout=2)
		tn = telnetlib.Telnet(host,port)

	except : 
		#print "socket.error"
		status=1
	finally:
		if status==0:
			print 'port open: ',port
			open.append(port)
def check2(port):
	msg=''
	status=0
	if verbose >0: print port
	try:
		tn = telnetlib.Telnet(host,port)
	except : 
		#print "socket.error"
		status=1
	finally:
		if status==0:
			#tn.set_debuglevel(2)
			#tn.write("GET / \r\n\ HTTP/1.1\r\nHost: www.baidu.com\r\nConnection: Close\r\n\r\n")
			#tn.write("GET /suibiandedaima\r\n\ HTTP/1.1\r\nHOST: localhost\r\nConnection: Close\r\n\r\n")
			#tn.write("GET /\ HTTP/1.1\r\nHOST: www.baidu.com\r\nConnection: Close\r\n\r\n")
			tn.write("GET /\ HTTP/1.1\r\nHOST: %s\r\nConnection: Close\r\n\r\n" %host)
			#tn.write("GET /\r\n\ HTTP/1.1\r\nHOST: 222.24.20.212\r\nConnection: Close\r\n\r\n")

			time.sleep(timeout)
			try:
				msg=tn.read_eager()

				if verbose>=2: print msg
			except:
				pass
			#msg=tn.read_all()
			#msg=tn.read_lazy()
			#msg=tn.read_some()
			tn.close()
			if 'SSH' in msg: 
				print "The SSH Service Port is :",port
				#sys.exit()
			if '220' in msg and 'FTP' in msg: 
				print "The FTP Service Port is :",port
				#sys.exit()
			if 'HTTP' in msg: 
				print "The Web Service Port is :",port
			if '+OK' in msg: 
				print "The POP Service Port is :",port
			if 'ESMTP' in msg: 
				print "The SMTP Service Port is :",port

print '$Psinfor [$HOST] [$PORT] [$TIMEOUT]\n'
print 'HOST :\t',host
print 'Timeout:\t',timeout,'\n'

for p in range(1,MAX):
	check(p)
print '\nopen: ',open,'\n'
for p in open:
	check2(p)
