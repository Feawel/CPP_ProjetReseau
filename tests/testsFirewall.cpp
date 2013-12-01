
#include "testsFirewall.h"

using namespace std;



bool TestsFirewall::testRules() {
    bool result = false, testPart1 = false, testPart2 = false, testPart3 = false;
    Firewall firewall;
    string rule1 = "Testing Rule 1";
    string rule2 = "Testing Rule 2";

    if(firewall.getRules().empty())
        testPart1 = true;

    firewall.setRules(rule1);

    if(firewall.getRules() == rule1)
        testPart2 = true;

    firewall.setRules(rule2);

    if(firewall.getRules() == rule2)
        testPart3 = true;


    if (testPart1 && testPart2 && testPart3)
        result = true;
    return result;
}


bool TestsFirewall::testAddresses() {
    bool result = false, testPart1 = false, testPart2 = false;
    Firewall firewall;
    Address privateAddress(1,2,3,4,5);
    Address publicAddress(6,7,8,9,0);

    firewall.setAddress(privateAddress);
    firewall.setPublicAddress(publicAddress);

    string privateAddressString = privateAddress.toString();
    string publicAddressString = publicAddress.toString();

    string privateAddressTestString = firewall.getAddress().toString();
    string publicAddressTestString = firewall.getPublicAddress().toString();

    if(privateAddressString == privateAddressTestString)
        testPart1 = true;
    if(publicAddressString == publicAddressTestString)
        testPart2 = true;

    if(testPart1 && testPart2)
        result = true;

    return result;

}
