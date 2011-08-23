$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)

require 'charlock_holmes'
require 'rspec'

RSpec.configure do |config|
  config.expect_with :stdlib
  config.alias_example_to :test
end