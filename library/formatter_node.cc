#include <node.h>
#include <v8.h>
#include "formatter.h"
#include <string>

#include <unicode/numfmt.h>
#include "unicode/unistr.h"

#include <boost/locale.hpp>
#include <boost/format.hpp>
#include <sstream>

using namespace v8;

Locale loc = Locale::getJapan();
UErrorCode success = U_ZERO_ERROR;
NumberFormat *nf = NumberFormat::createInstance(loc, success);

void ICUFormatNumber(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate* isolate = args.GetIsolate();

    UnicodeString myString;
    nf->format(123.123123, myString);

    std::string retval;
    myString.toUTF8String(retval);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, retval.c_str()));
}

void BoostFormatNumber(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate* isolate = args.GetIsolate();

    double value = args[0]->NumberValue();
    ostringstream resval;
    resval << boost::format("%f") % value;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, resval.str().c_str()));
}

void BoostLocaleFormatNumber(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate* isolate = args.GetIsolate();

    double value = args[0]->NumberValue();
    ostringstream resval;
    resval << boost::locale::as::number << value;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, resval.str().c_str()));
}

void init(Handle <Object> exports, Handle <Object> module) {
    NODE_SET_METHOD(exports, "ICUFormatNumber", ICUFormatNumber);
    NODE_SET_METHOD(exports, "BoostFormatNumber", BoostFormatNumber);
    NODE_SET_METHOD(exports, "BoostLocaleFormatNumber", BoostLocaleFormatNumber);
}

NODE_MODULE(formatter, init)
