<img width="998" alt="dBi" src="https://github.com/nixpal/shellcloak/blob/master/shellcloak.png">
                                          
----------------------------------------------------------------------------------------------
# PLEASE DO NOT UPLOAD THE MAIN DROPPER TO VIRUSTOTAL. IT'S ALMOST 100% UNDETECTABLE ALREADY.
----------------------------------------------------------------------------------------------

- ShellCloak is a new technique to separate the shellcode from the dropper without downloading anything to the vitctim's machine. The way how this works is it uses Chrome's and Firefox's history database to our advantage.

- First it will generate meterpreter x86 powershell then it will use that shellcode as a URL on THREE parts. So there will be THREE redirections using javascript files. Each redirection will take 1 part from the shellcode and of course Chrome or Firefox will store that URL in it's history database which we will access later.

- By doing that we are bypassing AV and IDS since we are not doing anything to the target box lol, it's the browser itself doing that for us. Thank you Chrome and Firefox for your cooperations :D.

- Once all the 3 parts stored in Chrome's or Firefox's database, we open that database using our C code and put all the pieces together and then execute it.

- Since the dropper itself doesn't have anything inside it, it should be almost 100% undetectable and clean.

- The javascript file will detect the browser and will redirect the user based on that browser.

### This was tested on Windows 7 x86 and it's working fine. I haven't tested it on other boxes. I will try to add x64 later for Windows7 and Windows 10. Wait for updates.



### The only step you need is: copy base64.rb to /usr/share/metasploit-framework/modules/encoders/base64/
### You also need to install mingw cross compiler using this commnand: apt-get install mingw-w64

# Thanks All

