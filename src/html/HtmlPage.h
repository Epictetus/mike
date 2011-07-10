#ifndef _MIKE_HTML_PAGE_H_
#define _MIKE_HTML_PAGE_H_

#include <libxml/HTMLparser.h>
#include <string>
#include <vector>

#include "xml/XmlPage.h"
#include "html/HtmlElement.h"
#include "html/HtmlFrame.h"
#include "html/HtmlEventHandler.h"
#include "javascript/JavaScriptHandler.h"

namespace mike
{
  using namespace std;

  class Window;
  class Browser;

  /**
   * Available locator types.
   */
  enum LocatorType {
    kByPath,
    kByXpath,
    kByCss,
    kById
  };
  
  /**
   * HTML page representation.
   */
  class HtmlPage : public XmlPage
  {
    friend class Window;
    
  public:
    explicit HtmlPage(Request* request);
    virtual ~HtmlPage();

    // override
    vector<HtmlElement*> getElementsByXpath(string xpath);
    vector<HtmlElement*> getElementsByTagName(string tag);
    HtmlElement* getElementByXpath(string xpath);
    HtmlElement* getElementByPath(string path);

    virtual void reload();

    /**
     * Returns set of elements matching given CSS rule.
     *
     * \code
     *   vector<HtmlElement*> items = page->getElementsByCss("ul#items li");
     * \endcode
     *
     * \param rule CSS rule.
     * \return Matching elements.
     */
    vector<HtmlElement*> getElementsByCss(string rule);

    /**
     * The same as 'getElementsByCss', but returns only the first element.
     *
     * \param rule CSS rule;
     * \return First matching element.
     */
    HtmlElement* getElementByCss(string rule);
    
    /**
     * Returns all elements with given class name.
     *
     * \code
     *   vector<HtmlElement*> tags = page->getElementsByClassName("tag");
     * \endcode
     *
     * \param klass Class name to find.
     * \return Elements with specified class name.
     */
    vector<HtmlElement*> getElementsByClassName(string klass);

    /**
     * Returns first found element with given ID. If no elements found then ElementNotFoundError
     * will be thrown.
     *
     * \code
     *   HtmlElement* header = page->getElementById("header");
     * \endcode
     *
     * \param id ID to find.
     * \return Element with specified id. 
     */
    HtmlElement* getElementById(string id);

    /**
     * Locates link or button on a page. It can be find by id, name or text.
     *
     * \code
     *   HtmlElement* link = page->getLinkOrButton("Click me!");
     *   HtmlElement* button = page->getLinkOrButton("submit_button");
     *   HtmlElement* named_link = page->getLinkOrButton("foo-link");
     * \endcode
     *
     * \param locator Name, ID or text of the link/button.
     * \return Element matching given locator.
     */
    // TODO: change result to HtmlClicableElement or smth...
    HtmlElement* getLinkOrButton(string locator);

    /**
     * Locates link on the page. It can be find by id, name or text.
     *
     * \code
     *   HtmlElement* link = page->getLink("Click me!");
     *   HtmlElement* named_link = page->getLink("foo-link");
     * \endcode
     *
     * \param locator Name, ID or text of the link.
     * \return Link matching given locator.
     */
    // TODO: change result to HtmlAnchorElement
    HtmlElement* getLink(string locator);

    /**
     * Locates button on the page. It can be find by id, name or text.
     *
     * \code
     *   HtmlElement* button = page->getButton("Click me!");
     *   HtmlElement* submit_button = page->getButton("submit");
     * \endcode
     *
     * \param locator Name, ID or text of the button.
     * \return Button matching given locator.
     */
    // TODO: change result to HtmlButtonElement
    HtmlElement* getButton(string locator);

    /**
     * Locates form field on the page. It can be find by id, name or label text.
     *
     * \code
     *   HtmlElement* user_name_field = page->getField("user[name]");
     *   HtmlElement* password_field = page->getField("Password");
     * \endcode
     *
     * \param locator Name, ID or label of the field.
     * \return Field matching given locator.
     */
    // TODO: change result to HtmlFormFieldElement or smth...
    HtmlElement* getField(string locator);

    /**
     * Locates element using given locator. If no locator specified then acts exacltly 
     * the same as 'getLinkOrButton' method.
     *
     * \param type Locator type.
     * \param locator XPath, CSS rule, ID or link/button property.
     * \return Element matching given locator.
     */
    HtmlElement* getElement(LocatorType type, string locator);
    HtmlElement* getElement(string locator);
    
    /**
     * \return Page title text.
     */
    string getTitle();
    string getTitleText();

    /**
     * \return All frames from within this page.
     */
    vector<HtmlFrame*>& getFrames();

    /**
     * If number given then returns frame from given index on the list, if string
     * then tries to find named frame.
     *
     * \param n Frame index.
     * \param name Frame name.
     * \return Specified frame.
     */
    HtmlFrame* getFrame(int n);
    HtmlFrame* getFrame(string name);
    HtmlFrame* getNamedFrame(string name);

    /**
     * Evaluates given javascript within page context.
     *
     * \param script Code to evaluate.
     * \return Result of evaluated expression (as string).
     */
    string evaluate(string script);

    void click(string locator);
    void click(LocatorType type, string locator);
    void clickLinkOrButton(string locator);
    void clickLink(string locator);
    void clickButton(string locator);
    void pressButton(string locator);
    
  protected:
    htmlDocPtr doc_;
    HtmlEventHandler* eventHandler_;
    JavaScriptHandler* javaScriptHandler_;
    vector<HtmlFrame*> frames_;
    
    // override
    virtual void enclose(Frame* frame);
    virtual void parseDocument();
    virtual XmlElement* newElement(xmlNodePtr);
    
    /**
     * Processes all javascripts within this page.
     */
    void processScripts();

    /**
     * Checks whether all expected popups appears during scripts execution.
     */
    void checkExpectations();
    
    /**
     * Loads specified asset file content to given pointer.
     *
     * \param url File to load.
     * \param content Ponter to which file content will be loaded.
     * \return Whether file has been loaded or not;
     */
    bool loadAsset(string uri, string* content);
    
    /**
     * Loads all iframes and frames, and opens them in virtual frames.
     */
    void loadFrames();

    /**
     * Removes all contents from within "<noscript>...</noscript>" nodes.
     */
    void removeNoScriptNodes();
  };
}

#endif /* _MIKE_HTML_PAGE_H_ */
