# This module provides very basic methods for files manipulation.
# To be clear it just provides methods to read stuff, distinguinsh
# types and operate paths.

sys = require('sys');
file = {}

# Default path separator. So far we're supporting only *nix systems
# so we can hardcode slash here.
file.pathSeparator = "/"

# Native functions.

file.read = $mike.File.read
file.exists = $mike.File.exists
file.isDirectory = $mike.File.isDirectory
file.isFile = $mike.File.isFile

# Joins few strings into single path to file.
#
#   file.join('foo', 'bar', '/bla/la) # => 'foo/bar/bla/la'
#
file.join = (paths...) ->
  path = paths.join(file.pathSeparator)
  path.replace(/\/+/g, '/')

# Returns absolute path to given file.
#
#   sys.cwd('/home/foo');
#   file.absolute('../bar/bla'); # => /home/bar/bla
#
file.absolute = (path) ->
  result = []
  parts = file.join(sys.pwd(), path).split(file.pathSeparator)
  for part in parts
    if part == '..'
      result.pop()
    else if part != '.'
      result.push(part)
  result.join(file.pathSeparator)

return file