module CharlockHolmes
  class EncodingDetector
    # Attempt to detect the encoding of this string
    #
    # NOTE: This will create a new CharlockHolmes::EncodingDetector instance on every call
    #
    # Returns: a Hash with :encoding, :language and :confidence
    def self.detect(str)
      new.detect(str)
    end
  end
end