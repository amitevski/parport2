{
  "targets": [
    {
      "target_name": "parport2",
      "sources": [ "src/addon.cc" ],
      "include_dirs"  : [
            "<!(node -e \"require('nan')\")"
      ],
      'cflags!': [ '-fno-exceptions', '-g' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "includes": [
          "low-level-port/low-level-port.gypi"
      ]
    }
  ]
}
