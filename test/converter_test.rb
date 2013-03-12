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

  def test_transliterate
    trans_id = "Any-NFD; Any-Latin; Latin-ASCII; Any-NFC"

    input = 'Schloß - Assunção - Łódź'
    assert_equal "Schloss - Assuncao - Lodz",
      CharlockHolmes::Converter.transliterate(input, trans_id)

    input = "TÜM GOLLER Fb 4-1 Bursa Maç Özeti Íƶle"
    assert_equal "TUM GOLLER Fb 4-1 Bursa Mac Ozeti Izle",
      CharlockHolmes::Converter.transliterate(input, trans_id)

    input = "ฉันกินกระจกได้ แต่มันไม่ทำให้ฉันเจ็บ"
    assert_equal "chan kin krack di tae man mi thahi chan ceb",
      CharlockHolmes::Converter.transliterate(input, trans_id)
  end
end