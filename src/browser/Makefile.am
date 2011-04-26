coffies:
	-$(FIND) . -name "*.coffee" | xargs $(COFFEE) -c
clean-local:
	-$(RM) -f *.js
all: coffies

.PHONY: coffies