require 'spec_helper'
require 'charlock_holmes/string'

describe String do
  test 'has a detect_encoding method' do
    str = 'test'
    str.respond_to? :detect_encoding

    detected = str.detect_encoding
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  if RUBY_VERSION =~ /1.9/
    test 'has a detect_encoding! method' do
      str = 'test'
      str.respond_to? :detect_encoding!

      str.detect_encoding!
      assert_equal Encoding.find('ISO-8859-1'), str.encoding
    end
  end
end