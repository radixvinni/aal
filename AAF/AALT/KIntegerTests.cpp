/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/KInteger.hpp"

using namespace AAL;

TEST(KInteger, DummyTest)
{
        CHECK(KInteger<uint>("ff",Hex)==KInteger<uchar>("ff",Hex));
        CHECK(KInteger<uint>("100",Hex)==KInteger<uchar>("100",Hex));
        CHECK(KInteger<uint>("101",Hex)==KInteger<uchar>("101",Hex));
        CHECK(KInteger<uint>("123456789abcdef",Hex)==KInteger<uchar>("123456789abcdef",Hex));
}

TEST(KInteger, Karatsuban4)
{
        CHECK(KInteger<uchar>("2")*KInteger<uchar>("3")==KInteger<uint>("2")*KInteger<uint>("3"));
        CHECK(KInteger<uint>("14ab20bd",Hex)*KInteger<uint>("2565a8e3",Hex)==KInteger<uchar>("14ab20bd",Hex)*KInteger<uchar>("2565a8e3",Hex));  //KInteger<uint>("304f0e1dccb0f97",Hex));
        CHECK(KInteger<uint>("42e576f7",Hex)*KInteger<uint>("3faf713",Hex)==KInteger<uint>("10a450b6f062555",Hex));
}
TEST(KInteger, Karatsuban8)
{
        //n=8
        CHECK(KInteger<uint>("1b69b4ba630f359",Hex)*KInteger<uint>("891087b8e3b70cb1",Hex)==KInteger<uint>("ead56db9553d9ff00cf6d612df6c89",Hex));
        CHECK(KInteger<uint>("9a368b564c287473",Hex)*KInteger<uint>("17af6629e73b8f",Hex)==KInteger<uchar>("9a368b564c287473",Hex)*KInteger<uchar>("17af6629e73b8f",Hex));//KInteger<uint>("e448f58fa617db9b3eebb5c348d3d",Hex));
        CHECK(KInteger<uint>("9bc1546914997f6c",Hex)*KInteger<uint>("1aea1c83351f07c",Hex)==KInteger<uchar>("9bc1546914997f6c",Hex)*KInteger<uchar>("1aea1c83351f07c",Hex));//KInteger<uint>("106012a2cda002dfd97f789b6faf850",Hex));
        //n=8[2]
        //CHECK(KInteger<uint>("5281877500950955839569596689")*KInteger<uint>("5281877500950955839569596689")==KInteger<uint>("27898229935051914505936841880218711515883674530119762721"));
        //CHECK(KInteger<uint>("22685491133344441733072379273554445380")*KInteger<uint>("113427455645594698656638941255359301768")==KInteger<uint>("2573157539325958476287548782092624036557592877796858164866880819769293431840"));
        CHECK(KInteger<uint>("26eeb7afdcb2453f76638cd5cab2ef20",Hex)*KInteger<uint>("7fae53254eff44fd7b2cf3f031e40f4a",Hex)==KInteger<uint>("136af0062a1690bcc1f25e9123c9dc7798efc14a4425d501c27791cf2c3bff40",Hex));
        //CHECK(KInteger<uint>("26eeb7afdcb2453f76638cd5cab2ef20",Hex)*KInteger<uint>("7fae53254eff44fd7b2cf3f031e40f4a",Hex)==KInteger<uchar>("26eeb7afdcb2453f76638cd5cab2ef20",Hex)*KInteger<uchar>("7fae53254eff44fd7b2cf3f031e40f4a",Hex));
}
TEST(KInteger, Karatsuban16)
{       //n=16

        CHECK(KInteger<uint>("136af0062a1690bcc1f25e9123c9dc7798efc14a4425d501c27791cf2c3bff4",Hex)*KInteger<uint>("47681ea30722e3ed33e55d547bc988b215d30dcaf30753c3df10e363fa27218",Hex)==KInteger<uint>("56a8e561def7a38748adf241d784f3efdea35d7372ae9e5856e8bc1a50f6b6666745c2d6f682ce6b6f3a36af642f88835bbd7e0cdc56bbe2fe066723ca6e0",Hex));
        CHECK(KInteger<uint>("e355552e4be4545221868b0381f92f9235adfa6aae0d1f4895d4d9e327fb2f",Hex)*KInteger<uint>("861069fc744655774d61e8d6e91d8763c8d4df2f50a8e960c18c7f96b7a29e",Hex)==KInteger<uint>("770d3e09bdcf38ef29be00da7366eb1aeca90324e840cb834dd7030dd11cc25786cee68f5391a4702b409e730bfc57796218edb8087efca85f4c9839c502",Hex));
}

TEST(KInteger, Karatsuban32)
{
        //n=32
        CHECK(KInteger<uint>("770d3e09bdcf38ef29be00da7366eb1aeca90324e840cb834dd7030dd11cc25786cee68f5391a4702b409e730bfc57796218edb8087efca85f4c9839c502",Hex)*KInteger<uint>("770d3e09bdcf38ef29be00da7366eb1aeca90324e840cb834dd7030dd11cc25786cee68f5391a4702b409e730bfc57796218edb8087efca85f4c9839c502",Hex)==KInteger<uint>("375d505c6a7ca64965fa5cee6850d682e77ee7ded851f724397c77c3b6bb6c5d15714115edd49f56a4b29d0a098770d7cfa191cee22a0f9f6528e4ee064ca77943596c125d1a98f39fb5e1f22918c4652cc2d568a04ef61b452b049661081899096c6f7732bbd12de580d6a16292c5765fc1858c1fa91c2bb2801404",Hex));
}

TEST(KInteger, Karatsuban64)
{
        //n=32
        CHECK(KInteger<uint>("375d505c6a7ca64965fa5cee6850d682e77ee7ded851f724397c77c3b6bb6c5d15714115edd49f56a4b29d0a098770d7cfa191cee22a0f9f6528e4ee064ca77943596c125d1a98f39fb5e1f22918c4652cc2d568a04ef61b452b049661081899096c6f7732bbd12de580d6a16292c5765fc1858c1fa91c2bb2801404",Hex)*KInteger<uint>("770d3e09bdcf38ef29be00da7366eb1aeca90324e840cb834dd7030dd11cc25786cee68f5391a4702b409e730bfc57796218edb8087efca85f4c9839c502770d3e09bdcf38ef29be00da7366eb1aeca90324e840cb834dd7030dd11cc25786cee68f5391a4702b409e730bfc57796218edb8087efca85f4c9839c502",Hex)==
              KInteger<uint>("19bf3d82befc43c2d6da96a1c75b1550fbf25118305207db28e8c9e3e0c4c9c724be13a38dcd8efaa0e7ece01640021fe09dd5f996899f9a5f42a755fb5145d8bc9664e47a10fd7caafba7f2e1c396a2cb9288c4fed2133e62bb38a9157733b340139b53f79ebad3b15b7c593ff5e227959cb5dd5cac11ffe275ad65e9f1ffe475f09e565b04af7c2e1bd56f963cad52b77362cf9164106981c9f6c320443bd4883bc1686984970acf902d9d43a2f4803a19eedbc308046aee1cbdd880d0d008680834629b224d8408fcfb8c32d85f006bd8a70e779229e5ab13114f0f647ab558c44f98d28f6976efc7421934dd1ac631ca104ac94b3c08",Hex));
}

