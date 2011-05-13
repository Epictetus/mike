# Collection of assertion errors encountered in test suites.
errors = []

# Runs given list of test suites. The "run" method must return the
# total number of failures, suitable for use as a process exit status
# code. The idiom for a self-running test module program would be:
#
#   test = require("test");
#   assert = require("assert");
#   var suite = {name: "foobar"};
#
#   suite["foo should be"] = function() {
#     assert.ok("foo");
#   });
#   suite["bar shuld be bar"] = function() {
#     assert.equal("bar", "bar");
#   });
#
#   test.run(suite);
#
run = (suites...) ->
  result = 0
  for suite in suites
    for name, block in suite
      continue if name == 'name'
      try
        block()
      catch err
        errors.push({suite: suite.name, name: test, error: err})
        result += 1