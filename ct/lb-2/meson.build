project('Lab 15', 'cpp',
  version : '1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17'
  ]
)

incdir = include_directories('include')

src = [
  'src/main.cpp',
]

executable('lab',
  sources : src,
  include_directories : incdir,
  install : true,
  install_dir : './bin',
)