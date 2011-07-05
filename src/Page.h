#ifndef _MIKE_PAGE_H_
#define _MIKE_PAGE_H_

#include <string>
#include <sstream>

#include "http/Request.h"
#include "Window.h"

namespace mike
{
  using namespace std;
  using namespace http;
  
  class XmlPage;
  class HtmlPage;
  
  /**
   * Available page types.
   */
  enum PageType {
    kUnknownPage,
    kBinaryPage,
    kTextPage,
    kXmlPage,
    kHtmlPage
  };
  
  /**
   * This is base class for any kind of pages opened in browser. You should never create
   * instances directly, only use the 'Open' method for simple get page, and Factory' method
   * for more complex requests.
   */
  class Page
  {
    friend class Window;
    friend class HtmlPage;
    friend class XmlPage;
    
  public:
    /**
     * Performs GET request on specified URL and returns page object of appropriate type.
     *
     * \code
     *   Page* page = Page::Open("http://www.mikebrowser.com");
     *   assert(page->isHtml());
     *   //...
     *   delete page;
     * \endcode
     *
     * \param url URL to open.
     * \param cookie_enabled Enable cookies?
     * \param session_token Unique session id.
     * \param force_base Forces usage of base class instead of type-specific.
     * \return Page object.
     */
    static Page* Open(string url, bool cookie_enabled=false, string session_token="",
		      bool force_base=false);
    
    /**
     * Performs given request, and depending on response content type creates new instance of
     * appropriate type. 
     *
     * \code
     *   Request* request = Request::Post("http://www.mypage.com/form");
     *   request->setPostData("foo=bar&spam=eggs");
     *   Page* page = Page::Factory(request);
     *   //...
     *   delete page;
     * \endcode
     *
     * Note: you don't need to delete req object, this will be done automatically on page destroy.
     *
     * \param request Request to perform.
     * \param force_base Forces usage of base class instead of type-specific.
     * \return Page object.
     */
    static Page* Factory(Request* request, bool force_base=false);

    /**
     * Creates new page instance. Don't call it directly, use 'Factory' or 'Open' instead. 
     *
     * \param request Performed request for this page.
     * \param type Kind of page.
     */
    explicit Page(Request* request, PageType type=kUnknownPage);
    
    /**
     * Destructor.
     */
    virtual ~Page();

    /**
     * \return HTTP request built for the page.
     */
    Request* getRequest();

    /**
     * \return HTTP response for the page.
     */
    Response* getResponse();

    /**
     * \requrn URL address of the page.
     */
    string getUrl();

    /**
     * \return Stream with content of the page.
     */
    stringstream* getStream();

    /**
     * \return Content of the page as string.
     */
    string getContent();
   
    /**
     * \return Whether page is an XML document or not.
     */
    bool isXml();

    /**
     * \return Whether page is an HTML document or not.
     */
    bool isHtml();

    /**
     * Reloads page using request passed to constructor.
     */
    virtual void reload();

    /**
     * \return Frame in which current page has been rendered.
     */
    Frame* getEnclosingFrame();

    /**
     * \return Window which contains frame with this page.
     */
    Window* getEnclosingWindow();

    /**
     * Returns absolute URL based on current or if absolute addres passed then
     * just returns it.
     *
     * \param url Relative URL
     * \return Absolute url based on current.
     */
    string getUrlFor(string url);

  protected:
    http::Request* request_;
    PageType type_;
    Frame* frame_;
    void* ref_;
    
    /**
     * Opens the page in given frame. For the security reasons each instance can
     * be enclosed only once.
     *
     * \param frame Frame in which this page should be opened.
     */
    virtual void enclose(Frame* frame);
  };
}

#include "PageRef.h"

#endif /* _MIKE_PAGE_H_ */
