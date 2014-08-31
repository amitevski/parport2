// addon.cc
#include <node.h>
#include "parport_wrap.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  ParportWrap::Init(exports);
}

NODE_MODULE(addon, InitAll)
