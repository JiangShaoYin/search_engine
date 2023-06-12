#include "../../include/Configuration.h"
#include <iostream>

using namespace std;

auto _conf = Configuration::GetInstance("../../conf/myconf.conf");

int main()
{
    auto _conf1 = Configuration::GetInstance("");
    cout << _conf1->getConfigMap("data") << endl;
    return 0;
}

