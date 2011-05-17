# - core.js -
#
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
    "#{@name} : no such module to load -- #{@module}"

# Writes given args to stdout.
@print = () ->
  $mike.Stdout.write(arg.toString()) for arg in arguments

# Writes given args to stdout line `print`, but with newline
# at the end.
@puts = () ->
  $mike.Stdout.write(arg.toString()) for arg in arguments
  $mike.Stdout.write("\n")

# Writes given args to stderr, and adds newline at the end.
@error = () ->
  $mike.Stderr.write(arg.toString()) for arg in arguments
  $mike.Stderr.write("\n")

# Extended version of `require` function. This one caches already
# loaded modules.
@require = (module) ->
  if typeof(loadedModules[module]) == 'undefined'
    loadedModules[module] = $mike.require(module)
  return loadedModules[module]

# This method should be used to inform user that called method is not
# implemented in mike.
@notImplemented = (what) ->
  @error(what + ' not implemented.')
