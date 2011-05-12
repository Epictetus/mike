# Writes given args to stdout.
@print = (texts...) ->
  Stdout.write text.toString() for text in texts

# Writes given args to stdout line `print`, but with newline
# at the end.
@puts = (texts...) ->
  print(texts, "\n")