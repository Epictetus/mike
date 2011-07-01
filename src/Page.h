#ifndef _MIKE_PAGE_H_
#define _MIKE_PAGE_H_

#include <string>
#include <sstream>
#include "http/Request.h"

namespace mike
{
  using namespace std;
  using namespace http;

  class RegularPage;
  class XmlPage;
  class HtmlPage;

  class Frame;
  class Window;
  
  /**
   * Available page types. 
   *
   */
  enum PageType {
    UNKNOWN_PAGE,
    XML_PAGE,
    HTML_PAGE,
    TEXT_PAGE,
    BINARY_PAGE
  };
  
  /**
   * Object of this class represents single page loaded by corresponding request.
   * This is base class for all complex kinds of pages, like HTML, XML, Text page, etc.
   *
   */
  class Page
  {
  public:
    static Page* Open(string url);
    
    /**
     * Performs given request, and depending on response content type build proper
     * page object for it. Example: 
     *
     * <code>
     *   http::Request* req = http::Request::Get("http://www.mikebrowser.com/");
     *   Page* page = Page::Build(req);
     *   // ...
     *   delete page;
     * </code>
     *
     * Note: you don't need to delete req object, it will be done automatically on page destroy.
     *
     */
    static Page* Factory(Request* request);

    /**
     * Constructor.
     *
     */
    explicit Page(Request* request, PageType type=UNKNOWN_PAGE);
    
    /**
     * Destructor.
     *
     */
    virtual ~Page();

    /**
     * Returns HTTP request built for this page.
     *
     */
    Request* getRequest();

    /**
     * Returns HTTP response built for this page.
     *
     */
    Response* getResponse();

    /**
     * Requrns request url of this website.
     *
     */
    string getUrl();

    /**
     * Returns string stream with content of this page;
     *
     */
    stringstream* getStream();

    /**
     * Returns strinc content of this page.
     *
     */
    string getContent();
   
    /**
     * Returns <code>true</code> when current page is an XML or HTML page.
     *
     */
    bool isXml();

    /**
     * Returns <code>true</code> when current page is an HTML page.
     *
     */
    bool isHtml();

    /**
     * Returns <code>true</code> when page has been properly loaded.
     *
     */
    virtual bool isLoaded();
    
    /**
     * Performs request to this page once again and reloads everything.
     *
     */
    virtual void reload();

    /**
     * Opens specified page in given frame.
     *
     */
    virtual void openInFrame(Frame* frame);

    /**
     * Returns frame in which current page has been rendered.
     *
     */
    Frame* getEnclosingFrame();

    /**
     * Returns window which contains frame with this page.
     *
     */
    Window* getEnclosingWindow();
    
  protected:
    http::Request* request_;
    PageType type_;
    Frame* frame_;
  };
}

#endif /* _MIKE_PAGE_H_ */
