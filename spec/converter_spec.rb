# encoding: utf-8

require 'spec_helper'

describe CharlockHolmes::Converter do
  test 'is able to convert regular ascii content from ISO-8859-1 to UTF-16, and back again' do
    input = 'test'

    output = CharlockHolmes::Converter.convert input, 'ISO-8859-1', 'UTF-16'
    assert input.bytesize < output.bytesize
    assert input != output

    output = CharlockHolmes::Converter.convert output, 'UTF-16', 'ISO-8859-1'
    assert input.bytesize == output.bytesize
    assert input == output
  end

  test 'is able to convert UTF-8 content from UTF-8 to UTF-16, and back again' do
    input = 'λ, λ, λ'

    output = CharlockHolmes::Converter.convert input, 'UTF-8', 'UTF-16'
    assert input.bytesize < output.bytesize
    assert input != output

    output = CharlockHolmes::Converter.convert output, 'UTF-16', 'UTF-8'
    assert input.bytesize == output.bytesize
    assert input == output
  end
end