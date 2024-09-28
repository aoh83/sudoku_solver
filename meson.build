project('sudoku_solver', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++20'])

gtest_dep = dependency('gtest', version : '1.15.0')
gmock_dep = dependency('gmock', version : '1.15.0')
gtest_main_dep = dependency('gtest_main', version : '1.15.0')

executable('sudoku_solver',
           'main.cc',
           install : true)

tests_src = [
  'tests/test_simple.cc',
]  
e = executable(
  'gtest-all',
  tests_src,
  dependencies : [
    gtest_dep,
    gtest_main_dep
  ],
)    
test('gtest tests', e)