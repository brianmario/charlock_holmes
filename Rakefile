# rspec
begin
  require 'rspec'
  require 'rspec/core/rake_task'

  desc "Run all examples with RCov"
  RSpec::Core::RakeTask.new('spec:rcov') do |t|
    t.rcov = true
  end
  RSpec::Core::RakeTask.new('spec') do |t|
    t.verbose = true
  end

  task :default => :spec
rescue LoadError
  puts "rspec, or one of its dependencies, is not available. Install it with: sudo gem install rspec"
end

# rake-compiler
require 'rake' unless defined? Rake

gem 'rake-compiler', '>= 0.7.5'
require "rake/extensiontask"

Rake::ExtensionTask.new 'char_detective'

Rake::Task[:spec].prerequisites << :compile