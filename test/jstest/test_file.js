sys = require('sys');
file = require('file');
suite.testFile = {};

sys.system('touch /tmp/test-file');
sys.system('mkdir -p /tmp/test-dir');

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
    sys.system('echo "foobar" > /tmp/test-file');
    assert.equal(file.read("/tmp/test-file"), "foobar\n");
    assert.equal(file.read("/tmp/test-notexists"), null);
}

suite.testFile.testJoin = function() {
    assert.equal(file.join("foo", "bar/bla", "/bla"), "foo/bar/bla/bla");
}

suite.testFile.testAbsolute = function() {
    path = sys.pwd().split('/')
    path.pop()
    path = path.join('/')
    assert.equal(file.absolute("../foo"), path+"/foo");
}