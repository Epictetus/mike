#ifndef _MIKE_BROWSER_WINDOW_H_
#define _MIKE_BROWSER_WINDOW_H_

#include <string>
#include "Browser.h"
#include "Page.h"

namespace mike
{
  using namespace std;

  class BrowserFrame;

  /**
   * Object of this class represents single window opened within browser instance. Such browser
   * window contains main frame with loaded specified page. Window can belong to other windows
   * (eg. simulating popups) and guarrantees session continuation within opened domains. 
   *
   */
  class BrowserWindow
  {
  public:
    /**
     * Constructors.
     *
     */
    explicit BrowserWindow(Browser* browser, string url);
    explicit BrowserWindow(BrowserWindow* parent_window, string url);

    /**
     * Destructor.
     *
     */
    virtual ~BrowserWindow();

    /**
     * Returns instance of browser within which this window has been created.
     *
     */
    Browser* getBrowser();

    /**
     * Returns the window that contains this one. If this is top level window then it
     * will return itself.
     * 
     */
    BrowserWindow* getParentWindow();

    /**
     * Returns the top level window that contains this one. If this is top level window 
     * then it will return itself.
     *
     */
    BrowserWindow* getTopLevelWindow();

    /**
     * Returns main frame with content of this window. 
     *
     */
    BrowserFrame* getFrame();

    /**
     * Returns page object which represents page loaded into main frame.  
     *
     */
    Page* getPage();

    /**
     * Returns address of currently open page.
     *
     */
    string getUrl();

    /**
     * Opens specified url and loads it into main frame. 
     *
     */
    void goTo(string url);
    
  protected:
    BrowserWindow* parentWindow_;
    BrowserFrame* frame_;
    Browser* browser_;
  };
}

#endif /* _MIKE_BROWSER_WINDOW_H_ */
