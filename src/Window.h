#ifndef _MIKE_BROWSER_WINDOW_H_
#define _MIKE_BROWSER_WINDOW_H_

#include <string>
#include <vector>

namespace mike
{
  using namespace std;

  class Browser;
  class Frame;
  class Page;
  
  /**
   * Represents single window opened within browser instance. Window can be related with
   * browser directly or through parent window (eg. for popup simulation). Objects of this
   * class shouldn't be actually created directly, mainly they are kind of anchors which
   * controlls everything under the hood.
   *
   * \code
   *   Window* window = new Window(browser, 1280, 1024);
   *   window->setPage(Page::Open("http://www.cuboxsa.com/");
   *   //...
   *   window->close();
   * \endcode
   */
  class Window
  {
  public:
    // Default window proportions.
    static const int DEFAULT_WIDTH  = 1280;
    static const int DEFAULT_HEIGHT = 1024;
    
    /**
     * Creates instance of Window related to given browser or parent window.
     *
     * \param browser Browser containing this window.
     * \param parent Parent window containing this one.
     * \param width Window width.
     * \param height Window height.
     */
    explicit Window(Browser* browser, int width=DEFAULT_WIDTH, int height=DEFAULT_HEIGHT);
    explicit Window(Window* parent, int width=DEFAULT_WIDTH, int height=DEFAULT_HEIGHT);
    explicit Window(int width, int height);
    
    /**
     * Destructor.
     */
    virtual ~Window();

    /**
     * \return Instance of browser within which this window has been created.
     */
    Browser* getBrowser();

    /**
     * Returns the window that contains this one. If this is top level window then it
     * will return itself.
     *
     * \return Parent window.
     */
    Window* getParent();
    Window* getParentWindow();

    /**
     * Returns the top level window that contains this one. If this is top level window 
     * then it will return itself.
     *
     * \return Top level window.
     */
    Window* getTopLevel();
    Window* getTopLevelWindow();

    /**
     * Renders given page within  this window. 
     *
     * \param page Page to set
     */
    void setPage(Page* page);
    
    /**
     * \return Page loaded into main frame.
     */
    Page* getPage();

    /**
     * \return URL of currently opened page.
     */
    string getUrl();

    /**
     * \return Window width;
     */
    int getWidth();

    /**
     * \return Window width;
     */
    int getHeight();
    
    /**
     * Returns true if there is no page opened in this window.
     *
     * \return Page state
     */
    bool isBlank();
    
    /**
     * Closes this page and removes it from browser's references.
     */
    void close();
    
    /**
     * Changes width to given value.
     *
     * \param w New width.
     */
    void resizeX(int w);
    void setWidth(int w);

    /**
     * Changes height to given value.
     *
     * \param h New height.
     */
    void resizeY(int h);
    void setHeight(int h);

    /**
     * Changes window's size.
     *
     * \param w New width
     * \param h New height
     */
    void resize(int w, int h);
    
  protected:
    int width_;
    int height_;
    Browser* browser_;
    Window* parent_;
    Frame* frame_;

    /**
     * DRY initializer used in all constructors.
     */
    void init(int width, int height, Window* parent);
  };
}

#endif /* _MIKE_BROWSER_WINDOW_H_ */
