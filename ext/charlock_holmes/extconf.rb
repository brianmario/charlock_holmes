require 'mkmf'

CWD = File.expand_path(File.dirname(__FILE__))
def sys(cmd)
  puts "  -- #{cmd}"
  unless ret = xsystem(cmd)
    raise "#{cmd} failed, please report issue on https://github.com/brianmario/charlock_holmes"
  end
  ret
end

if `which make`.strip.empty?
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "*************** make required (apt-get install make build-essential) =( ***************"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

##
# ICU dependency
#

dir_config 'icu'

rubyopt = ENV.delete("RUBYOPT")

if !have_library 'icui18n'
  $INCFLAGS << " -I#{CWD}/darwin" if have_library 'icucore'

  unless have_header 'unicode/ucnv.h'
    STDERR.puts "\n\n"
    STDERR.puts "***************************************************************************************"
    STDERR.puts "*********** icu required (brew install icu4c or apt-get install libicu-dev) ***********"
    STDERR.puts "***************************************************************************************"
    exit(1)
  end
end

have_library 'z' or abort 'libz missing'
have_library 'icuuc' or have_library 'icucore' or abort 'libicuuc missing'
have_library 'icudata' or have_library 'icucore' or abort 'libicudata missing'

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

ENV['RUBYOPT'] = rubyopt
create_makefile 'charlock_holmes/charlock_holmes'
