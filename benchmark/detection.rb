$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)

require 'charlock_holmes'
require 'benchmark'

CONTENT = File.read(File.expand_path('../test.txt', __FILE__))

TIMES = 1000
DETECTOR = CharlockHolmes::EncodingDetector.new

Benchmark.bmbm do |x|
  x.report 'class-level detect (new detector every iteration)' do
    TIMES.times do
      CharlockHolmes::EncodingDetector.detect CONTENT
    end
  end

  x.report 'instance-level detect (shared detector for all iterations)' do
    TIMES.times do
      DETECTOR.detect CONTENT
    end
  end
end
