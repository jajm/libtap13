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

	is(0, 1);
	is(0, 1, "is 0 == 1 ?");
	is(0, 1, "is %d == %d ?", 0, 1);
	is(0, 1, "is 0 == 1 ?", "[1]");
	is(0, 1, "is %d == %d ?", 0, 1, "[%d]", 1);

	is(1, 1);
	is(1, 1, "is 1 == 1 ?");
	is(1, 1, "is %d == %d ?", 1, 1);
	is(1, 1, "is 1 == 1 ?", "[1]");
	is(1, 1, "is %d == %d ?", 1, 1, "[%d]", 1);

	isnt(0, 1);
	isnt(0, 1, "is 0 != 1 ?");
	isnt(0, 1, "is %d != %d ?", 0, 1);
	isnt(0, 1, "is 0 != 1 ?", "[1]");
	isnt(0, 1, "is %d != %d ?", 0, 1, "[%d]", 1);

	isnt(1, 1);
	isnt(1, 1, "is 1 != 1 ?");
	isnt(1, 1, "is %d != %d ?", 1, 1);
	isnt(1, 1, "is 1 != 1 ?", "[1]");
	isnt(1, 1, "is %d != %d ?", 1, 1, "[%d]", 1);
}

int main()
{
	char *expected[] = {
		"TAP version 13",
		"1..10",
		"not ok 1 in test_plan (" __FILE__ ":10)",
		"not ok 2 testing 0 in test_plan (" __FILE__ ":11)",
		"not ok 3 testing 0 in test_plan (" __FILE__ ":12)",
		"not ok 4 testing 0 in test_plan (" __FILE__ ":13)",
		"  ---",
		"  test: 0",
		"  ...",
		"not ok 5 testing 0 in test_plan (" __FILE__ ":14)",
		"  ---",
		"  test: 0",
		"  ...",
		"ok 6",
		"ok 7 testing 1",
		"ok 8 testing 1",
		"ok 9 testing 1",
		"ok 10 testing 1",
		"not ok 11 in test_plan (" __FILE__ ":22)",
		"not ok 12 explicit fail in test_plan (" __FILE__ ":23)",
		"not ok 13 explicit fail in test_plan (" __FILE__ ":24)",
		"  ---",
		"  - 1",
		"  - 2",
		"  - 3",
		"  ...",
		"ok 14",
		"ok 15 explicit pass",
		"not ok 16 in test_plan (" __FILE__ ":29)",
		"not ok 17 is 0 == 1 ? in test_plan (" __FILE__ ":30)",
		"not ok 18 is 0 == 1 ? in test_plan (" __FILE__ ":31)",
		"not ok 19 is 0 == 1 ? in test_plan (" __FILE__ ":32)",
		"  ---",
		"  - 1",
		"  ...",
		"not ok 20 is 0 == 1 ? in test_plan (" __FILE__ ":33)",
		"  ---",
		"  - 1",
		"  ...",
		"ok 21",
		"ok 22 is 1 == 1 ?",
		"ok 23 is 1 == 1 ?",
		"ok 24 is 1 == 1 ?",
		"ok 25 is 1 == 1 ?",
		"ok 26",
		"ok 27 is 0 != 1 ?",
		"ok 28 is 0 != 1 ?",
		"ok 29 is 0 != 1 ?",
		"ok 30 is 0 != 1 ?",
		"not ok 31 in test_plan (" __FILE__ ":47)",
		"not ok 32 is 1 != 1 ? in test_plan (" __FILE__ ":48)",
		"not ok 33 is 1 != 1 ? in test_plan (" __FILE__ ":49)",
		"not ok 34 is 1 != 1 ? in test_plan (" __FILE__ ":50)",
		"  ---",
		"  - 1",
		"  ...",
		"not ok 35 is 1 != 1 ? in test_plan (" __FILE__ ":51)",
		"  ---",
		"  - 1",
		"  ...",
	};

	return run(test_plan, expected);
}
