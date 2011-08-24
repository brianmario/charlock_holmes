require 'charlock_holmes' unless defined? CharlockHolmes

class String
  # Attempt to detect the encoding of this string
  #
  # Returns: a Hash with :encoding, :language and :confidence
  def detect_encoding
    encoding_detector.detect(self)
  end

  if RUBY_VERSION =~ /1.9/
    # Attempt to detect the encoding of this string
    # then set the encoding to what was detected ala `force_encoding`
    #
    # Returns: a Hash with :encoding, :language and :confidence
    def detect_encoding!
      if detected = self.detect_encoding
        self.force_encoding detected[:encoding]
        detected
      end
    end
  end

  protected
  def encoding_detector
    @encoding_detector ||= CharlockHolmes::EncodingDetector.new
  end
end
