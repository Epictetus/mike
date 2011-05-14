# This module provides very basic methods for files manipulation.
# To be clear it just provides methods to read stuff, distinguinsh
# types and operate paths.

file = {}

# Default path separator. So far we're supporting only *nix systems
# so we can hardcode slash here.
file.pathSeparator = "/"

# Native functions.

file.read = File.read
file.exists = File.exists
file.isDirectory = File.isDirectory
file.isFile = File.isFile

# Joins few strings into single path to file.
file.join = (paths...) ->
  path = paths.join(file.pathSeparator)
  path.replace(/\/+/g, '/')

return file