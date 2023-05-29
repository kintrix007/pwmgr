project('pwmgr', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++2b'],
  )

deps = []

src = files(
  'main.cpp',
  'src/generator.cpp',
  'src/database.cpp',
  )

# add_global_arguments('-Werror', language : 'cpp')
add_global_arguments('-Wno-c++20-designator', language : 'cpp')
add_global_arguments('-std=c++2b', language : 'cpp')

executable('pwmgr',
  src,
  dependencies: deps,
  install : true,
  )
