# Basic test environment.

# blah fuck this
require 'rubygems' if !defined?(Gem)
require 'bundler/setup'

require 'charlock_holmes'

# bring in minitest
require 'minitest/autorun'

def fixture(name)
  path = File.expand_path "../fixtures/#{name}", __FILE__
  File.new path
end

# put lib and test dirs directly on load path
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
$LOAD_PATH.unshift File.expand_path('..', __FILE__)
