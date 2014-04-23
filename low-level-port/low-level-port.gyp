{
    "targets": [ {
        "target_name": "low-level-port",
        "type": "shared_library",
        "include_dirs": [ "src" ]
        "sources": [
            "src/ParallelPort.cpp"
        ],
        "direct_dependent_settings": {
            "include_dirs": [ "src" ],
            "cflags_cc": [ "-fexceptions" ]
        },
        "cflags_cc": [  "-fexceptions"  ] 
    } ]
}
