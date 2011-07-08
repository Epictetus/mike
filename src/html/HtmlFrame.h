#ifndef _MIKE_HTML_FRAME_H_
#define _MIKE_HTML_FRAME_H_

#include <string>
#include <exception>

#include "Frame.h"

namespace mike
{
  using namespace std;
  
  class HtmlPage;
  class Frame;
  
  /**
   * Error raised when specified frame index is out of range.
   */
  class FrameNotExistsError : public exception
  {
  public:
    explicit FrameNotExistsError() {};
    virtual ~FrameNotExistsError() throw() {};
    virtual const char* what() const throw() { return "Frame index out of range"; }
  };

  /**
   * Error raised when specified named frame does not exist.
   */
  class NamedFrameNotExistsError : public FrameNotExistsError
  {
  public:
    explicit NamedFrameNotExistsError(string name) : name_(name) {}
    virtual ~NamedFrameNotExistsError() throw() {};
    virtual const char* what() const throw() { return ("Frame " + name_ + " doesn't exist").c_str(); }
  protected:
    string name_;
  };

  /**
   * Frame adjusted to HTML manipulation purposes. This frames are used as all HTML iframes/frames
   * representation to avoid redundant typecasting to HtmlPage.
   */
  class HtmlFrame : public Frame
  {
  public:
    explicit HtmlFrame(Frame* frame);
    HtmlPage* getPage() const;
    HtmlPage* getEnclosedPage() const;
  };
}

#endif /* _MIKE_HTML_FRAME_H_ */
