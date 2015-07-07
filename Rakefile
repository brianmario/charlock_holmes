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

ICU_VERSION = "54.1"
TGZ = "icu4c-#{ICU_VERSION.sub('.', '_')}-src.tgz"

file "tmp/#{TGZ}" => "tmp" do |f|
  url = "http://download.icu-project.org/files/icu4c/#{ICU_VERSION}/#{TGZ}"
  sh "curl -L #{url} > #{f.name}"
end

task :vendor => "tmp/#{TGZ}" do |f|
  rm_rf "vendor/icu"
  sh "tar", "zxf", f.prerequisites[0], "-C", "vendor/", "icu/source/"
  sh "git add -A -f vendor/icu/source"
end

CLEAN.include "tmp/icu"

Rake::Task[:test].prerequisites  << :compile
