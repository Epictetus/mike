var AssertionError, assert, test, suite;

(function() {
    var __hasProp = Object.prototype.hasOwnProperty;
    var __extends = function(child, parent) {
	for (var key in parent) { if (__hasProp.call(parent, key)) { child[key] = parent[key]; } }
	function ctor() { this.constructor = child; }
	ctor.prototype = parent.prototype;
	child.prototype = new ctor;
	child.__super__ = parent.prototype;
	return child;
    };
    
    AssertionError = (function() {
	__extends(AssertionError, Error);

	function AssertionError(options) {
	    this.name = 'AssertionError';
	    this.message = options.message;
	    this.actual = options.actual;
	    this.expected = options.expected;
	    this.operator = options.operator;
	    this.stackStartFunction = options.stackStartFunction || fail;
	    if (Error.captureStackTrace) {
		Error.captureStackTrace(this, this.stackStartFunction);
	    }
	}
	AssertionError.prototype.toString = function() {
	    var msg;
	    if (this.message) {
		msg = this.message;
	    } else {
		msg = "assertion failed";
	    }
	    return msg + "\n- Expression: " + this.expected + " " + this.operator + " " + this.actual;
	};
	return AssertionError;
    })();

    var __fail = function(actual, expected, message, operator, stackStartFunction) {
	throw new AssertionError({
	    message: message,
	    expected: expected,
	    actual: actual,
	    operator: operator,
	    stackStartFunction: stackStartFunction
	});
    };
    
    assert = {
	ok: function(guard, message) {
	    if (!guard) {
		return __fail(guard, true, message, '==', assert.ok);
	    }
	},
	equal: function(actual, expected, message) {
	    if (actual !== expected) {
		return __fail(actual, expected, message, '==', assert.equal);
	    }
	},
	notEqual: function(actual, expected, message) {
	    if (actual === expected) {
		return __fail(actual, expected, message, '!=', assert.notEqual);
	    }
	},
	strictEqual: function(actual, expected, message) {
	    if (actual !== expected) {
		return __fail(actual, expected, message, '===', assert.strictEqual);
	    }
	},
	notStrictEqual: function(actual, expected, message) {
	    if (actual === expected) {
		return __fail(actual, expected, message, '!==', assert.notStrictEqual);
	    }
	},
	throws: function(block, errorclass, message) {
	    try {
		return block();
	    } catch (error) {
		if (!(error instanceof errorclass)) {
		    return __fail(error, errorclass, message, 'instanceof', assert.throws);
		}
	    }
	},
    };

    test = {
	failures: [],
	passed: 0,
	run: function(suite) {
	    var block, name, result;
	    result = 0;
	    for (name in suite) {
		block = suite[name];
		if (name.match(/^(describe|test)(.+)$/)) {
		    if (typeof block === "function") {
			try {
			    block();
			    print(".");
			    test.passed += 1;
			} catch (err) {
			    if (err instanceof AssertionError) {
				print("F");
			    } else {
				print("E");
			    }
			    test.failures.push({
				name: name,
				error: err
			    });
			    result += 1;
			}
		    } else if (typeof block === "object") {
			result += test.run(block);
		    }
		}
	    }
	    return result;
	}
    }

    suite = {};
}).call(this);