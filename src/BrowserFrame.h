#ifndef _MIKE_BROWSER_FRAME_H_
#define _MIKE_BROWSER_FRAME_H_

#include <string>
#include "Browser.h"
#include "BrowserWindow.h"
#include "Page.h"
#include "History.h"

namespace mike
{
  using namespace std;
  
  class BrowserFrame
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit BrowserFrame(BrowserWindow* window);

    /**
     * Destructor.
     *
     */
    virtual ~BrowserFrame();

    /**
     * Returns url of currently open page. 
     *
     */
    string getUrl();

    /**
     * Returns currentlu open page instance. 
     *
     */
    Page* getCurrentPage();

    /**
     * Retuns history container for this frame.
     *
     */
    History* getHistory();

    /**
     * Returns window which contains this frame.
     *
     */
    BrowserWindow* getWindow();
    
  protected:
    BrowserWindow* window_;
    History* history_;
  };
}

#endif /* _MIKE_FRAME_H_ */
