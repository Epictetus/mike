# The "test" module provides a "run" method that runs unit tests
# and catalogs their results. The "run" method must return the total
# number of failures, suitable for use as a process exit status code.

assert = require('assert')
test = {}

# Collection of assertion errors encountered in test suites.
test.failures = []
# Number of passed cases.
test.passed = 0

# Accepts any `Object`, usually a unit test module's exports. It will scan
# the object for all functions and object properties that have names that
# begin with but are not equal to "test", and other properties for specific
# flags. Sub-objects with names that start with but are not equal to "test"
# will be run as sub-tests.
#
#   test = require("test");
#   assert = require("assert");
#   var suite = {testFoobar: {}};
#
#   suite.testFoobar.testFoo = function() {
#     assert.ok("foo");
#   });
#   suite.testFoobar.testBar = function() {
#     assert.equal("bar", "bar");
#   });
#   suite.testSomethingElse = function() {
#     assert.equal("something", "something");
#   });
#
#   test.run(suite);
#
test.run = (suite) ->
  result = 0
  for name, block of suite
    if name.match(/^test(.+)$/)
      if typeof(block) == "function"
        try
          block()
          print(".")
          test.passed += 1
        catch err
          if err instanceof assert.AssertionError
            print("F")
          else
            print("E")
          test.failures.push({name: name, error: err})
          result += 1
      else if typeof(block) == "object"
        result += test.run(block)
  return result

return test