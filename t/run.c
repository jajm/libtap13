#include "tap.h"
#include <stdio.h>

int run(void (*test_plan)(void), char *expected[], unsigned int n)
{
	FILE *tempfile;
	char buf[BUFSIZ];
	char *p;
	unsigned int i;

	tempfile = tmpfile();
	if (!tempfile) {
		skip_all("Cannot create temporary file");
		return EXIT_FAILURE;
	}
	tap_set_stream(tempfile);

	test_plan();

	tap_reset();
	plan(n + 1);
	rewind(tempfile);
	for (i = 0; i < n; i++) {
		if (NULL == fgets(buf, BUFSIZ, tempfile)) {
			fail("line %d should exists", i+1);
			continue;
		}

		if ((p = strrchr(buf, '\n'))) {
			*p = '\0';
		}
		str_eq(buf, expected[i], "line %d is \"%s\"", i+1, expected[i],
			"{got: '%s', expected: '%s'}", buf, expected[i]);
	}

	ok(NULL == fgets(buf, BUFSIZ, tempfile), "line %d should not exists", i+1);

	fclose(tempfile);

	return EXIT_SUCCESS;
}
