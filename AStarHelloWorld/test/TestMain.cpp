/*
 * TestMain.cpp
 *
 *  Created on: 5 de mar de 2017
 *      Author: Pichau
 */

#include "gtest/gtest.h"

#ifdef UNIT_TEST_BUILD

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif
