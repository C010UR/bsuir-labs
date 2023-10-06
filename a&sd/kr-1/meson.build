project('KR 1', 'cpp',
  version : '1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17'
  ]
)

incdir = include_directories('include')

exe_bst = executable('bst',
  sources : ['src/main_bst.cpp'],
  include_directories : incdir,
  install : true,
  install_dir : './bin',
)

exe_tbst = executable('tbst',
  sources : ['src/main_threaded_bst.cpp'],
  include_directories : incdir,
  install : true,
  install_dir : './bin',
)

exe_avlbst = executable('avlbst',
  sources : ['src/main_avl_bst.cpp'],
  include_directories : incdir,
  install : true,
  install_dir : './bin',
)