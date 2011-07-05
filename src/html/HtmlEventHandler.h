#ifndef _MIKE_HTML_EVENT_HANDLER_H_
#define _MIKE_HTML_EVENT_HANDLER_H_

#include <string>

namespace mike
{
  using namespace std;

  class HtmlPage;
  class HtmlElement;

  /**
   * Eeach HTML page contains its event handler, which handles all kind of events
   * and operations on elements.
   */
  class HtmlEventHandler
  {
  public:
    /**
     * Creates new event handler.
     *
     * \param page Owner page.
     */
    HtmlEventHandler(HtmlPage* page);

    /**
     * Destructor.
     */
    virtual ~HtmlEventHandler();


  protected:
    HtmlPage* page_;
  };
}

#endif /* _MIKE_HTML_EVENT_HANDLER_H_ */
