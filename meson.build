project('sudoku_solver', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

gtest_dep = dependency('gtest', version : '1.15.0')
gmock_dep = dependency('gmock', version : '1.15.0')
# glog_dep = dependency('libglog', version : '0.7.1')
gtest_main_dep = dependency('gtest_main', version : '1.15.0')
boost_dep = dependency('boost', version: '1.86.0')
spd_dep = dependency('spdlog', version:'1.14.1')

deps = [ boost_dep, spd_dep ]

slib = library('sudokulib', 'src/sudoku.cc', dependencies: deps)

incdir = include_directories('src') # FIXME: move to include


executable('sudoku_solver',
           'main.cc',
           link_with: slib,
           include_directories: incdir,
           dependencies: deps,
           install : true)

tests_src = [
  'tests/test_simple.cc',
  'tests/test_main.cc',
]

e = executable(
  'gtest-all',
  tests_src,
  dependencies : [
    gtest_dep,
    deps
  ],
  link_with: slib,
  include_directories:incdir
)    
test('gtest tests', e)
