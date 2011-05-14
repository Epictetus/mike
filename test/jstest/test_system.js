suite.testSystem = {};

suite.testSystem.testSystem = function() {
    assert.equal(System.system('pwd'), 0);
    System.system('touch /tmp/test-system');
    assert.ok(File.exists('/tmp/test-system'));
}

suite.testSystem.testPwd = function() {
    assert.ok(System.pwd().match(/test$/));
}

suite.testSystem.testCwd = function() {
    assert.ok(!System.cwd('not-exists'));
    assert.ok(System.cwd('jstest'));
    assert.ok(System.pwd().match(/test\/jstest$/));
    System.cwd('..');
}
