require 'rake/testtask'

Rake::TestTask.new do |t|
  t.pattern = "test/**/*_test.rb"
end

task :default => :test

gem 'rake-compiler', '>= 0.7.5'
require "rake/extensiontask"

Rake::ExtensionTask.new 'charlock_holmes' do |ext|
  ext.lib_dir = File.join 'lib', 'charlock_holmes'
  ext.config_options << '--enable-static' if ENV['ENABLE_STATIC']
end

Rake::Task[:test].prerequisites << :compile
