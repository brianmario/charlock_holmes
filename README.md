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
# => {:encoding => 'UTF-8', :confidence => 100}

# optionally there will be a :language key as well, but
# that's mostly only returned for legacy encodings like ISO-8859-1
```

NOTE: `CharlockHolmes::EncodingDetector.detect` will return `nil` if it was unable to find an encoding.

Though it's more efficient to reuse once detector instance:

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

## Installing

If the traditional `gem install charlock_holmes` doesn't work, you may need to specify the path to your installation of ICU using the `--with-icu-dir` option during the gem install.

At the time of writing, if you installed ICU via homebrew on OSX your gem install may look something like this:

`gem install charlock_holmes --with-icu-dir=/usr/local/Cellar/icu4c/4.4.1`

If you're using Bundler and need to specify a custom path, you can do so with the `bundle config` command:

`bundle config build.charlock_holmes --with-icu-dir=/usr/local/Cellar/icu4c/4.4.1`
