sys = require('sys');
file = require('fs');

tests = {};

sys.system('touch /tmp/test-file');
sys.system('mkdir -p /tmp/test-dir');

tests.testExists = function() {
    assert.ok(file.exists('/tmp/test-dir'));
    assert.ok(!file.exists('/tmp/test-not-exists'));
};

tests.testIsDirectory = function() {
    assert.ok(!file.isDirectory('/tmp/test-file'));
    assert.ok(file.isDirectory('/tmp/test-dir'));
}

tests.testIsFile = function() {
    assert.ok(file.isFile('/tmp/test-file'));
    assert.ok(!file.isFile('/tmp/test-dir'));
}

tests.testRead = function() {
    sys.system('echo "foobar" > /tmp/test-file');
    assert.equal(file.read("/tmp/test-file"), "foobar\n");
    assert.equal(file.read("/tmp/test-notexists"), null);
}

tests.testJoin = function() {
    assert.equal(file.join("foo", "bar/bla", "/bla"), "foo/bar/bla/bla");
}

tests.testAbsolute = function() {
    path = sys.pwd().split('/')
    path.pop()
    path = path.join('/')
    assert.equal(file.absolute("../foo"), path+"/foo");
}

tests;