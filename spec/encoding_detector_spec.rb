require 'spec_helper'

describe CharlockHolmes::EncodingDetector do
  MAPPING = [
    ['repl2.cljs',                'ISO-8859-1'],
    ['core.rkt',                  'UTF-8'],
    ['cl-messagepack.lisp',       'ISO-8859-1'],
    ['TwigExtensionsDate.es.yml', 'UTF-8'],
    ['AnsiGraph.psm1',            'UTF-16LE']
  ]

  before :all do
    @detector = CharlockHolmes::EncodingDetector.new
  end

  MAPPING.each do |mapping|
    file, encoding = mapping

    test "#{file} is detected as #{encoding}" do
      path = File.expand_path "../fixtures/#{file}", __FILE__
      content = File.read path
      guessed = @detector.detect content

      puts "Guessed: #{guessed.inspect} for file #{file}"

      assert_equal encoding, guessed[:encoding]

      if content.respond_to? :force_encoding
        content.force_encoding guessed[:encoding]
        assert content.valid_encoding?
      end
    end
  end
end