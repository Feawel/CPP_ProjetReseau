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
#include "/Users/Jonathan/CPP_ProjetReseau/tests/tests_unitaires/TestBuilding.h"

static TestBuilding suite_TestBuilding;

static CxxTest::List Tests_TestBuilding = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_TestBuilding( "TestBuilding.h", 5, "TestBuilding", suite_TestBuilding, Tests_TestBuilding );

static class TestDescription_suite_TestBuilding_testgetFloors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestBuilding_testgetFloors() : CxxTest::RealTestDescription( Tests_TestBuilding, suiteDescription_TestBuilding, 9, "testgetFloors" ) {}
 void runTest() { suite_TestBuilding.testgetFloors(); }
} testDescription_suite_TestBuilding_testgetFloors;

static class TestDescription_suite_TestBuilding_testIsAdmin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestBuilding_testIsAdmin() : CxxTest::RealTestDescription( Tests_TestBuilding, suiteDescription_TestBuilding, 24, "testIsAdmin" ) {}
 void runTest() { suite_TestBuilding.testIsAdmin(); }
} testDescription_suite_TestBuilding_testIsAdmin;

static class TestDescription_suite_TestBuilding_testSetAdmin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_TestBuilding_testSetAdmin() : CxxTest::RealTestDescription( Tests_TestBuilding, suiteDescription_TestBuilding, 29, "testSetAdmin" ) {}
 void runTest() { suite_TestBuilding.testSetAdmin(); }
} testDescription_suite_TestBuilding_testSetAdmin;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
