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

##
# ICU dependency
#

src = File.basename('icu4c-4_8_1-src.tgz')
dir = File.basename('icu')

Dir.chdir("#{CWD}/src") do
  FileUtils.rm_rf(dir) if File.exists?(dir)

  sys("tar zxvf #{src}")
  Dir.chdir(File.join(dir, 'source')) do
    sys("./configure --prefix=#{CWD}/dst/ --disable-tests --disable-samples --disable-icuio --disable-extras --disable-layout --enable-static")
    sys("make install")
  end
end

dir_config 'icu'

$INCFLAGS << " -I#{CWD}/dst/include "
$LDFLAGS  << " -L#{CWD}/dst/lib "

unless have_library 'icui18n' and have_header 'unicode/ucnv.h'
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "********* error compiling and linking icu4c. please report issue on github *********"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

##
# libmagic dependency
#

src = File.basename('file-5.08.tar.gz')
dir = File.basename(src, '.tar.gz')

Dir.chdir("#{CWD}/src") do
  FileUtils.rm_rf(dir) if File.exists?(dir)

  sys("tar zxvf #{src}")
  Dir.chdir(dir) do
    sys("./configure --prefix=#{CWD}/dst/ --disable-shared --enable-static --with-pic")
    sys("make -C src install")
    sys("make -C magic install")
  end
end

FileUtils.cp "#{CWD}/dst/lib/libmagic.a", "#{CWD}/libmagic_ext.a"

$INCFLAGS[0,0] = " -I#{CWD}/dst/include "
$LDFLAGS << " -L#{CWD} "

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
