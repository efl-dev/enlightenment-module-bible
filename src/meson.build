inc = include_directories('.', '../..', '../')

e = dependency('enlightenment')

src = [
  'tageslosung.h',
  'main.c',
  'config.c'
]

executable('tageslosung',
  src,
  dependencies: e,
  install_dir: install_dir,
  install: true,
  include_directories: inc
)
