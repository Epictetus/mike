#ifndef _MIKE_BROWSER_FRAME_H_
#define _MIKE_BROWSER_FRAME_H_

#include <vector>
#include <string>
#include "Browser.h"
#include "Window.h"
#include "Page.h"
#include "History.h"

namespace mike
{
  using namespace std;
  
  class Frame
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit Frame(Window* window);

    /**
     * Destructor.
     *
     */
    virtual ~Frame();

    /**
     * This method should be called always before opening new page within this frame.
     *
     */
    void cleanup();
    
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
    Window* getWindow();

    /**
     * Returns name of this frame.
     *
     */
    string getName();

    /**
     * Sets name of this frame.
     * 
     */
    void setName(string name);
    
    /**
     * Creates new sub frame and returns pointer to it.
     *
     */
    Frame* buildFrame();

    /**
     * Returns all sub frames from this frame.
     *
     */
    vector<Frame*> getFrames();

    /**
     * Returns frame from given index. If list of frames doesn't have
     * such index then <code>NULL</code> will be returned.
     *
     */
    Frame* getFrame(int key);

    /**
     * Returns frame with specified name. If there is no such frame then
     * <code>NULL</code> will be returned. 
     *
     */
    Frame* getNamedFrame(string name);

    /**
     * Returns content of currently opened page.
     *
     */
    string getContent();
    
  protected:
    string name_;
    Window* window_;
    History* history_;
    vector<Frame*> frames_;
  };
}

#endif /* _MIKE_FRAME_H_ */
