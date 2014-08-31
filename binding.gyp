{
  "targets": [
    {
      "target_name": "parport2",
      "sources": [ "src/addon.cc" ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "includes": [
          "low-level-port/low-level-port.gypi"
      ]
    }
  ]
}
