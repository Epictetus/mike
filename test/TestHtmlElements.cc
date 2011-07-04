#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string.h>

#include "utils/CppunitMacros.h"
#include "html/HtmlPage.h"

using namespace std;
using namespace mike;

#define CHECK_ELEM_GETTER(name)			\
  elem->get##name();

#define CHECK_ELEM_CHECKER(name)		\
  elem->has##name();				\
  elem->has##name("test");

#define CHECK_ELEM_ATTR(name)			\
  CHECK_ELEM_GETTER(name);			\
  CHECK_ELEM_CHECKER(name);

#define CHECK_CORE_ATTRS			\
  CHECK_ELEM_ATTR(Id);				\
  CHECK_ELEM_ATTR(Style);			\
  CHECK_ELEM_ATTR(Title);			\
  CHECK_ELEM_ATTR(Class);

#define CHECK_I18N_ATTRS			\
  CHECK_ELEM_ATTR(Lang);			\
  CHECK_ELEM_ATTR(XmlLang);			\
  CHECK_ELEM_ATTR(Dir);

#define CHECK_EVENT_ATTRS			\
  CHECK_ELEM_ATTR(OnClick);			\
  CHECK_ELEM_ATTR(OnDblClick);			\
  CHECK_ELEM_ATTR(OnMouseDown);			\
  CHECK_ELEM_ATTR(OnMouseUp);			\
  CHECK_ELEM_ATTR(OnMouseOver);			\
  CHECK_ELEM_ATTR(OnMouseOut);			\
  CHECK_ELEM_ATTR(OnMouseMove);			\
  CHECK_ELEM_ATTR(OnKeyPress);			\
  CHECK_ELEM_ATTR(OnKeyDown);			\
  CHECK_ELEM_ATTR(OnKeyDown);

#define CHECK_ACCESS_ATTRS			\
  CHECK_ELEM_ATTR(Accesskey);			\
  CHECK_ELEM_ATTR(TabIndex);			\
  CHECK_ELEM_ATTR(OnFocus);			\
  CHECK_ELEM_ATTR(OnBlur);

#define CHECK_HALIGN_ATTRS			\
  CHECK_ELEM_ATTR(Align);			\
  CHECK_ELEM_ATTR(Char);			\
  CHECK_ELEM_ATTR(CharOff);

#define CHECK_VALIGN_ATTRS			\
  CHECK_ELEM_ATTR(VAlign);

#define CHECK_DEFAULT_ATTRS			\
  CHECK_CORE_ATTRS;				\
  CHECK_I18N_ATTRS;				\
  CHECK_EVENT_ATTRS;

#define TEST_CASE_FOR_ELEM(klass, xpath)				\
  void test##klass() {							\
    klass* elem = page->getElementByXpath(xpath)->cast<klass>();	\

#define TEST_CASE_END \
  }

class MikeHtmlElementsTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(MikeHtmlElementsTest);
  //CPPUNIT_TEST(testHtmlHtmlElement);
  //CPPUNIT_TEST(testHtmlHeadElement);
  //CPPUNIT_TEST(testHtmlDivElement);
  //CPPUNIT_TEST(testHtmlTrElement);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp()
  {
    page = (HtmlPage*)Page::Open("http://localhost:4567/all-elements.html");
  }

  void tearDown()
  {
    delete page;
  }

protected:
  HtmlPage* page;

  TEST_CASE_FOR_ELEM(HtmlHtmlElement, "//html")
  {
    CHECK_I18N_ATTRS;
    CHECK_ELEM_ATTR(Id);
    CHECK_ELEM_ATTR(XmlNs);
  }
  TEST_CASE_END;

  TEST_CASE_FOR_ELEM(HtmlHeadElement, "//head")
  {
    CHECK_I18N_ATTRS;
    CHECK_ELEM_ATTR(Id);
    CHECK_ELEM_ATTR(Profile);
  }
  TEST_CASE_END;

  TEST_CASE_FOR_ELEM(HtmlDivElement, "//div")
  {
    CHECK_DEFAULT_ATTRS;
  }
  TEST_CASE_END;

  
  TEST_CASE_FOR_ELEM(HtmlTrElement, "//tr")
  {
    CHECK_DEFAULT_ATTRS;
    CHECK_VALIGN_ATTRS;
    CHECK_HALIGN_ATTRS;
  }
  TEST_CASE_END;

};

CPPUNIT_TEST_SUITE_REGISTRATION(MikeHtmlElementsTest);
