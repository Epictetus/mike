#include <string.h>
#include "Browser.h"
#include "BrowserWindow.h"
#include "utils/SystemInfo.h"

namespace mike
{
  Browser::Browser(string language/*="en"*/, string userAgent/*=""*/, bool cookieEnabled/*=true*/, bool javaEnabled/*=true*/)
    : language_(language)
    , customUserAgent_(userAgent)
    , cookieEnabled_(cookieEnabled)
    , javaEnabled_(javaEnabled)
  {
  }

  Browser::~Browser()
  {
  }

  string Browser::getLanguage()
  {
    return language_;
  }

  string Browser::getUserAgent()
  {
    if (customUserAgent_.empty()) {
      char* tpl = (char*)MIKE_USER_AGENT;
      char agent[255];
      sprintf(agent, tpl, OS_TYPE, CPU_ARCH, MIKE_VERSION);
      return agent;
    } else {
      return customUserAgent_;
    }
  }
  
  bool Browser::isJavaEnabled()
  {
    return javaEnabled_;
  }

  bool Browser::isCookieEnabled()
  {
    return cookieEnabled_;
  }

  BrowserWindow* Browser::Open(string url)
  {
    return new BrowserWindow(this, url);
  }
}
