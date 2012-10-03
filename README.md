# CharlockHolmes

Character encoding detecting library for Ruby using [ICU](http://site.icu-project.org/)

## Usage

First you'll need to require it

``` ruby
require 'charlock_holmes'
```

## Encoding detection

``` ruby
contents = File.read('test.xml')
detection = CharlockHolmes::EncodingDetector.detect(contents)
# => {:encoding => 'UTF-8', :confidence => 100, :type => :text}

# optionally there will be a :language key as well, but
# that's mostly only returned for legacy encodings like ISO-8859-1
```

NOTE: `CharlockHolmes::EncodingDetector.detect` will return `nil` if it was unable to find an encoding.

For binary content, `:type` will be set to `:binary`

Though it's more efficient to reuse once detector instance:

``` ruby
detector = CharlockHolmes::EncodingDetector.new

detection1 = detector.detect(File.read('test.xml'))
detection2 = detector.detect(File.read('test2.json'))

# and so on...
```

### String monkey patch

Alternatively, you can just use the `detect_encoding` method on the `String` class

``` ruby
require 'charlock_holmes/string'

contents = File.read('test.xml')

detection = contents.detect_encoding
```

### Ruby 1.9 specific

NOTE: This method only exists on Ruby 1.9+

If you want to use this library to detect and set the encoding flag on strings, you can use the `detect_encoding!` method on the `String` class

``` ruby
require 'charlock_holmes/string'

contents = File.read('test.xml')

# this will detect and set the encoding of `contents`, then return self
contents.detect_encoding!
```

## Transcoding

Being able to detect the encoding of some arbitrary content is nice, but what you probably want is to be able to transcode that content into an encoding your application is using.

``` ruby
content = File.read('test2.txt')
detection = CharlockHolmes::EncodingDetector.detect(content)
utf8_encoded_content = CharlockHolmes::Converter.convert content, detection[:encoding], 'UTF-8'
```

The first parameter is the content to transcode, the second is the source encoding (the encoding the content is assumed to be in), and the third parameter is the destination encoding.

## Installing

If the traditional `gem install charlock_holmes` doesn't work, you may need to specify the path to
your installation of ICU using the `--with-icu-dir` option during the gem install or by configuring Bundler to
pass those arguments to Gem:

Configure Bundler to always use the correct arguments when installing:

    bundle config build.charlock_holmes --with-icu-dir=/path/to/installed/icu4c

Using Gem to install directly without Bundler:

    gem install charlock_holmes -- --with-icu-dir=/path/to/installed/icu4c


### Homebrew

If you're installing on Mac OS X then using [Homebrew](http://mxcl.github.com/homebrew/) is
the easiest way to install ICU.

However, be warned; it is a Keg-Only (see [homedir issue #167](https://github.com/mxcl/homebrew/issues/167)
for more info) install meaning RubyGems won't find it when installing without specifying `--with-icu-dir`

To install ICU with Homebrew:

    brew install icu4c

Configure Bundler to always use the correct arguments when installing:

    bundle config build.charlock_holmes --with-icu-dir=/usr/local/opt/icu4c

Using Gem to install directly without Bundler:

    gem install charlock_holmes -- --with-icu-dir=/usr/local/opt/icu4c
