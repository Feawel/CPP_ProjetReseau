/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_TestBuilding_init = false;
#include "/Users/Jonathan/CPP_ProjetReseau/TestBuilding.h"

static TestBuilding suite_TestBuilding;

static CxxTest::List Tests_TestBuilding = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestBuilding( "TestBuilding.h", 6, "TestBuilding", suite_TestBuilding, Tests_TestBuilding );

static class TestDescription_suite_TestBuilding_testGetFloors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestBuilding_testGetFloors() : CxxTest::RealTestDescription( Tests_TestBuilding, suiteDescription_TestBuilding, 10, "testGetFloors" ) {}
 void runTest() { suite_TestBuilding.testGetFloors(); }
} testDescription_suite_TestBuilding_testGetFloors;

static class TestDescription_suite_TestBuilding_testIsAdmin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestBuilding_testIsAdmin() : CxxTest::RealTestDescription( Tests_TestBuilding, suiteDescription_TestBuilding, 25, "testIsAdmin" ) {}
 void runTest() { suite_TestBuilding.testIsAdmin(); }
} testDescription_suite_TestBuilding_testIsAdmin;

static class TestDescription_suite_TestBuilding_testSetAdmin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestBuilding_testSetAdmin() : CxxTest::RealTestDescription( Tests_TestBuilding, suiteDescription_TestBuilding, 30, "testSetAdmin" ) {}
 void runTest() { suite_TestBuilding.testSetAdmin(); }
} testDescription_suite_TestBuilding_testSetAdmin;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
