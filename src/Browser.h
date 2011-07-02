#ifndef _MIKE_BROWSER_H_
#define _MIKE_BROWSER_H_

#include <string>
#include <list>

namespace mike
{
  using namespace std;

  class Page;
  class Window;

  /**
   * Error raised when trying to get window which is not open in particular browser instance.
   */
  class WindowNotExistsError
  {
  public:
    const char* getReason() const { return "Window index out of range"; }
    const char* operator*() { return getReason(); }
  };
  
  /**
   * Instance of this class represents single, separatelly configured browser. You can configure
   * browser by passing various parameters to constructor (configurable language, user agent string
   * and cookies/javascript availability).
   *
   * \code
   *   Browser* browser = new Browser("en", "", true, true); // language, custom user agent, cookies, javascript
   *   HtmlPage* page = (HtmlPage*)browser->open("http://www.mypage.com");
   *   assert(page->getTitle() == "Hello My Page!");
   *   browser.closeAll();
   *   delete browser;
   * \endcode
   */
  class Browser
  {
  public:
    /**
     * Creates configured browser instance.
     *
     * \param language The language used by this browser instance.
     * \param user_agent Custom user agent string.
     * \param enable_cookie Should this instance allow to store cookies?
     * \param enable_javascript Should this instance allow to execute javascript?
     */
    explicit Browser(string language="en", string user_agent="",
		     bool enable_cookie=true, bool enable_java=true);

    /**
     * Destructor.
     */
    ~Browser();

    /**
     * \return Language used by browser.
     */
    string getLanguage() const;

    /**
     * \return User agent string assigned to this browser.
     */
    string getUserAgent() const;

    /**
     * \return Unique token of this session.
     */
    string getSessionToken() const;

    /**
     * Returns list of all currently opened windows.
     *
     * \code
     *   browser->open("http://www.mikebrowser.com/");
     *   browser->open("http://www.cuboxsa.com");
     *   list<Window*> windows = browser->getWindows();
     *   assert(windows.size() == 2);
     * \endcode
     */
    list<Window*> getWindows();

    /**
     * Returns specified window if opened, otherwise throws 'WindowNotFound' error.
     *
     * \code
     *   browser->open("http://www.cuboxsa.com/");
     *   Window* window = browser->getWindow(0);
     *   assert(window->getUrl(), "http://www.cuboxsa.com");
     * \endcode
     *
     * \param n Index of window to get.
     */
    Window* getWindow(int n);
    
    /**
     * \return True when javascript is enabled. 
     */
    bool isJavaEnabled() const;
    bool isJavaScriptEnabled() const;

    /**
     * \return True when cookies are enabled.
     */
    bool isCookieEnabled() const;

    /**
     * Enables cookies handling.
     */
    void enableCookies();

    /**
     * Disables cookies handling.
     */
    void disableCookies();
    
    /**
     * Closes all windows opened within current instance (called automatically when browser object
     * is deleted).
     *
     * \code
     *   Browser* browser = new Browser();
     *   browser->open("http://www.cuboxsa.com");
     *   browser->open("http://www.mikebrowser.com");
     *   //...
     *   browser->closeAll();
     *   browser->open("http://www.cuboxsa.com");
     *   //...
     *   delete browser; // closeAll is called here automatically...
     * \endcode
     */
    void closeAll();
    void closeAllWindows();

    /**
     * Closes window beeing under specified index on the list. If specified window doesn't
     * exist then nothing happen. Second version closes and removes specified window from the
     * list of opened.
     *
     * \code
     *   browser->open("http://www.mikebrowser.com/");
     *   browser->open("http://www.cuboxsa.com/");
     *   browser->closeWindow(1);
     *   browser->closeWindow(browser->getWindow(0));
     * \endcode
     *
     * \param n Index of window to close.
     * \param window Window instance to close.
     */
    void closeWindow(int n);
    void closeWindow(Window* window);
    
    /**
     * Opens specified url in new virtual window, and returns loaded page. You can also use
     * the getPage() alias.
     * 
     * \code
     *   HtmlPage* page = (HtmlPage*)browser->open("http://www.google.com/");
     *   assert(page->getTitle() == "Google Search");
     *   assert(page->getContent() == "...");
     *   // ...
     * \endcode
     *
     * \param url Address of page to open. 
     */
    Page* open(string url);
    Page* getPage(string url);
    
  protected:
    bool javaEnabled_;
    bool cookieEnabled_;
    string language_;
    string customUserAgent_;
    string sessionToken_;
    list<Window*> windows_;

    /**
     * Generates UUID token for current browser instance.
     */
    void generateSessionToken();
  };
}

#endif /* _MIKE_BROWSER_H_ */
