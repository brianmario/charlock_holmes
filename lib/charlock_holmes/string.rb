require 'charlock_holmes' unless defined? CharlockHolmes

class String
  # Attempt to detect the encoding of this string
  #
  # Returns: a Hash with :encoding, :language and :confidence
  def detect_encoding
    encoding_detector.detect(self)
  end

  # Attempt to detect the encoding of this string, and return
  # a list with all the possible encodings that match it.
  #
  # Returns: an Array with zero or more Hashes,
  #          each one of them with with :encoding, :language and :confidence
  def detect_encodings
    encoding_detector.detect_all(self)
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
