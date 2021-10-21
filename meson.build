project('spanfsd', 'cpp')

# this appears to do nothing :/
add_project_arguments('-Wno-reorder', '-Wsign-compare', language: 'cpp')

executable('spanfsd', 'spanfsd.cpp',
    dependencies: [
        dependency('fuse3'),
    ],
)