# encoding: utf-8
require File.expand_path("../helper", __FILE__)

class ConverterTest < MiniTest::Unit::TestCase
  def test_convert_ascii_from_iso859_1_to_utf16_and_back
    input = 'test'

    output = CharlockHolmes::Converter.convert input, 'ISO-8859-1', 'UTF-16'
    assert input.bytesize < output.bytesize
    assert input != output

    output = CharlockHolmes::Converter.convert output, 'UTF-16', 'ISO-8859-1'
    assert input.bytesize == output.bytesize
    assert input == output
  end

  def test_convert_utf8_to_utf16_and_back
    input = 'λ, λ, λ'

    output = CharlockHolmes::Converter.convert input, 'UTF-8', 'UTF-16'
    assert input.bytesize < output.bytesize
    assert input != output

    output = CharlockHolmes::Converter.convert output, 'UTF-16', 'UTF-8'
    assert input.bytesize == output.bytesize
    assert input == output
  end

  def test_params_must_be_strings
    assert_raises TypeError do
      CharlockHolmes::Converter.convert nil, 'UTF-8', 'UTF-16'
    end

    assert_raises TypeError do
      CharlockHolmes::Converter.convert 'lol', nil, 'UTF-16'
    end

    assert_raises TypeError do
      CharlockHolmes::Converter.convert 'lol', 'UTF-8', nil
    end

    begin
      CharlockHolmes::Converter.convert 'lol', 'UTF-8', 'UTF-16'
    rescue Exception => e
      assert_nil e, "#{e.class.name} raised, expected nothing"
    end
  end
end