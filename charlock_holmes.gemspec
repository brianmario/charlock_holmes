require './lib/charlock_holmes/version' unless defined? CharlockHolmes::VERSION

Gem::Specification.new "charlock_holmes", CharlockHolmes::VERSION do |s|
  s.license = "MIT"
  s.authors = ["Brian Lopez", "Vicent Martí"]
  s.email = "seniorlopez@gmail.com"
  s.extensions = ["ext/charlock_holmes/extconf.rb"]
  s.files = `git ls-files lib`.split("\n")
  s.homepage = "https://github.com/brianmario/charlock_holmes"
  s.rdoc_options = ["--charset=UTF-8"]
  s.summary = "Character encoding detection, brought to you by ICU"
  s.description = "charlock_holmes provides binary and text detection as well as text transcoding using libicu"
  s.required_ruby_version = '>= 1.9.3'

  # tests
  s.add_development_dependency 'rake-compiler', ">= 0.7.5"
  s.add_development_dependency 'minitest'
  # benchmarks
  s.add_development_dependency 'chardet'
end
