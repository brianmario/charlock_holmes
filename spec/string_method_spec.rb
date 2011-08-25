require 'spec_helper'
require 'charlock_holmes/string'

describe String do
  test 'has a detect_encoding method' do
    str = 'test'
    str.respond_to? :detect_encoding

    detected = str.detect_encoding
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  test 'has a detect_encoding method that accepts an encoding hint' do
    str = 'test'
    str.respond_to? :detect_encoding

    detected = str.detect_encoding 'UTF-8'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  test 'has a detect_encodings method' do
    str = 'test'
    str.respond_to? :detect_encodings

    detected_list = str.detect_encodings
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  test 'has a detect_encodings method that accepts an encoding hint' do
    str = 'test'
    str.respond_to? :detect_encodings

    detected_list = str.detect_encodings 'UTF-8'
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
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