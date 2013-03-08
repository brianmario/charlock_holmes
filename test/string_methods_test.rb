require File.expand_path("../helper", __FILE__)
require 'charlock_holmes/string'

class StringMethodsTest < MiniTest::Unit::TestCase
  def test_adds_detect_encoding_method
    str = 'test'
    str.respond_to? :detect_encoding

    detected = str.detect_encoding
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  def test_detect_encoding_accepts_encoding_hint_param
    str = 'test'
    str.respond_to? :detect_encoding

    detected = str.detect_encoding 'UTF-8'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  def test_adds_detect_encodings_method
    str = 'test'
    str.respond_to? :detect_encodings

    detected_list = str.detect_encodings
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  def test_detect_encodings_accepts_encoding_hint_param
    str = 'test'
    str.respond_to? :detect_encodings

    detected_list = str.detect_encodings 'UTF-8'
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  if RUBY_VERSION =~ /1.9/
    def test_adds_detect_encoding_bang_method
      str = 'test'
      str.respond_to? :detect_encoding!

      str.detect_encoding!
      assert_equal Encoding.find('ISO-8859-1'), str.encoding
    end
  end
end