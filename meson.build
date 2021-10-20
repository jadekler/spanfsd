project('spanfsd', 'cpp')

add_project_arguments('-Wno-reorder', language: 'cpp')

executable('spanfsd', 'spanfsd.cpp',
    dependencies: [
        dependency('fuse3'),
    ],
)