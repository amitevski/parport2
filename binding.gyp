{
  "targets": [
    {
      "target_name": "parport2",
      "sources": [ "src/binding.cc" ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "includes": [
          "low-level-port/low-level-port.gypi"
      ]
    }
  ]
}
