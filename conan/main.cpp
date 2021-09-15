#include <iostream>
#include "Poco/MD5Engine.h"
#include <boost/regex.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace Poco;

int main() {
    MD5Engine md5 {};
    md5.update("Hello world");
    string md5string = DigestEngine::digestToHex(md5.digest());
    cout << "MD5=" << md5string << "\n";

    return 0;
}
