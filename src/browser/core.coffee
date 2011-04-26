# Writes given args to stdout.
#
#   print "Hello", "\n", " world!" # displays "Hello\n world!"
#
print = (texts...) ->
  $stdout.write text.toString() for text in texts
  true

# Writes given args to stdout line `print`, but with newline
# at the end.
#
#   puts "Hello", " ", "world!" # displays "Hello world!\n"
#
puts = (texts...) ->
  print texts, "\n"
