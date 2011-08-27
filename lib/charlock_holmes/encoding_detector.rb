module CharlockHolmes
  class EncodingDetector
    alias :strip_tags? :strip_tags

    # Attempt to detect the encoding of this string
    #
    # NOTE: This will create a new CharlockHolmes::EncodingDetector instance on every call
    #
    # str      - a String, what you want to detect the encoding of
    # hint_enc - an optional String (like "UTF-8"), the encoding name which will
    #            be used as an additional hint to the charset detector
    #
    # Returns: a Hash with :encoding, :language, :type and :confidence
    def self.detect(str, hint_enc=nil)
      new.detect(str, hint_enc)
    end

    # Attempt to detect the encoding of this string, and return
    # a list with all the possible encodings that match it.
    #
    # NOTE: This will create a new CharlockHolmes::EncodingDetector instance on every call
    #
    # str      - a String, what you want to detect the encoding of
    # hint_enc - an optional String (like "UTF-8"), the encoding name which will
    #            be used as an additional hint to the charset detector
    #
    # Returns: an Array with zero or more Hashes,
    # each one of them with with :encoding, :language, :type and :confidence
    def self.detect_all(str, hint_enc=nil)
      new.detect_all(str, hint_enc)
    end
  end
end