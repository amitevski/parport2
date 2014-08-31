// ParportWrap.h
#ifndef PARPORTWRAP_H
#define PARPORTWRAP_H

#include <node.h>
#include <node_object_wrap.h>
#include "ParallelPort.h"

class ParportWrap : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
   explicit ParportWrap(int portid = 0);
   ~ParportWrap();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ReadData(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ReadControl(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void ReadStatus(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void WriteData(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void WriteControl(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;
    ParallelPort port;
    const short ptid;
};

#endif
