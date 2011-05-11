coffies:
	-$(FIND) . -name "*.coffee" | xargs $(COFFEE) -c
clean-local:
	-$(RM) -f *.js
all: coffies

.PHONY: coffies

javascript_files = \
	core.js

mikelibdir = $(datarootdir)/mike/site-javascript
mikelib_DATA = $(javascript_files)