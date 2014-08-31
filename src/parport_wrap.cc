// parport_wrap.cc
#include "parport_wrap.h"

using namespace v8;

Persistent<Function> ParportWrap::constructor;

ParportWrap::ParportWrap(int portid) : ptid(portid) {
  port.open(portid);
}

ParportWrap::~ParportWrap() {
  port.close();
}

void ParportWrap::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "ParportWrap"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "readData", ReadData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "readStatus", ReadStatus);
  NODE_SET_PROTOTYPE_METHOD(tpl, "readControl", ReadControl);
  NODE_SET_PROTOTYPE_METHOD(tpl, "writeData", WriteData);
  NODE_SET_PROTOTYPE_METHOD(tpl, "writeControl", WriteControl);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "ParportWrap"),
               tpl->GetFunction());
}

void ParportWrap::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    int ptid = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    ParportWrap* obj = new ParportWrap(ptid);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void ParportWrap::ReadData(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ParportWrap* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());

  args.GetReturnValue().Set(Integer::New(isolate, obj->port.readData()));
}


void ParportWrap::ReadControl(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ParportWrap* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());

  args.GetReturnValue().Set(Integer::New(isolate, obj->port.readControl()));
}


void ParportWrap::ReadStatus(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ParportWrap* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());

  args.GetReturnValue().Set(Integer::New(isolate, obj->port.readStatus()));
}



void ParportWrap::WriteData(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ParportWrap* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());

  obj->port.writeControl(Integer::New(isolate, args[0]));
  args.GetReturnValue().Set(Undefined());
}




void ParportWrap::WriteControl(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  ParportWrap* obj = ObjectWrap::Unwrap<MyObject>(args.Holder());

  obj->port.writeControl(Integer::New(isolate, args[0]));
  args.GetReturnValue().Set(Undefined());
}
