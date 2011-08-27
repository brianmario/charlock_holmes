$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)

RUBY_19 = !!(RUBY_VERSION =~ /1.9/)

require 'charlock_holmes'

# the chardet gem isn't compatible with 1.9
require 'UniversalDetector' unless RUBY_19

require 'benchmark'

CONTENT = File.read(File.expand_path('../test.txt', __FILE__))

TIMES = 100
DETECTOR = CharlockHolmes::EncodingDetector.new

Benchmark.bmbm do |x|
  # new detector every iteration
  x.report 'singleton call' do
    TIMES.times do
      CharlockHolmes::EncodingDetector.detect CONTENT
    end
  end

  # shared detector for all iterations
  x.report 'reusing a single detector' do
    TIMES.times do
      DETECTOR.detect CONTENT
    end
  end

  unless RUBY_19
    x.report 'chardet' do
      TIMES.times do
        UniversalDetector.chardet CONTENT
      end
    end
  end
end
