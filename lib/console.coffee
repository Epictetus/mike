# - console.js -
#
# Console is a well known logging facility to all the JS devs. By utilizing
# this standard interface which is almost identical across all major browsers,
# we will gain from familiarity from the developers. console is not a replacement
# for a `print` or any other full featured logging API, it may be an easily
# available default instance of a logger or a wrapper on `print`. Message
# representation and implementation is up to the platform provider.

# Just represents object as string.
# TODO: In the future we can implement something more useful, like inspect...
toString = (object) ->
  try
    object+''
  catch e
    null

# Basic formatting regexp.
formatRegexp = /%[sdj]/g

# Prepares given arguments for append to logs. Implementation partially borrowed
# from node.js.
formatString = (args) ->
  format = args[0]
  if typeof format isnt 'string'
    objects = []
    objects.push(toString(object)) for object in arguments
    return objects.join('')
  i = 1
  str = String(format).replace formatRegexp, (x) ->
    switch x
      when '%s' then return String(args[i++])
      when '%d' then return Number(args[i++])
      when '%j' then return JSON.stringify(arguments[i++])
      else
        return x
  while (i < args.length)
    obj = args[i++]
    str += ' '+toString(obj)
  return str

# Logs formated arguments for given level.
logFormatted = (level, args) ->
  if level == 'ERROR' or level == 'WARNING'
    out = $mike.Stderr
  else
    out = $mike.Stdout
  if level?
    out.write([level, ": ", formatString(args), "\n"].join(''))
  else
    out.write([formatString(args), "\n"].join(''))


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
    logFormatted(null, arguments)

  # Logs a message, with a visual "debug" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  debug: () ->
    logFormatted('DEBUG', arguments)

  # Logs a message with the visual "info" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  info: () ->
    logFormatted('INFO', arguments)

  # Logs a message with the visual "warning" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  warn: () ->
    logFormatted('WARNING', arguments)

  # Logs a message with the visual "error" representation. Optionally includes an
  # info of a caller (file, line where it was called from).
  error: (obj) ->
    logFormatted('ERROR', arguments)

  # Logs a static / interactive stack trace of JavaScript execution at the point
  # where it is called. Details that platform is able to provide is most likely will
  # be different there for it's up to platform, some may provide full stack trace
  # like the functions on the stack, as well as the values that were passed as
  # arguments to each function. While others may log just a module require graph.
  #
  # This implementation has been borrowed from node.js.
  trace: () ->
    e = new Error()
    e.name = 'Trace'
    e.message = label or ''
    Error.captureStackTrace(e, arguments.callee)
    error(e.stack)

  # Logs a static / interactive listing of all properties of the object.
  dir: (object) ->
    notImplemented("Console#dir")

  # Logs the XML source tree of an HTML or XML element. Even though there is no
  # CommonJS standards for XML, HTML yet most likely there will be one at some
  # point. In order to keep compatibility with well known console from browsers,
  # platform should implement this and may decide to default for a log or dir
  # described above.
  dirxml: (node) ->
    notImplemented("Console#dirxml")

  # Tests that an expression is true. If not, logs a message and throws an exception.
  assert: (expression, objetcts...) ->
    notImplemented("Console#assert")

  # Logs a message to and opens a nested block to indent all future messages sent.
  # Call require("console").groupEnd() to close the block. Representation of block
  # is up to the platform, it can be an interactive block or just a set of indented
  # sub messages.
  group: (objects...) ->
    notImplemented("Console#group")

  # Closes the most recently opened block created by a call to require("console").group()
  # or require("console").groupCollapsed()
  groupEnd: () ->
    notImplemented("Console#groupEnd")

  # Creates a new timer under the given name. Call require("console").timeEnd(name)
  # with the same name to stop the timer and log the time elapsed.
  time: (name) ->
    notImplemented("Console#time")

  # Stops a timer created by a call to require("console").time(name) and logs the
  # time elapsed.
  timeEnd: (name) ->
    notImplemented("Console#timeEnd")

  # Turns on profiler. The optional argument title would contain the text to be
  # logged in the header of the profile report. Data included in a report generated
  # by a profiler is up to platform.
  profile: (title) ->
    notImplemented("Console#profile")

  # Turns off profiler and logs its report.
  profileEnd: () ->
    notImplemented("Console#profileEnd")

  # Writes the number of times that the line of code where count was called was
  # executed. The optional argument title will print a message in addition to
  # the number of the count.
  count: (title) ->
    notImplemented("Console#count")

return new Console();