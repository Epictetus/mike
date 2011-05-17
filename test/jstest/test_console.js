assert = require('assert');
console = require('console');

var out_strings = [];
var err_strings = [];
var dummy_out_write = function(string) { out_strings.push(string); };
var dummy_err_write = function(string) { err_strings.push(string); };
var stdout_write = $mike.Stdout.write;
var stderr_write = $mike.Stderr.write;

var redirectStreams = function(block) {
    $mike.Stdout.write = dummy_out_write;
    $mike.Stderr.write = dummy_err_write;
    var error = null;
    
    try {
	block();
    } catch(e) {
	error = e;
    } finally {
	$mike.Stdout.write = stdout_write;
	$mike.Stderr.write = stderr_write;

	if (error !== null) {
	    throw(error)
	}
    }
}

tests = {};

tests.testSimpleLog = function() {
    redirectStreams(function() {
	console.log('foo');
	assert.equal("foo\n", out_strings.shift());
    });
}

tests.testLogFewItems = function() {
    redirectStreams(function() {
	console.log('foo', 'bar');
	assert.equal("foo bar\n", out_strings.shift());
    });
}

tests.testFormattedLog = function() {
    redirectStreams(function() {
	console.log('%s %s', 'this', 'is', 'sparta!');
	assert.equal("this is sparta!\n", out_strings.shift());
    });
}

tests.testLogDebug = function() {
    redirectStreams(function() {
	console.debug('foo');
	assert.equal("DEBUG: foo\n", out_strings.shift());
    });
}

tests.testLogInfo = function() {
    redirectStreams(function() {
	console.info('foo');
	assert.equal("INFO: foo\n", out_strings.shift());
    });
}

tests.testLogError = function() {
    redirectStreams(function() {
	console.error('foo');
	assert.equal("ERROR: foo\n", err_strings.shift());
    });
}

tests.testLogWarn = function() {
    redirectStreams(function() {
	console.warn('foo');
	assert.equal("WARNING: foo\n", err_strings.shift());
    });
}

tests;