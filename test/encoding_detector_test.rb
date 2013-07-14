# encoding: utf-8
require File.expand_path("../helper", __FILE__)

class EncodingDetectorTest < MiniTest::Unit::TestCase
  def setup
    @detector = CharlockHolmes::EncodingDetector.new
  end

  def test_has_class_level_detect_method
    CharlockHolmes::EncodingDetector.respond_to? :detect
    detected = CharlockHolmes::EncodingDetector.detect 'test'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  def test_class_level_detect_accepts_encoding_hint
    CharlockHolmes::EncodingDetector.respond_to? :detect
    detected = CharlockHolmes::EncodingDetector.detect 'test', 'UTF-8'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  def test_has_class_level_detect_all_method
    CharlockHolmes::EncodingDetector.respond_to? :detect_all
    detected_list = CharlockHolmes::EncodingDetector.detect_all 'test'
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  def test_class_level_detect_all_method_accepts_encoding_hint
    CharlockHolmes::EncodingDetector.respond_to? :detect_all
    detected_list = CharlockHolmes::EncodingDetector.detect_all 'test', 'UTF-8'
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  def test_has_detect_method
    @detector.respond_to? :detect
    detected = @detector.detect 'test'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  def test_detect_accepts_encoding_hint
    @detector.respond_to? :detect
    detected = @detector.detect 'test', 'UTF-8'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  def test_has_detect_all_method
    @detector.respond_to? :detect_all
    detected_list = @detector.detect_all 'test'
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  def test_detect_all_accepts_encoding_hint
    @detector.respond_to? :detect_all
    detected_list = @detector.detect_all 'test', 'UTF-8'
    assert detected_list.is_a? Array

    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  def test_strip_tags_flag
    detector = CharlockHolmes::EncodingDetector.new
    detector.strip_tags = true
    assert detector.strip_tags

    detection = detector.detect "<div ascii_attribute='some more ascii'>λ, λ, λ</div>"
    assert_equal 'UTF-8', detection[:encoding]

    detector.strip_tags = false
    assert !detector.strip_tags

    detection = detector.detect "<div ascii_attribute='some more ascii'>λ, λ, λ</div>"
    assert_equal 'UTF-8', detection[:encoding]
  end

  def test_has_list_of_supported_encodings
    CharlockHolmes::EncodingDetector.respond_to? :supported_encodings
    supported_encodings = CharlockHolmes::EncodingDetector.supported_encodings

    assert supported_encodings.is_a?(Array)
    assert supported_encodings.include? 'UTF-8'
  end

  MAPPING = [
    ['repl2.cljs',                'ISO-8859-1', :text],
    ['core.rkt',                  'UTF-8',      :text],
    ['cl-messagepack.lisp',       'ISO-8859-1', :text],
    ['TwigExtensionsDate.es.yml', 'UTF-8',      :text],
    ['AnsiGraph.psm1',            'UTF-16LE',   :text],
    ['laholator.py',              'UTF-8',      :text],
    ['hello_world',               nil,          :binary]
  ]

  def test_detection_works_as_expected
    MAPPING.each do |mapping|
      file, encoding, type = mapping

      path = File.expand_path "../fixtures/#{file}", __FILE__
      content = File.read path
      guessed = @detector.detect content

      assert_equal encoding, guessed[:encoding]
      assert_equal type, guessed[:type]

      if content.respond_to?(:force_encoding) && guessed[:type] == :text
        content.force_encoding guessed[:encoding]
        assert content.valid_encoding?
      end
    end
  end
end