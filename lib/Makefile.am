javascript_files = \
	core.js \
	assert.js \
	test.js

mikelibdir = $(datarootdir)/mike/site-javascript
mikelib_DATA = $(javascript_files)

.coffee.js:
	-$(COFFEE) -c $<
clean-local:
	-$(RM) -f *.js
