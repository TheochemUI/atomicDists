# Source files
_srcs = [
  'SimpleMatrix.cc',
]

_incdirs += include_directories(['include'])

# Create library
atmdistlib = library('atmdist',
                 _srcs,
                 dependencies: _deps,
                 cpp_args: _args,
                 link_with: _linkto,
                 include_directories: _incdirs,
                 install: true)
_linkto += atmdistlib

# --------------------- Executable

tiny_cli = executable('tiny_cli', 'tiny_cli.cpp',
                       dependencies: _deps,
                       include_directories: _incdirs,
                       cpp_args: _args,
                       link_with: _linkto,
                       install: false)
