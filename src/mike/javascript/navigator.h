#ifndef _MIKE_NAVIGATOR_H_
#define _MIKE_NAVIGATOR_H_

#include <stdlib.h>
#include <string>
#include "mike/frame.h"

using namespace std;

namespace mike
{
  class Frame;
  class Navigator;
  
  typedef Frame* pFrame;
  typedef Navigator* pNavigator;
  
  class Navigator {
  private:
    pFrame frame;
  public:
    Navigator(pFrame f);
    virtual ~Navigator();
    string AppName() const;
    string AppVersion() const;
    string UserAgent() const;
    string Platform() const;
    string AppCodeName() const;
    string Product() const;
    string Vendor() const;
    string Language() const;
    bool OnLine() const;
    bool JavaEnabled() const;
    bool CookieEnabled() const;
    //Geolocation* Geolocation() const;
    //DOMMimeTypeArray MimeTypes() const;
    //DOMPluginArray Plugins() const;
  };
}

#endif /* _MIKE_NAVIGATOR_H_ */
