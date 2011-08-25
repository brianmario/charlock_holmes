module CharlockHolmes
  class EncodingDetector
    # Attempt to detect the encoding of the string passed
    #
    # NOTE: This will create a new CharlockHolmes::EncodingDetector instance on every call
    #
    # Returns: a Hash with :encoding, :language and :confidence
    def self.detect(str)
      new.detect(str)
    end

    # Attempt to detect the encoding of the string passed, and return
    # a list with all the possible encodings that match it.
    #
    # NOTE: This will create a new CharlockHolmes::EncodingDetector instance on every call
    #
    # Returns: an Array with zero or more Hashes,
    #          each one of them with with :encoding, :language and :confidence
    def self.detect_all(str)
      new.detect_all(str)
    end
  end
end