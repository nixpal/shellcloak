##
# This module requires Metasploit: https://metasploit.com/download
# Current source: https://github.com/rapid7/metasploit-framework
##
 
class MetasploitModule < Msf::Encoder
  Rank = NormalRanking
 
  def initialize
    super(
      'Name'             => 'Powershell Base64 Script Encoder',
      'Description'      => %q{
        This encodes a PowerShell script as a base64 encoded script for PowerShell.
      },
      'Author'           => 'Didier Stevens',
      'Arch'             => ARCH_CMD,
      'Platform'         => 'win')
 
    register_options([
      OptBool.new('NOEXIT', [ false, 'Add -noexit option', false ]),
      OptBool.new('SYSWOW64', [ false, 'Call syswow64 powershell', false ])
    ])
 
  end
 
  #
  # Encodes the payload
  #
  def encode_block(state, buf)
    base64 = Rex::Text.encode_base64(Rex::Text.to_unicode(buf))
    cmd = ''
    if datastore['SYSWOW64']
      cmd += 'c:\Windows\SysWOW64\WindowsPowerShell\v1.0\powershell.exe '
    else
      cmd += 'powershell.exe '
    end
    if datastore['NOEXIT']
      cmd += '-NoExit '
    end
    cmd += "-EncodedCommand #{base64}"
  end
end
