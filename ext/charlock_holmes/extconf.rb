require 'mkmf'

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

ldflags = cppflags = nil

if RbConfig::CONFIG["host_os"] =~ /darwin/
  begin
    brew_prefix = `brew --prefix icu4c`.chomp
    ldflags   = "#{brew_prefix}/lib"
    cppflags  = "#{brew_prefix}/include"
    pkg_conf  = "#{brew_prefix}/lib/pkgconfig"
    # pkg_config should be less error prone than parsing compiler
    # commandline options, but we need to set default ldflags and cpp flags
    # in case the user doesn't have pkg-config installed
    ENV['PKG_CONFIG_PATH'] ||= pkg_conf
  rescue
  end
end

dir_config 'icu', cppflags, ldflags

pkg_config("icu-i18n")
pkg_config("icu-io")
pkg_config("icu-uc")

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

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

minimal_program = <<~SRC
  #include <unicode/translit.h>
  int main() { return 0; }
SRC

# Pass -x c++ to force gcc to compile the test program
# as C++ (as it will end in .c by default).
compile_options = +"-x c++"

icu_requires_version_flag = checking_for("icu that requires explicit C++ version flag") do
  !try_compile(minimal_program, compile_options)
end

if icu_requires_version_flag
  abort "Cannot compile icu with your compiler: recent versions require C++17 support." unless %w[c++20 c++17 c++11 c++0x].any? do |std|
    checking_for("icu that compiles with #{std} standard") do
      flags = compile_options + " -std=#{std}"
      if try_compile(minimal_program, flags)
        $CPPFLAGS << flags

        true
      end
    end
  end
end

create_makefile 'charlock_holmes/charlock_holmes'
