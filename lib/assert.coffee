# The assert module provides functions that throw AssertionError's
# when particular conditions are not met. The assert module must conform
# to the following interface.

assert = {}

# The `AssertionError` should be used to inform about all failed assertions.
class AssertionError extends Error
  constructor: (options) ->
    @name = 'AssertionError'
    @message = options.message
    @actual = options.actual
    @expected = options.expected
    @operator = options.operator
    @stackStartFunction = options.stackStartFunction || fail

    if (Error.captureStackTrace)
      Error.captureStackTrace(this, @stackStartFunction)

  toString: ->
    if @message
      [@name+":", @message].join(" ")
    else
      [@name+":", @expected+"", @operator, @actual+""].join(" ")

assert.AssertionError = AssertionError

# All of the following functions must throw an AssertionError
# when a corresponding condition is not met, with a message that
# may be undefined if not provided.  All assertion methods provide
# both the actual and expected values to the assertion error for
# display purposes.

fail = (actual, expected, message, operator, stackStartFunction) ->
  throw new AssertionError({
    message: message,
    expected: expected,
    actual: actual,
    operator: operator,
    stackStartFunction: stackStartFunction
  })

# Pure assertion tests whether a value is truthy, as determined
# by !!guard.
assert.ok = (guard, message) ->
  if !guard
    fail(guard, true, message, '==', assert.ok)

# The equality assertion tests shallow, coercive equality with ==.
assert.equal = (actual, expected, message) ->
  if actual != expected
    fail(actual, expected, message, '==', assert.equal)

# The non-equality assertion tests for whether two objects are not
# equal with !=.
assert.notEqual = (actual, expected, message) ->
  if actual == expected
    fail(actual, expected, message, '!=', assert.notEqual)

# The strict equality assertion tests strict equality, as determined
# by ===.
assert.strictEqual = (actual, expected, message) ->
  if actual isnt expected
    fail(actual, expected, message, '===', assert.strictEqual)

# The strict non-equality assertion tests for strict inequality,
# as determined by !==.
assert.notStrictEqual = (actual, expected, message) ->
  if actual is expected
    fail(actual, expected, message, '!==', assert.notStrictEqual)

# Expected to throw an error.
assert.throws = (block, errorclass, message) ->
  try
    block()
  catch error
    if !(error instanceof errorclass)
      fail(error, errorclass, message, 'instanceof', assert.throws)

return assert
