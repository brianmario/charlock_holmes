require 'spec_helper'

describe CharlockHolmes::EncodingDetector do
  before :all do
    @detector = CharlockHolmes::EncodingDetector.new
  end

  test 'has a detect class-level method' do
    CharlockHolmes::EncodingDetector.respond_to? :detect
    detected = CharlockHolmes::EncodingDetector.detect 'test'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  test 'has a detect method' do
    @detector.respond_to? :detect
    detected = @detector.detect 'test'
    assert_equal 'ISO-8859-1', detected[:encoding]
  end

  test 'has a detect_all method' do
    @detector.respond_to? :detect_all
    detected_list = @detector.detect_all 'test'
    encoding_list = detected_list.map {|d| d[:encoding]}.sort
    assert_equal ['ISO-8859-1', 'ISO-8859-2', 'UTF-8'], encoding_list
  end

  context "is able to detect that" do
    MAPPING = [
      ['repl2.cljs',                'ISO-8859-1'],
      ['core.rkt',                  'UTF-8'],
      ['cl-messagepack.lisp',       'ISO-8859-1'],
      ['TwigExtensionsDate.es.yml', 'UTF-8'],
      ['AnsiGraph.psm1',            'UTF-16LE']
    ]

    MAPPING.each do |mapping|
      file, encoding = mapping

      test "#{file} is #{encoding}" do
        path = File.expand_path "../fixtures/#{file}", __FILE__
        content = File.read path
        guessed = @detector.detect content

        assert_equal encoding, guessed[:encoding]

        if content.respond_to? :force_encoding
          content.force_encoding guessed[:encoding]
          assert content.valid_encoding?
        end
      end
    end
  end
end