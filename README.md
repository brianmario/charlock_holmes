# CharlockHolmes

Character encoding detecting library for Ruby using [ICU](http://site.icu-project.org/)

## Usage

First you'll need to require it

``` ruby
require 'charlock_holmes'
```

Now if you want to detect the encoding of a set of bytes:

```
contents = File.read('test.xml')
detection = CharlockHolmes.detect(contents)
```

Alternatively, you can just use the `detect_encoding` method on the `String` class

``` ruby
contents = File.read('test.xml')
detection = contents.detect_encoding
```

## Ruby 1.9 specific

If you want to use this library to detect and set the encoding flag on strings, you can use the `detect_encoding!` method on the `String` class

``` ruby
contents = File.read('test.xml')
# this will detect and set the encoding of `contents`
contents.detect_encoding!
```
