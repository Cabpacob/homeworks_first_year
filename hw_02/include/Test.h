#pragma once 
#include <vector>
#include <cstdlib>
#include <iostream>
#include <assert.h>

#define DO_CHECK(expr) Test::check((expr), __func__, __FILE__, __LINE__)

class Test
{
protected:
	static int32_t failed;
	static int32_t total;

	static void check(bool expr, const char *func, const char  *filename, size_t lineNum); 

public:
	static bool show_final_results();
	virtual void run_all_tests() = 0;

};

