#include "html/HtmlEventHandler.h"
#include "html/HtmlPage.h"
#include "html/HtmlElement.h"

namespace mike
{
  HtmlEventHandler::HtmlEventHandler(HtmlPage* page)
  {
    page_ = page;
  }

  HtmlEventHandler::~HtmlEventHandler()
  {
  }
}
