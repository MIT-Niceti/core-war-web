#include "Compiler.hh"
#include <node.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

namespace compiler {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

inline void replaceStdCerr(std::ostringstream &stream, std::streambuf *&coutBackup, std::streambuf *&cerrBackup)
{
    coutBackup = std::cout.rdbuf();
    cerrBackup = std::cerr.rdbuf();
    std::cerr.rdbuf(stream.rdbuf());
    std::cout.rdbuf(stream.rdbuf());
}

inline void extractCompilerLogAndResetStdCerr(std::ostringstream &stream, std::streambuf *coutBackup, std::streambuf *cerrBackup, std::string &output)
{
    output = stream.str();
    std::cerr.rdbuf(cerrBackup);
    std::cout.rdbuf(coutBackup);
}

void jsonizeCompilerOutput(bool status, std::string &output)
{
    std::string json;
    std::string escapedOutputLog;

    for (char c : output)
    {
        if (c == '\'' || c == '\"' || c == '\\')
            escapedOutputLog.push_back('\\');
        if (c == '\n')
            escapedOutputLog += "\\n";
        else if (c != '\r')
            escapedOutputLog.push_back(c);
    }
    json = "{ \"status\": " + (status ? std::string("true") : std::string("false")) + ", \"logs\": \"" + escapedOutputLog + "\" }";
    output = json;
}

void RunCompiler(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    std::vector<std::string> arguments;

    if (args.Length() < 2) {
      // Throw an Error that is passed back to JavaScript
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
    }
    for (int i = 0; i < args.Length(); ++i)
    {
      v8::String::Utf8Value param(args[i]->ToString());
      arguments.push_back(std::string(*param));
    }

    Compiler compiler(arguments[0], arguments[1]);
    std::streambuf *cerrBackup = NULL, *coutBackup = NULL;
    std::ostringstream outputStream;
    std::string output;
    bool status;

    replaceStdCerr(outputStream, cerrBackup, coutBackup);
    status = compiler.run();
    extractCompilerLogAndResetStdCerr(outputStream, cerrBackup, coutBackup, output);

    jsonizeCompilerOutput(status, output);

    args.GetReturnValue().Set(String::NewFromUtf8(isolate, output.c_str()));
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "compile", RunCompiler);
}

NODE_MODULE(compilerAddon, Init)

}
