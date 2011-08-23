require 'char_detective' unless defined? CharDetective

class String
  # Attempt to detect the encoding of this string
  #
  # Returns: a Hash with :encoding, :language and :confidence
  def detect_encoding
    CharDetective.detect(self)
  end

  if RUBY_VERSION =~ /1.9/
    # Attempt to detect the encoding of this string
    # then set the encoding to what was detected ala `force_encoding`
    #
    # Returns: a Hash with :encoding, :language and :confidence
    def detect_encoding!
      if detected = CharDetective.detect(self)
        self.force_encoding detected[:encoding]
        detected
      end
    end
  end
end