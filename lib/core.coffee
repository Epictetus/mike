_require = @require

# This error is raised when given module can't be loaded using
# `require` function.
class LoadError extends Error
  constructor: (module) ->
    @module = module
  toString: ->
    "No such module to load: " + @module

# Writes given args to stdout.
@print = (texts...) ->
  Stdout.write text.toString() for text in texts

# Writes given args to stdout line `print`, but with newline
# at the end.
@puts = (texts...) ->
  print(texts, "\n")

# Extended version of `require` function.
@require = (module) ->
  exports = _require(module)
  unless exports?
    throw new LoadError(module)