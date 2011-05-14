file = require('file');
suite.testFile = {};

System.system('touch /tmp/test-file');
System.system('mkdir -p /tmp/test-dir');

suite.testFile.testExists = function() {
    assert.ok(file.exists('/tmp/test-dir'));
    assert.ok(!file.exists('/tmp/test-not-exists'));
};

suite.testFile.testIsDirectory = function() {
    assert.ok(!file.isDirectory('/tmp/test-file'));
    assert.ok(file.isDirectory('/tmp/test-dir'));
}

suite.testFile.testIsFile = function() {
    assert.ok(file.isFile('/tmp/test-file'));
    assert.ok(!file.isFile('/tmp/test-dir'));
}

suite.testFile.testRead = function() {
    System.system('echo "foobar" > /tmp/test-file');
    assert.equal(file.read("/tmp/test-file"), "foobar\n");
    assert.equal(file.read("/tmp/test-notexists"), null);
}

suite.testFile.testJoin = function() {
    assert.equal(file.join("foo", "bar/bla", "/bla"), "foo/bar/bla/bla");
}