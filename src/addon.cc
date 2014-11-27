// addon.cc
#include <node.h>
#include <nan.h>

// Parallel-Port
#include "ParallelPort.h"

using node::ObjectWrap;

using v8::Array;
using v8::Context;
using v8::Function;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Number;

static Persistent<FunctionTemplate> constructor;

class ParportWrap: public ObjectWrap {
public:
  ParportWrap(int portid) : ptid(portid) {
    port.open(portid);
  }

  ~ParportWrap() {
    port.close();
  }

  static NAN_METHOD(New) {
    NanScope();
    int portaddress = 0;
    if (args.Length() >= 1)
      portaddress = args[0]->Uint32Value();

    ParportWrap* ppw = new ParportWrap(portaddress);
    ppw->Wrap(args.This());

    NanReturnValue(args.This());
  }

  // read methods

  static NAN_METHOD(ReadData) {
    NanScope();
    ParportWrap* self = ObjectWrap::Unwrap<ParportWrap>(args.This());

    int data = self->port.readData();
    NanReturnValue(NanNew<Number>(data));
  }

  static NAN_METHOD(ReadControl) {
    NanScope();
    ParportWrap* self = ObjectWrap::Unwrap<ParportWrap>(args.This());

    int data = self->port.readControl();
    NanReturnValue(NanNew<Number>(data));
  }

  static NAN_METHOD(ReadStatus) {
    NanScope();
    ParportWrap* self = ObjectWrap::Unwrap<ParportWrap>(args.This());

    int data = self->port.readStatus();
    NanReturnValue(NanNew<Number>(data));
  }

  // write methods

  static NAN_METHOD(WriteData) {
    NanScope();
    ParportWrap* self = ObjectWrap::Unwrap<ParportWrap>(args.This());

    int data = args[0]->Uint32Value();
    self->port.writeData(data);
    NanReturnUndefined();
  }

  static NAN_METHOD(WriteControl) {
    NanScope();
    ParportWrap* self = ObjectWrap::Unwrap<ParportWrap>(args.This());

    int data = args[0]->Uint32Value();
    self->port.writeControl(data);
    NanReturnUndefined();
  }

  static void Init() {
    Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(ParportWrap::New);
    NanAssignPersistent(constructor, tpl);
    tpl->SetClassName(NanNew<String>("ParportWrap"));
    tpl->InstanceTemplate()->SetInternalFieldCount(5);
    NODE_SET_PROTOTYPE_METHOD(tpl, "readData", ParportWrap::ReadData);
    NODE_SET_PROTOTYPE_METHOD(tpl, "readControl", ParportWrap::ReadControl);
    NODE_SET_PROTOTYPE_METHOD(tpl, "readStatus", ParportWrap::ReadStatus);
    NODE_SET_PROTOTYPE_METHOD(tpl, "writeData", ParportWrap::WriteData);
    NODE_SET_PROTOTYPE_METHOD(tpl, "writeControl", ParportWrap::WriteControl);
  }

private:
  ParallelPort port;
  const short ptid;
};

void Init(Handle<Object> exports, Handle<Object> module) {
  ParportWrap::Init();
  v8::Local<v8::FunctionTemplate> constructorHandle =
      NanNew(constructor);

  module->Set(NanNew<String>("exports"), constructorHandle->GetFunction());
}

NODE_MODULE(parport2, Init)
