#include "html/HtmlAnchorElement.h"
#include "html/HtmlPage.h"
#include "Browser.h"
#include "Window.h"

namespace mike
{
  HtmlAnchorElement::HtmlAnchorElement(HtmlPage* page, xmlNodePtr node)
    : HtmlElement(page, node)
  {
  }

  bool HtmlAnchorElement::click()
  {
    if (HtmlElement::click()) {
      // Get link attributes.
      bool new_window = hasAttribute("target", "blank_");
      string url = page_->getUrlFor(getAttribute("href"));

      // Select in which window page should be opened (current or new).
      Window* window = new_window ? getBrowser()->newWindow() : page_->getEnclosingWindow();

      // Prepare request.
      Request* request = Request::Get(url);
      request->enableCookieSession(getBrowser()->isCookieEnabled(), getBrowser()->getSessionToken());
      request->setReferer(page_->getUrl());

      // Load page.
      Page* page = Page::Factory(request);
      window->setPage(page);

      return true;
    }

    return false;
  }
}
