# Original `require` function from C implementation.
_require = @require

# This error is raised when given module can't be loaded using
# `require` function.
class LoadError extends Error
  constructor: (module) ->
    @name = "LoadError"
    @module = module

  toString: ->
    [@name, ": no such module to load -- ", @module].join("")

# Writes given args to stdout.
@print = (texts...) ->
  Stdout.write text.toString() for text in texts

# Writes given args to stdout line `print`, but with newline
# at the end.
@puts = (texts...) ->
  print(texts, "\n")

# Extended version of `require` function. This one raises appropriate
# error when module can't be loaded.
@require = (module) ->
  exports = _require(module)
  unless exports?
    throw new LoadError(module)
