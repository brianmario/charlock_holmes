require 'mkmf'
require 'fileutils'

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

# detect homebrew installs
if !have_library 'icui18n'
  base = if !`which brew`.empty?
    `brew --prefix`.strip
  elsif File.exists?("/usr/local/Cellar/icu4c")
    '/usr/local/Cellar'
  end

  if base and icu4c = Dir[File.join(base, 'Cellar/icu4c/*')].sort.last
    $INCFLAGS << " -I#{icu4c}/include "
    $LDFLAGS  << " -L#{icu4c}/lib "
  end
end

icu_version = "49_1_2"

# If the ICU version is changed 
bundled_icu_flag = "#{CWD}/bundled_icu_flag_#{icu_version}"

if File.exists?(bundled_icu_flag)
  $INCFLAGS << " -I#{CWD}/dst/include "
  $LDFLAGS  << " -L#{CWD}/dst/lib"
end

unless have_library 'icui18n' and have_library 'icudata' and have_library 'icutu' and have_library 'icuuc' and have_header 'unicode/ucnv.h'
  src = File.basename("icu4c-#{icu_version}-src.tgz")
  dir = File.basename('icu')

  Dir.chdir("#{CWD}/src") do
    FileUtils.rm_rf(dir) if File.exists?(dir)

    sys("tar zxvf #{src}")
    Dir.chdir(File.join(dir, 'source')) do
      sys("LDFLAGS= CXXFLAGS=\"-O2 -fPIC\" CFLAGS=\"-O2 -fPIC\" ./configure --prefix=#{CWD}/dst/ --disable-tests --disable-samples --disable-icuio --disable-extras --disable-layout --enable-static --disable-shared")
      sys("make install")
      sys("make clean")
    end
  end

  dir_config 'icu'

  FileUtils.touch(bundled_icu_flag)

  $INCFLAGS << " -I#{CWD}/dst/include "
  $LDFLAGS  << " -L#{CWD}/dst/lib"
end

unless have_library 'icui18n' and have_library 'icudata' and have_library 'icutu' and have_library 'icuuc' and have_header 'unicode/ucnv.h'
  STDERR.puts "\n\n"
  STDERR.puts "***************************************************************************************"
  STDERR.puts "********* error compiling and linking icu4c. please report issue on github *********"
  STDERR.puts "***************************************************************************************"
  exit(1)
end

##
# libmagic dependency
#

libmagic_version = "5.08"

bundled_libmagic_flag = "#{CWD}/bundled_libmagic_flag_#{icu_version}_#{libmagic_version}"

if File.exists?(bundled_libmagic_flag)
  $LDFLAGS << " -L#{CWD} "
else
  src = File.basename("file-#{libmagic_version}.tar.gz")
  dir = File.basename(src, '.tar.gz')

  Dir.chdir("#{CWD}/src") do
    FileUtils.rm_rf(dir) if File.exists?(dir)

    sys("tar zxvf #{src}")
    Dir.chdir(dir) do
      sys("./configure --prefix=#{CWD}/dst/ --disable-shared --enable-static --with-pic")
      sys("patch -p0 < ../file-soft-check.patch")
      sys("make -C src install")
      sys("make -C magic install")
      sys("make -C src clean")
      sys("make -C magic clean")
    end
  end

  FileUtils.cp "#{CWD}/dst/lib/libmagic.a", "#{CWD}/libmagic_ext.a"
  FileUtils.rm_rf("#{CWD}/src/icu")
  FileUtils.rm_rf("#{CWD}/src/file-5.08")

  $INCFLAGS[0,0] = " -I#{CWD}/dst/include "
  $LDFLAGS << " -L#{CWD} "
end

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
$LIBS << " -lstdc++"
create_makefile 'charlock_holmes/charlock_holmes'
