#include "tap.h"

int main()
{
	plan(19);

	ok(0);
	ok(0, "should fail");
	ok(0, "should fail too", "{ reason: 'test is 0', data: [1, 2, 3] }");
	ok(1);
	ok(1, "should succeed");
	ok(1, "should succeed", "[]");

	todo("lot of stuff to do") {
		ok(0, "this will fail");
		ok(1, "this will pass");
	}

	skip_if(1, 2, "skip 2 tests with no reason") {
		ok(1, "we don't get there");
		ok(1, "we don't get there");
	}

	diag("Diagnostic: %s:%d (%s)", __FILE__, __LINE__, __func__);

	pass("Pass");
	fail("Fail");

	int got = 1, expected = 1;

	is(got, expected, "1 == 1", "{ got: %d, expected: %d }", got, expected);
	expected = 2;
	is(got, expected, "1 == 2", "{ got: %d, expected: %d }", got, expected);
	isnt(1, 1, "1 != 1");
	isnt(1, 2, "1 != 2");

	str_eq("foo", "foo", "'foo' == 'foo'");
	str_eq("foo", "bar", "'foo' == 'bar'");

	ok(0, "test yaml diagnostic", "[aa, bb, {a: [1, 2], b: {c: 'foo'}}, cc]");

	return 0;
}
