suite["test foo"] = {
    "test if foo is foo": function() {
	assert.equal("foo", "foo");
    },
    "test if bar is bar": function() {
	assert.equal("bar", "bar");
    }
}