#include "tap.h"

int main()
{
	plan(18);

	ok(0);
	ok(0, "should fail");
	ok(0, "should fail too", "[]");
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

	is(1, 1, "1 == 1");
	is(1, 2, "1 == 2");
	isnt(1, 1, "1 != 1");
	isnt(1, 2, "1 != 2");

	str_eq("foo", "foo", "'foo' == 'foo'");
	str_eq("foo", "bar", "'foo' == 'bar'");

	return 0;
}
