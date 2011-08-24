require 'mkmf'

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

$CFLAGS  << ' -I/usr/local/Cellar/icu4c/4.4.1/include'
$LDFLAGS << ' -L/usr/local/Cellar/icu4c/4.4.1/lib'

dir_config 'icu'

have_library 'icui18n'

create_makefile 'charlock_holmes'
