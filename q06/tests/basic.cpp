/**
 * Created: FA17
 *      Lab_trees
 *
 * Modified:
 *      By:
 */
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "catchlib.h"

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include "../binarytree.h"


using namespace std;
using namespace util;


TEST_CASE("trivial") {
	REQUIRE( 1ul == 1ul );
}

int main(int argc, char* argv[])
{
	int result = Catch::Session().run(argc, argv);

	return (result < 0xFF ? result : 0xFF);
}