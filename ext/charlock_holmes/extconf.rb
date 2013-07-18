require 'mkmf'

CWD = File.expand_path(File.dirname(__FILE__))
def sys(cmd)
  puts "  -- #{cmd}"
  unless ret = xsystem(cmd)
    raise "#{cmd} failed, please report issue on http://github.com/brianmario/charlock_holmes"
  end
  ret
end

if !find_executable('make')
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

icu_config = with_config('icu-config', 'icu-config')

def find_brew_executable(command)
  brew = find_executable('brew') or return nil
  find_executable(command, `eval $(#{brew} --env icu4c) && echo $PATH`.strip)
end

if icu_config = find_executable(icu_config) || find_brew_executable(icu_config)
  $CPPFLAGS = `#{icu_config} --cppflags`.strip << ' ' << $CPPFLAGS
  $LDFLAGS  = `#{icu_config} --ldflags`.strip  << ' ' << $LDFLAGS
  $LIBPATH  = `#{icu_config} --ldflags-searchpath`.strip.shellsplit.map { |arg|
    arg[/\A-L(.+)/, 1]
  } | $LIBPATH
end

unless have_library 'icui18n' and have_header 'unicode/ucnv.h'
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "*********** icu required (brew install icu4c or apt-get install libicu-dev) ***********"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

have_library 'z' or abort 'libz missing'
have_library 'icuuc' or abort 'libicuuc missing'
have_library 'icudata' or abort 'libicudata missing'

##
# libmagic dependency
#

src = File.basename('file-5.08.tar.gz')
dir = File.basename(src, '.tar.gz')
libdir = 'lib'

Dir.chdir("#{CWD}/src") do
  FileUtils.rm_rf(dir) if File.exists?(dir)

  sys("tar zxvf #{src}")
  Dir.chdir(dir) do
    sys("./configure --prefix=#{CWD}/dst/ --disable-shared --enable-static --with-pic")
    sys("patch -p0 < ../file-soft-check.patch")
    sys("make -C src install")
    sys("make -C magic install")
    # this should evaluate to either 'lib' or 'lib64'
    libdir = `grep ^libdir config.log`.strip().split("'")[1].split('/')[-1]
  end
end

FileUtils.cp "#{CWD}/dst/#{libdir}/libmagic.a", "#{CWD}/libmagic_ext.a"

$INCFLAGS[0,0] = " -I#{CWD}/dst/include "
$LIBPATH = [CWD] | $LIBPATH

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
