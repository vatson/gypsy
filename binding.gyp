{
  'targets': [
    {
      'target_name': 'formatting',
      'defines': [ 'V8_DEPRECATION_WARNINGS=1' ],
      'sources': [ 'library/formatter.cc', 'library/formatter_node.cc'],
      'libraries': [ "<!@(icu-config --ldflags)", "/usr/local/Cellar/boost/1.62.0/lib/libboost_locale-mt.dylib"],
      'cflags': [ "<!@(icu-config --cppflags)" ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++', '-v'],
            'OTHER_LDFLAGS': ['-stdlib=libc++'],
            'GCC_ENABLE_CPP_RTTI': 'YES'
          }
        }]
      ]
    }  
  ],
  
}