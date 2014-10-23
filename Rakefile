require 'rake/testtask'

Rake::TestTask.new do |t|
  t.pattern = "test/**/*_test.rb"
end

task :default => :test

gem 'rake-compiler', '>= 0.9.3'
require "rake/extensiontask"

Rake::ExtensionTask.new 'charlock_holmes' do |ext|
  ext.lib_dir = File.join 'lib', 'charlock_holmes'
end

task :clean_icu do
  icu_dst_dir = File.expand_path("../ext/charlock_holmes/dst", __FILE__)
  FileUtils.rm_rf(icu_dst_dir) if File.exist?(icu_dst_dir)

  icu_src_dir = File.expand_path("../ext/charlock_holmes/src/icu", __FILE__)
  FileUtils.rm_rf(icu_src_dir) if File.exist?(icu_src_dir)
end

Rake::Task[:clean].prerequisites << :clean_icu
Rake::Task[:test].prerequisites  << :compile
