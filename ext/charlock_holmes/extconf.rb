require 'mkmf'

CWD = File.expand_path(File.dirname(__FILE__))
def sys(cmd)
  puts "  -- #{cmd}"
  unless ret = xsystem(cmd)
    raise "#{cmd} failed, please report issue on http://github.com/brianmario/charlock_holmes"
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

# Make sure we're using the right compiler and flags.

ENV['CC']       = RbConfig::MAKEFILE_CONFIG['CC']
ENV['CXX']      = RbConfig::MAKEFILE_CONFIG['CXX']
ENV['CFLAGS']   = '-O2 -fPIC -std=gnu99'
ENV['CXXFLAGS'] = '-O2 -fPIC'

# Make sure we're using our headers rather than ones elsewhere.
$INCFLAGS[0,0] = " -I#{CWD} "; $INCFLAGS << " -I#{CWD} "
$LDFLAGS << " -L#{CWD} "

##
# ICU dependency
#

dir_config 'icu'

if %x(uname).chomp == "Darwin" # Use the system ICU on Darwin 10.7+
  if %x(sw_vers -productVersion | cut -c4-5).chomp.to_i > 6
    
    %x(cd #{CWD}; tar xf src/darwin-icu-headers.tar.gz)
    $LDFLAGS << " -L/usr/lib "; $LDFLAGS.insert(0," -L/usr/lib -Wl,-search_dylibs_first ")
    have_library 'icucore' and have_header 'unicode/ucnv.h' or abort 'ICU missing.' 

  elsif not have_library 'icui18n' # Otherwise check Homebrew.

    base = if not %x(which brew).empty? %x(brew --prefix).strip
           elsif File.exists?("/usr/local/Cellar/icu4c") then '/usr/local/Cellar' end
    if base and icu4c = Dir[File.join(base, 'Cellar/icu4c/*')].sort.last
      $INCFLAGS << " -I#{icu4c}/include "
      $LDFLAGS  << " -L#{icu4c}/lib "

      unless have_library 'icui18n' and have_header 'unicode/ucnv.h'
        STDERR.puts "\n\n"
        STDERR.puts "**********************************************************"
        STDERR.puts "*********** icu required (brew install icu4c) ************"
        STDERR.puts "**********************************************************"
        exit(1)
      end
    end
  end # !Darwin
  else
    unless have_library 'icui18n' and have_library 'icudata' and have_header 'unicode/ucnv.h' 
      STDERR.puts "\n\n"
      STDERR.puts "***********************************************************************"
      STDERR.puts "*********** icu required (i.e., apt-get install libicu-dev) ***********"
      STDERR.puts "***********************************************************************"
      exit(1)
    end
end

##
# libmagic dependency
#

src = File.basename('file-5.16.tar.gz')
dir = File.basename(src, '.tar.gz')
libdir = 'lib'

Dir.chdir("#{CWD}/src") do
  FileUtils.rm_rf(dir) if File.exists?(dir)

  sys("tar zxvf #{src}")
  Dir.chdir(dir) do
    sys("./configure --prefix=#{CWD}/dst --disable-shared --enable-static --with-pic")
    sys("patch -p0 < ../file-soft-check.patch")
    sys("cd src; make install")
    sys("cd magic; make install")
    # this should evaluate to either 'lib' or 'lib64'
    libdir = `grep ^libdir config.log`.strip().split("'")[1].split('/')[-1]
  end
end

FileUtils.cp "#{CWD}/dst/#{libdir}/libmagic.a", "#{CWD}/libmagic_ext.a"
FileUtils.cp "#{CWD}/dst/include/magic.h",      "#{CWD}/magic.h"

%x(cd #{CWD}; rm -rf dst)

dir_config 'magic'
unless have_library 'magic_ext' and have_header 'magic.h'
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "********* error compiling and linking libmagic. please report issue on github *********"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

create_makefile 'charlock_holmes/charlock_holmes'
