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

unless File.exists?(CWD + '/libmagic_ext.a')
  src = File.basename('file-5.08.tar.gz')
  dir = File.basename(src, '.tar.gz')

  Dir.chdir("#{CWD}/src") do
    FileUtils.rm_rf(dir) if File.exists?(dir)

    sys("tar zxvf #{src}")
    Dir.chdir(dir) do
      sys("./configure --prefix=#{CWD}/dst/ --disable-shared --enable-static")
      sys("make")
      sys("make install")
    end
  end

  FileUtils.cp "#{CWD}/dst/lib/libmagic.a", "#{CWD}/libmagic_ext.a"
end

$INCFLAGS[0,0] = "-I#{CWD}/dst/include "
$LDFLAGS << " -L#{CWD}"

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

dir_config 'icu'
have_library 'icui18n'

dir_config 'magic'
have_library 'magic_ext'

create_makefile 'charlock_holmes'
