module CharlockHolmes
  class EncodingDetector
    # Default length for which to scan content for NULL bytes
    DEFAULT_BINARY_SCAN_LEN = 1024*1024

    # Length for which to scan content for NULL bytes
    attr_accessor :binary_scan_length

    alias :strip_tags? :strip_tags

    def initialize(scan_len=DEFAULT_BINARY_SCAN_LEN)
      @binary_scan_length = scan_len
    end

    # Attempt to detect the encoding of this string
    #
    # NOTE: This will create a new CharlockHolmes::EncodingDetector instance on every call
    # as well as use the default binary scan length
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
    # as well as use the default binary scan length
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
