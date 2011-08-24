# CharlockHolmes

Character encoding detecting library for Ruby using [ICU](http://site.icu-project.org/)

## Usage

First you'll need to require it

``` ruby
require 'charlock_holmes'
```

Now if you want to detect the encoding of a set of bytes:

``` ruby
contents = File.read('test.xml')
detection = CharlockHolmes::EncodingDetector.detect(contents)
```

Though it'd probably be more efficient to reuse once detector instance:

``` ruby
detector = CharlockHolmes::EncodingDetector.new

detection1 = detector.detect(File.read('test.xml'))
detection2 = detector.detect(File.read('test2.json'))

# and so on...
```

## String monkey patch

Alternatively, you can just use the `detect_encoding` method on the `String` class

``` ruby
require 'charlock_holmes/string'

contents = File.read('test.xml')

detection = contents.detect_encoding
```

## Ruby 1.9 specific

NOTE: This method only exists on Ruby 1.9+

If you want to use this library to detect and set the encoding flag on strings, you can use the `detect_encoding!` method on the `String` class

``` ruby
require 'charlock_holmes/string'

contents = File.read('test.xml')

# this will detect and set the encoding of `contents`
contents.detect_encoding!
```
