#include <assert.h>
#include <stdio.h>
#include "tap.h"
#include "run.h"

void test_plan(void)
{
	plan(10);

	ok(0);
	ok(0, "testing 0");
	ok(0, "testing %d", 0);
	ok(0, "testing %d", 0, "{test: 0}");
	ok(0, "testing %d", 0, "{test: %d}", 0);

	ok(1);
	ok(1, "testing 1");
	ok(1, "testing %d", 1);
	ok(1, "testing %d", 1, "{test: 1}");
	ok(1, "testing %d", 1, "{test: %d}", 1);

	fail();
	fail("explicit fail");
	fail("explicit fail", "[1,2,3]");

	pass();
	pass("explicit pass");
}

int main()
{
	char *expected[] = {
		"TAP version 13",
		"1..10",
		"not ok 1 in test_plan (basic.t.c:10)",
		"not ok 2 testing 0 in test_plan (basic.t.c:11)",
		"not ok 3 testing 0 in test_plan (basic.t.c:12)",
		"not ok 4 testing 0 in test_plan (basic.t.c:13)",
		"  ---",
		"  test: 0",
		"  ...",
		"not ok 5 testing 0 in test_plan (basic.t.c:14)",
		"  ---",
		"  test: 0",
		"  ...",
		"ok 6",
		"ok 7 testing 1",
		"ok 8 testing 1",
		"ok 9 testing 1",
		"ok 10 testing 1",
		"not ok 11 in test_plan (basic.t.c:22)",
		"not ok 12 explicit fail in test_plan (basic.t.c:23)",
		"not ok 13 explicit fail in test_plan (basic.t.c:24)",
		"  ---",
		"  - 1",
		"  - 2",
		"  - 3",
		"  ...",
		"ok 14",
		"ok 15 explicit pass",
	};

	return run(test_plan, expected);
}
