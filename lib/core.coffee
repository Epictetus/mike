# The core module provides basic stuff like `require`, `print`, `puts`
# methods, common exception classes, etc.

# Placeholder for already loaded modules.
loadedModules = {}

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
  $mike.Stdout.write(text.toString()) for text in texts

# Writes given args to stdout line `print`, but with newline
# at the end.
@puts = (texts...) ->
  print(texts, "\n")

# Extended version of `require` function. This one caches already
# loaded modules.
@require = (module) ->
  if typeof(loadedModules[module]) == 'undefined'
    loadedModules[module] = $mike.require(module)
  return loadedModules[module]
