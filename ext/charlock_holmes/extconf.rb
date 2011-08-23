require 'mkmf'

$CFLAGS << ' -Wall -funroll-loops'
$CFLAGS << ' -Wextra -O0 -ggdb3' if ENV['DEBUG']

dir_config 'icu'

have_library 'icui18n'

create_makefile 'charlock_holmes'