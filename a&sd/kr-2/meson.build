project('KR 2', 'cpp',
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

exe = executable('kr',
  sources : src,
  include_directories : incdir,
  install : true,
  install_dir : './bin',
)