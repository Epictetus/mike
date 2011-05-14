sys = require('sys');
file = require('file');
suite.testSystem = {};

suite.testSystem.testSystem = function() {
    assert.equal(sys.system('pwd'), 0);
    sys.system('touch /tmp/test-system');
    assert.ok(file.exists('/tmp/test-system'));
}

suite.testSystem.testPwd = function() {
    assert.ok(sys.pwd().match(/test$/));
}

suite.testSystem.testCwd = function() {
    assert.ok(!sys.cwd('not-exists'));
    assert.ok(sys.cwd('jstest'));
    assert.ok(sys.pwd().match(/test\/jstest$/));
    sys.cwd('..');
}
