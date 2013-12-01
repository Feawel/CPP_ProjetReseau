#include <cxxtest/TestSuite.h>
#include "phases/networkbuilder.h"

class TestNetworkBuilder_Phase1 : public CxxTest::TestSuite
{
public:
    void testAddedComponents(void)
    {

        TS_ASSERT_EQUALS(1 + 1, 2);
    }
    void testAddedAddresses()
    {

    }
};
