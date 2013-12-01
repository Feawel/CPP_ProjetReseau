#include <cxxtest/TestSuite.h>
#include "../../model/location/building.h"
#include "../../model/location/floor.h"


class TestBuilding : public CxxTest::TestSuite
{
public:

    void testGetFloors(void)
    {
        Building buildingTest("Building test");
        std::vector<Floor*> floors = buildingTest.getFloors();

        //Test du cas où floors est vide
        TS_ASSERT_EQUALS(floors.empty() , true);

        Floor* floorTest = new Floor("Floor Test", 0);
        buildingTest.addSpecialSection(floorTest);
        std::vector<Floor*>floors2 = buildingTest.getFloors();

        //Test du cas où floors n'est pas vide
        TS_ASSERT_EQUALS(floors2.empty() , false);
    }
    void testIsAdmin(void)
    {
        Building buildingTestNonAdmin("Building test");
        TS_ASSERT_EQUALS(buildingTestNonAdmin.isAdmin(), false);
    }
    void testSetAdmin(void)
    {
        Building buildingTestAdmin("Building test");
        buildingTestAdmin.setAdmin();
        TS_ASSERT_EQUALS(buildingTestAdmin.isAdmin(), true);
    }

};
