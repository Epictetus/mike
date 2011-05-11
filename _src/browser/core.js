(function() {
  var __slice = Array.prototype.slice;
  this.print = function() {
    var text, texts, _i, _len;
    texts = 1 <= arguments.length ? __slice.call(arguments, 0) : [];
    for (_i = 0, _len = texts.length; _i < _len; _i++) {
      text = texts[_i];
      $stdout.write(text.toString());
    }
    return true;
  };
  this.puts = function() {
    var texts;
    texts = 1 <= arguments.length ? __slice.call(arguments, 0) : [];
    return print(texts, "\n");
  };
  this.require = function(file) {
    return null;
  };
}).call(this);
