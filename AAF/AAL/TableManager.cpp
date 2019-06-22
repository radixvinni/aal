/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "TableManager.h"
#include <fstream>
#include "Polynom.h"
//#include <direct.h>
namespace AAL
{
//****************************   РљР»Р°СЃСЃ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ С‚Р°Р±Р»РёС†   *******
TableManager::TableManager() {
       std::ifstream in("../Tables/gf2_multiplication_table.dat", std::ios::in | std::ios::binary);
       if(!in.is_open())
                throw new Exception("РќРµ РјРѕР¶РµС‚ Р±С‹С‚СЊ РѕС‚РєСЂС‹С‚ С„Р°Р№Р» СЃ С‚Р°Р±Р»РёС†РµР№ СѓРјРЅРѕР¶РµРЅРёСЏ РґР»СЏ GF(2)");

        for(uchar i = 0; i <= 255; i++)
        {
                for(uchar j = 0; j <= 255; j++)
                {
                        uchar result1 = 0;
                        uchar result2 = 0;
                        in.read(reinterpret_cast<char*>(&result1), 1);
                        in.read(reinterpret_cast<char*>(&result2), 1);
                        _gf2MultiplicationTable[i][j] = (ushort)(((unsigned int) result1) + (((unsigned int)result2) << 8));

                        if(j == 255) break;
                }
                if(i == 255) break;
        }

        in.close();
}

TableManager& TableManager::Instance()
{
        static TableManager tableManager;
        return tableManager;
}
/*
void TableManager::createMultiplicationTableForGF2()
{
        std::ofstream out("Tables/gf2_multiplication_table.dat", std::ios::out | std::ios::binary);
        for(uchar i = 0; i <= 255; i++)
        {
                for(uchar j = 0; j <= 255; j++)
                {
                        ushort result = Polynom::MulElemPolynoms(i, j);
                        out << ((uchar) result);
                        out << ((uchar) (result >> 8));
                        if(j == 255)
                        {
                                break;
                        }

                }
                if(i == 255) break;
        }
        out.close();
}
*/
ushort TableManager::getElementaryPolynomsMultiplication(uchar u, uchar v)
{
        return _gf2MultiplicationTable[u][v];
}

};
