require 'charlock_holmes' unless defined? CharlockHolmes

class String
  # Attempt to detect the encoding of this string
  #
  # Returns: a Hash with :encoding, :language and :confidence
  def detect_encoding
    CharlockHolmes.detect(self)
  end

  if RUBY_VERSION =~ /1.9/
    # Attempt to detect the encoding of this string
    # then set the encoding to what was detected ala `force_encoding`
    #
    # Returns: a Hash with :encoding, :language and :confidence
    def detect_encoding!
      if detected = CharlockHolmes.detect(self)
        self.force_encoding detected[:encoding]
        detected
      end
    end
  end
end