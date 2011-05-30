#include "mike/navigator.h"

namespace mike
{
  Navigator::Navigator(pFrame f)
    : frame(f)
  {
  }
  
  Navigator::~Navigator()
  {
  }

  string Navigator::AppName() const
  {
    return "Netscape";
  }

  string Navigator::AppVersion() const
  {
    const string agent = UserAgent();
    return agent.substr(agent.find('/')+1);
  }

  string Navigator::UserAgent() const
  {
    return frame->Window()->UserAgent();
  }

  string Navigator::AppCodeName() const
  {
    return "Mozilla";
  }

  string Navigator::Platform() const
  {
    return "Gecko";
  }

  string Navigator::Vendor() const
  {
    return "Mike - the Headless Browser!";
  }

  string Navigator::Language() const
  {
    return frame->Window()->Language();
  }
  
  bool Navigator::OnLine() const
  {
    return true;
  }

  bool Navigator::JavaEnabled() const
  {
    return frame->Window()->IsJavaEnabled();
  }

  bool Navigator::CookieEnabled() const
  {
    return frame->Window()->IsCookieEnabled();
  }
}
