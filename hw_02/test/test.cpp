#include "Test.h"

int32_t Test::total = 0;
int32_t Test::failed = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum)
{
	total++;
	if(!expr)
	{
		std::cout << "Test failed: line " << lineNum << " in " << func << " in file " << filename << std::endl;
		failed++;
	}
}

bool Test::show_final_results()
{
	std::cout << failed << " tests failed " << total - failed << " passed" << std::endl;
	return (failed == 0);
}

