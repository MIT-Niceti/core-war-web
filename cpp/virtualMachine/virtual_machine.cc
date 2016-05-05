#include "v8.h"
#include "node.h"
#include "Arena.h"
#include "vector"
#include "string"

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  std::vector<std::string> champions;
  int      i = 0;

  if (args.Length() < 2) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }
  for (i = 0; i < args.Length(); i++)
  {
    v8::String::Utf8Value param(args[i]->ToString());
    champions.push_back(std::string(*param));
  }
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, startMachine(champions).c_str()));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "setVirtualMachine", Method);
}
NODE_MODULE(virtualMachine, init)
