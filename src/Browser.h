#ifndef _MIKE_BROWSER_H_
#define _MIKE_BROWSER_H_

#include <string>
#include <list>

namespace mike
{
  using namespace std;

  class Page;
  class Window;

  namespace glue
  {
    class Window;
  }
  
  /**
   * Error raised when trying to get window which is not open in particular browser instance.
   */
  class WindowNotExistsError
  {
  public:
    const char* getReason() const { return "Window index out of range"; }
    const char* operator*() { return getReason(); }
  };

  enum PopupType {
    kPopupAlert,
    kPopupConfirm
  };

  enum PopupExpectationFlag {
    kMatchMessage = 1,
    kSkipMessage = 2
  };
  
  typedef struct popup_expectation {
    PopupExpectationFlag flags;
    PopupType kind;
    string message;
    string choice;
  } PopupExpectation;
  
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
    friend class glue::Window;
    
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
     * Creates new empty window and returns it.
     *
     * \return New window.
     */
    Window* newWindow();
    
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
    list<Window*>& getWindows();

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
     * Enables javascript processing.
     */
    void enableJava();
    void enableJavaScript();

    /**
     * Disables javascript processing.
     */
    void disableJava();
    void disableJavaScript();
    
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

    /**
     * Sets expectation of one alert box with any message.
     */
    void expectAlert();

    /**
     * Sets expectation of one alert box with given message.
     *
     * \param msg Expected message.
     */
    void expectAlert(string msg);

    /**
     * Sets expectation of given number of alerts with any message.
     *
     * \param n Number of expected alerts.
     */
    void expectAlerts(int n);

    /**
     * Sets expectation of one confirmation box with any message, and sets prefered choice
     * for it.
     *
     * \param choice Prefered choice (true = Yes, false = No).
     */
    void expectConfirmation(bool choice);

    /**
     * Sets expectation of one confirmation box with given message, and sets prefered choice
     * for it.
     *
     * \param msg Expected message.
     * \param bool Prefered choice.
     */
    void expectConfirmation(string text, bool choice);

    /**
     * Sets expectation of given number of confirmationswith given message, and sets prefered
     * choice for all of them.
     *
     * \param n Number of expected windows.
     * \param bool Prefered choice.
     */
    void expectConfirmations(int n, bool choice);
    
  protected:
    bool javaEnabled_;
    bool cookieEnabled_;
    string language_;
    string customUserAgent_;
    string sessionToken_;
    list<Window*> windows_;
    list<PopupExpectation> expected_popups_;

    /**
     * Generates UUID token for current browser instance.
     */
    void generateSessionToken();
  };
}

#endif /* _MIKE_BROWSER_H_ */
