sys = require('sys');

tests = {};

tests.testSystem = function() {
    assert.equal(sys.system('pwd'), 0);
    sys.system('touch /tmp/test-system');
    assert.ok(file.exists('/tmp/test-system'));
}

tests.testPwd = function() {
    assert.ok(sys.pwd().match(/test$/));
}

tests.testCwd = function() {
    assert.ok(!sys.cwd('not-exists'));
    assert.ok(sys.cwd('jstest'));
    assert.ok(sys.pwd().match(/test\/jstest$/));
    sys.cwd('..');
}

tests;