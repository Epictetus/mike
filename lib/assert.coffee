# The assert module provides functions that throw AssertionError's
# when particular conditions are not met. The assert module must conform
# to the following interface.

class AssertionError extends Error
  constructor: (options) ->
    @name = 'AssertionError'
    @message = options.message
    @actual = options.actual
    @expected = options.expected
    @operator = options.operator
    @startStackFunction = options.startStackFunction || fail

    if (Error.captureStackTrace)
      Error.captureStackTrace(this, @startStackFunction)

  toString: ->
    if @message
      [@name+":", @message].join(" ")
    else
      [@name+":", @expected+"", @operator, @actual+""].join(" ")

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
    startStackFunction: startStackFunction
  })

# Pure assertion tests whether a value is truthy, as determined
# by !!guard.
ok = (guard, message) ->
  if !value
    fail(value, true, message, '==', ok)

# The equality assertion tests shallow, coercive equality with ==.
equal = (actual, expected, message) ->
  if actual != expected
    fail(actual, expected, message, '==', equal)

# The non-equality assertion tests for whether two objects are not
# equal with !=.
notEqual = (actual, expected, message) ->
  if actual == expected
    fail(actual, expected, message, '!=', notEqual)

# The strict equality assertion tests strict equality, as determined
# by ===.
strictEqual = (actual, expected, message) ->
  if actual isnt expected
    fail(actual, expected, message, '===', strictEqual)

# The strict non-equality assertion tests for strict inequality,
# as determined by !==.
notStrictEqual = (actual, expected, message) ->
  if actual is expected
    fail(actual, expected, message, '!==', notStrictEqual)

# Expected to throw an error.
throws = (block, errorclass, message) ->
  try
    block()
  catch error
    if (!(error instanceof errorclass))
      fail(error, errorclass, 'instanceof', message)
