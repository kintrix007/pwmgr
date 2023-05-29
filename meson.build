project('pwmgr', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++2b'],
  )

deps = []

src = files(
  'main.cpp',
  'src/generator.cpp', 'src/database.cpp',
  'src/arguments.cpp', 'src/commands.cpp',
  'src/commands/help.cpp',
  'src/commands/add.cpp',
  'src/commands/edit.cpp',
  'src/commands/remove.cpp',
  'src/commands/search.cpp',
  'src/commands/list.cpp',
  )

# add_global_arguments('-Werror', language : 'cpp')
add_global_arguments('-Wno-c++20-designator', language : 'cpp')
add_global_arguments('-std=c++2b', language : 'cpp')

executable('pwmgr',
  src,
  dependencies: deps,
  install : true,
  )
