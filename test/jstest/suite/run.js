result = test.run(suite);

if (result == 0) {
    puts("\n\n\nOK (", test.passed, " tests)");
} else {
    var i, len;
    var failures = test.failures;

    puts("\n\n!!!FAILURES!!!");
    puts("Test Results:");
    puts("Run:  ", result+test.passed, "   Failures:  ", result, "\n");
    
    for (i = 0; i < result; i++) {
	var failure = failures[i]; 
	puts((i+1) + ") "+ failure.name);
	puts(failure.error.toString());
    }
}

puts("\n");
result == 0;
