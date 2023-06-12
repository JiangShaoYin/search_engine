#include "../../include/Configuration.h"
#include "../../include/CppJieba.h"
#include "../../include/PageLib.h"
#include "../../include/RssHeader.h"
#include "../../include/CnDictProducer.h"
#include "../../include/EngDictProducer.h"

int main()
{
    auto _conf = Configuration::GetInstance("../../conf/myconf.conf");
    auto _sp = SplitToolCppJieba::GetInstance(_conf.get());
    
    CnDictProducer _cndict(_sp.get());
    _cndict.buildDict();
    _cndict.createIndex();
    _cndict.storeDict();

    EngDictProducer _endcit;
    _endcit.buildDict();
    _endcit.createIndex();
    _endcit.storeDict();

    PageLib lib;
    lib.create();
    lib.invertIndex();
    lib.store();
    


    return 0;
}

