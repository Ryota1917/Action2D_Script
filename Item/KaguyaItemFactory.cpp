#include "KaguyaItemFactory.h"
#include"TestItem.h"
#include"SwordItem.h"
#include"BombItem.h"

KaguyaItemFactory::KaguyaItemFactory()
{
       
}

std::unique_ptr<KaguyaItem> KaguyaItemFactory::Create(int id)
{
    switch (id) {
    case 0:
        return std::unique_ptr<KaguyaItem>(new TestItem());
    case 1:
        return std::unique_ptr<KaguyaItem>(new SwordItem());
    case 2:
        return std::unique_ptr<KaguyaItem>(new BombItem());
    }

    return std::unique_ptr<KaguyaItem>();
}
