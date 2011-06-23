#include "http/Cookie.h"

namespace mike
{
  Cookie::Cookie(string name, string value, string domain, string path, bool secure, time_t expires)
    : name_(name)
    , value_(value)
    , domain_(domain)
    , path_(path)
    , secure_(secure)
    , expires_(expires)
  {
  }

  Cookie::~Cookie()
  {
  }

  string Cookie::toStr()
  {
    return "";
  }

  string Cookie::getName()
  {
    return name_;
  }

  string Cookie::getValue()
  {
    return value_;
  }

  string Cookie::getDomain()
  {
    return domain_;
  }

  string Cookie::getPath()
  {
    return path_;
  }

  bool Cookie::isSecure()
  {
    return secure_;
  }

  time_t Cookie::getExpires()
  {
    return expires_;
  }
}
