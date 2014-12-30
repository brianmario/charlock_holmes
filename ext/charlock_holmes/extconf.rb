require 'mkmf'

ROOT = File.expand_path("../../..", __FILE__)
TMP  = File.join(ROOT, "tmp")
SRC  = File.join(TMP, "icu/source")

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

rubyopt = ENV.delete("RUBYOPT")

sys("cp -R #{ROOT}/vendor/icu #{TMP}/icu") unless File.exists?("#{TMP}/icu")

Dir.chdir(SRC) do
  sys("LDFLAGS= CXXFLAGS=\"-O2 -fPIC --std=c++0x\" CFLAGS=\"-O2 -fPIC\" ./configure --disable-tests --disable-samples --disable-icuio --disable-extras --disable-layout --enable-static --disable-shared")
  sys("make")
end

dir_config 'icu'

$INCFLAGS << " -I#{SRC}/common -I#{SRC}/i18n "
$LDFLAGS  << " -L#{SRC}/lib"

unless have_library 'icui18n' and have_library 'icudata' and have_library 'icutu' and have_library 'icuuc' and have_header 'unicode/ucnv.h'
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "********* error compiling and linking icu4c. please report issue on github *********"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

have_library 'z' or abort 'libz missing'
have_library 'icuuc' or abort 'libicuuc missing'
have_library 'icudata' or abort 'libicudata missing'

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']
$LIBS << " -lstdc++"

ENV['RUBYOPT'] = rubyopt
create_makefile 'charlock_holmes/charlock_holmes'
