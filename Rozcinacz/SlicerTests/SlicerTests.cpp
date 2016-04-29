// SlicerTests.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include <Graph.h>
#define ELPP_DISABLE_LOGS
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

TEST(testGraph, graphInitTest)
{
	Graph graph(6);
	EXPECT_EQ(6, graph.Size());
}