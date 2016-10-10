# Basic test environment.

# blah fuck this
require 'rubygems' if !defined?(Gem)
require 'bundler/setup'

require 'charlock_holmes'

# bring in minitest
require 'minitest/autorun'

if Minitest.const_defined?('Test')
  # We're on Minitest 5+. Nothing to do here.
else
  # Minitest 4 doesn't have Minitest::Test yet.
  Minitest::Test = MiniTest::Unit::TestCase
end

def fixture(name)
  path = File.expand_path "../fixtures/#{name}", __FILE__
  File.new path
end

# put lib and test dirs directly on load path
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
$LOAD_PATH.unshift File.expand_path('..', __FILE__)

# iso encodings
SUPPORTED_ENCODINGS = Encoding.name_list.grep(/^ISO-8859-(1|2)$/)

# utf16 variants
#if Encoding.name_list.grep(/UTF-16/)
#  (SUPPORTED_ENCODINGS << Encoding.name_list.grep(/^UTF-16(BE|LE)/).flatten).flatten!
#end

# utf8
if Encoding.name_list.grep("UTF-8")
  SUPPORTED_ENCODINGS << "UTF-8"
end
