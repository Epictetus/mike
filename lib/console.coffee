# - console.js -
#
# Console is a well known logging facility to all the JS devs. By utilizing
# this standard interface which is almost identical across all major browsers,
# we will gain from familiarity from the developers. console is not a replacement
# for a `print` or any other full featured logging API, it may be an easily
# available default instance of a logger or a wrapper on `print`. Message
# representation and implementation is up to the platform provider.

logFormatted: (args, level) ->
  return 0

notImplemented: (method) ->
  puts("NotImplemented: Console#" + method)

class Console
  # Logs a message to with visual "log" representation allowing user to distinguish
  # form other message types. You may pass as many arguments as you'd like, and they
  # will be joined together in a space-delimited line.
  #
  # The first argument to log may be a string containing printf-like string
  # substitution patterns. For example:
  #
  #   require("console").log("The %s jumped over %d tall buildings", animal, count);
  #
  log: () ->
    logFormatted(arguments)

  # Logs a message, with a visual "debug" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  debug: () ->
    logFormatted(arguments, 'DEBUG')

  # Logs a message with the visual "info" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  info: () ->
    logFormatted(arguments, 'INFO')

  # Logs a message with the visual "warning" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  warn: () ->
    logFormatted(arguments, 'WARNING')

  # Logs a message with the visual "error" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  error: (obj) ->
    logFormatted(arguments, 'ERROR')

  # Logs a static / interactive stack trace of JavaScript execution at the point
  # where it is called. Details that platform is able to provide is most likely will
  # be different there for it's up to platform, some may provide full stack trace
  # like the functions on the stack, as well as the values that were passed as
  # arguments to each function. While others may log just a module require graph.
  trace: () ->
    notImplemented('trace')

  # Logs a static / interactive listing of all properties of the object.
  dir: () ->
    notImplemented('dir')

  # Logs the XML source tree of an HTML or XML element. Even though there is no
  # CommonJS standards for XML, HTML yet most likely there will be one at some
  # point. In order to keep compatibility with well known console from browsers,
  # platform should implement this and may decide to default for a log or dir
  # described above.
  dirxml: () ->
    notImplemented('dirxml')