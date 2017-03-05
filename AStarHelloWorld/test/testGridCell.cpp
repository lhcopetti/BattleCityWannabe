/*
 * testGridCell.cpp
 *
 *  Created on: 5 de mar de 2017
 *      Author: Pichau
 */

#include "GridCell.h"
#include "gtest/gtest.h"

TEST(GridCellTest, GridCellInitialState) {
	GridCell g(0, 0);
	EXPECT_EQ(g.heuristic(), 0);
	EXPECT_EQ(g.movementCost(), 0);
	EXPECT_EQ(g.parent(), nullptr);
}

TEST(GridCellTest, GridCostTest) {
	GridCell g(0, 0);
	g.heuristic(50);
	g.movementCost(20);
	EXPECT_EQ(g.cost(), 50 + 20);
}

TEST(GridCellTest, GridEqualityTest) {
	GridCell g1(10, 5);
	GridCell g2(10, 5);
	EXPECT_EQ(g1, g2);
}

TEST(GridCellTest, GridInequalityTest) {
	GridCell g1(10, 5);
	GridCell g2(10, 5);
	EXPECT_EQ(g1, g2);
	g2.x(9);
	EXPECT_NE(g1, g2);
}
