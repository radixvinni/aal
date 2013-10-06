/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "DecompositionManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdexcept>
#include <sys/timeb.h>
#include <string>

namespace AAL
{
  DecompositionManager::DecompositionManager()
  {
    withOneOddTwoDecompositionCompositCount = 127;
    withoutOneOddTwoDecompositionCompositeCount = 97;
    EvenLargeTwoWithOneDecompositionCompositeCount = 178;
    EvenTwoWithOneDecompositionCompositeCount = 53;
    withOneThreeDecompositionCompositCount = 37;
    withoutOneThreeDecompositionCompositeCount = 17;
    withOneFiveDecompositionCompositeCount = 27;
    withoutOneFiveDecompositionCompositeCount = 23;
    withOneSixDecompositionCompositeCount = 25;
    withoutOneSixDecompositionCompositeCount = 11;
    withOneSevenDecompositionCompositeCount = 20;
    withoutOneSevenDecompositionCompositeCount = 10;
    withOneOddTenDecompositionCompositeCount = 56;
    withoutOneOddTenDecompositionCompositCount = 22;
    withOneElevenDecompositionCompositeCount = 13;
    withoutOneElevenDecompositionCompositeCount = 8;
    withOneTwelveDecompositionCompositeCount = 13;
    withoutOneTwelveDecompositionCompositeCount = 11;

   withOneOddTwoDecompositionCompositeDegrees[0] = 653;
   withOneOddTwoDecompositionCompositeDegrees[1] = 659;
   withOneOddTwoDecompositionCompositeDegrees[2] = 661;
   withOneOddTwoDecompositionCompositeDegrees[3] = 667;
   withOneOddTwoDecompositionCompositeDegrees[4] = 671;
   withOneOddTwoDecompositionCompositeDegrees[5] = 689;
   withOneOddTwoDecompositionCompositeDegrees[6] = 697;
   withOneOddTwoDecompositionCompositeDegrees[7] = 709;
   withOneOddTwoDecompositionCompositeDegrees[8] = 719;
   withOneOddTwoDecompositionCompositeDegrees[9] = 721;
   withOneOddTwoDecompositionCompositeDegrees[10] = 733;
   withOneOddTwoDecompositionCompositeDegrees[11] = 737;
   withOneOddTwoDecompositionCompositeDegrees[12] = 749;
   withOneOddTwoDecompositionCompositeDegrees[13] = 751;
   withOneOddTwoDecompositionCompositeDegrees[14] = 761;
   withOneOddTwoDecompositionCompositeDegrees[15] = 775;
   withOneOddTwoDecompositionCompositeDegrees[16] = 779;
   withOneOddTwoDecompositionCompositeDegrees[17] = 787;
   withOneOddTwoDecompositionCompositeDegrees[18] = 791;
   withOneOddTwoDecompositionCompositeDegrees[19] = 797;
   withOneOddTwoDecompositionCompositeDegrees[20] = 799;
   withOneOddTwoDecompositionCompositeDegrees[21] = 805;
   withOneOddTwoDecompositionCompositeDegrees[22] = 811;
   withOneOddTwoDecompositionCompositeDegrees[23] = 823;
   withOneOddTwoDecompositionCompositeDegrees[24] = 827;
   withOneOddTwoDecompositionCompositeDegrees[25] = 833;
   withOneOddTwoDecompositionCompositeDegrees[26] = 845;
   withOneOddTwoDecompositionCompositeDegrees[27] = 847;
   withOneOddTwoDecompositionCompositeDegrees[28] = 851;
   withOneOddTwoDecompositionCompositeDegrees[29] = 853;
   withOneOddTwoDecompositionCompositeDegrees[30] = 857;
   withOneOddTwoDecompositionCompositeDegrees[31] = 859;
   withOneOddTwoDecompositionCompositeDegrees[32] = 863;
   withOneOddTwoDecompositionCompositeDegrees[33] = 865;
   withOneOddTwoDecompositionCompositeDegrees[34] = 869;
   withOneOddTwoDecompositionCompositeDegrees[35] = 871;
   withOneOddTwoDecompositionCompositeDegrees[36] = 875;
   withOneOddTwoDecompositionCompositeDegrees[37] = 877;
   withOneOddTwoDecompositionCompositeDegrees[38] = 881;
   withOneOddTwoDecompositionCompositeDegrees[39] = 887;
   withOneOddTwoDecompositionCompositeDegrees[40] = 889;
   withOneOddTwoDecompositionCompositeDegrees[41] = 893;
   withOneOddTwoDecompositionCompositeDegrees[42] = 905;
   withOneOddTwoDecompositionCompositeDegrees[43] = 913;
   withOneOddTwoDecompositionCompositeDegrees[44] = 921;
   withOneOddTwoDecompositionCompositeDegrees[45] = 923;
   withOneOddTwoDecompositionCompositeDegrees[46] = 925;
   withOneOddTwoDecompositionCompositeDegrees[47] = 931;
   withOneOddTwoDecompositionCompositeDegrees[48] = 933;
   withOneOddTwoDecompositionCompositeDegrees[49] = 943;
   withOneOddTwoDecompositionCompositeDegrees[50] = 947;
   withOneOddTwoDecompositionCompositeDegrees[51] = 949;
   withOneOddTwoDecompositionCompositeDegrees[52] = 951;
   withOneOddTwoDecompositionCompositeDegrees[53] = 953;
   withOneOddTwoDecompositionCompositeDegrees[54] = 955;
   withOneOddTwoDecompositionCompositeDegrees[55] = 961;
   withOneOddTwoDecompositionCompositeDegrees[56] = 967;
   withOneOddTwoDecompositionCompositeDegrees[57] = 969;
   withOneOddTwoDecompositionCompositeDegrees[58] = 979;
   withOneOddTwoDecompositionCompositeDegrees[59] = 981;
   withOneOddTwoDecompositionCompositeDegrees[60] = 983;
   withOneOddTwoDecompositionCompositeDegrees[61] = 989;
   withOneOddTwoDecompositionCompositeDegrees[62] = 991;
   withOneOddTwoDecompositionCompositeDegrees[63] = 993;
   withOneOddTwoDecompositionCompositeDegrees[64] = 997;
   withOneOddTwoDecompositionCompositeDegrees[65] = 1001;
   withOneOddTwoDecompositionCompositeDegrees[66] = 1007;
   withOneOddTwoDecompositionCompositeDegrees[67] = 1009;
   withOneOddTwoDecompositionCompositeDegrees[68] = 1011;
   withOneOddTwoDecompositionCompositeDegrees[69] = 1017;
   withOneOddTwoDecompositionCompositeDegrees[70] = 1019;
   withOneOddTwoDecompositionCompositeDegrees[71] = 1021;
   withOneOddTwoDecompositionCompositeDegrees[72] = 1025;
   withOneOddTwoDecompositionCompositeDegrees[73] = 1027;
   withOneOddTwoDecompositionCompositeDegrees[74] = 1033;
   withOneOddTwoDecompositionCompositeDegrees[75] = 1037;
   withOneOddTwoDecompositionCompositeDegrees[76] = 1041;
   withOneOddTwoDecompositionCompositeDegrees[77] = 1043;
   withOneOddTwoDecompositionCompositeDegrees[78] = 1049;
   withOneOddTwoDecompositionCompositeDegrees[79] = 1051;
   withOneOddTwoDecompositionCompositeDegrees[80] = 1055;
   withOneOddTwoDecompositionCompositeDegrees[81] = 1057;
   withOneOddTwoDecompositionCompositeDegrees[82] = 1063;
   withOneOddTwoDecompositionCompositeDegrees[83] = 1067;
   withOneOddTwoDecompositionCompositeDegrees[84] = 1069;
   withOneOddTwoDecompositionCompositeDegrees[85] = 1075;
   withOneOddTwoDecompositionCompositeDegrees[86] = 1079;
   withOneOddTwoDecompositionCompositeDegrees[87] = 1085;
   withOneOddTwoDecompositionCompositeDegrees[88] = 1087;
   withOneOddTwoDecompositionCompositeDegrees[89] = 1091;
   withOneOddTwoDecompositionCompositeDegrees[90] = 1097;
   withOneOddTwoDecompositionCompositeDegrees[91] = 1099;
   withOneOddTwoDecompositionCompositeDegrees[92] = 1101;
   withOneOddTwoDecompositionCompositeDegrees[93] = 1103;
   withOneOddTwoDecompositionCompositeDegrees[94] = 1105;
   withOneOddTwoDecompositionCompositeDegrees[95] = 1107;
   withOneOddTwoDecompositionCompositeDegrees[96] = 1109;
   withOneOddTwoDecompositionCompositeDegrees[97] = 1113;
   withOneOddTwoDecompositionCompositeDegrees[98] = 1115;
   withOneOddTwoDecompositionCompositeDegrees[99] = 1119;
   withOneOddTwoDecompositionCompositeDegrees[100] = 1123;
   withOneOddTwoDecompositionCompositeDegrees[101] = 1127;
   withOneOddTwoDecompositionCompositeDegrees[102] = 1129;
   withOneOddTwoDecompositionCompositeDegrees[103] = 1131;
   withOneOddTwoDecompositionCompositeDegrees[104] = 1133;
   withOneOddTwoDecompositionCompositeDegrees[105] = 1135;
   withOneOddTwoDecompositionCompositeDegrees[106] = 1137;
   withOneOddTwoDecompositionCompositeDegrees[107] = 1139;
   withOneOddTwoDecompositionCompositeDegrees[108] = 1143;
   withOneOddTwoDecompositionCompositeDegrees[109] = 1147;
   withOneOddTwoDecompositionCompositeDegrees[110] = 1151;
   withOneOddTwoDecompositionCompositeDegrees[111] = 1153;
   withOneOddTwoDecompositionCompositeDegrees[112] = 1157;
   withOneOddTwoDecompositionCompositeDegrees[113] = 1159;
   withOneOddTwoDecompositionCompositeDegrees[114] = 1161;
   withOneOddTwoDecompositionCompositeDegrees[115] = 1163;
   withOneOddTwoDecompositionCompositeDegrees[116] = 1165;
   withOneOddTwoDecompositionCompositeDegrees[117] = 1167;
   withOneOddTwoDecompositionCompositeDegrees[118] = 1169;
   withOneOddTwoDecompositionCompositeDegrees[119] = 1173;
   withOneOddTwoDecompositionCompositeDegrees[120] = 1177;
   withOneOddTwoDecompositionCompositeDegrees[121] = 1179;
   withOneOddTwoDecompositionCompositeDegrees[122] = 1183;
   withOneOddTwoDecompositionCompositeDegrees[123] = 1187;
   withOneOddTwoDecompositionCompositeDegrees[124] = 1191;
   withOneOddTwoDecompositionCompositeDegrees[125] = 1193;
   withOneOddTwoDecompositionCompositeDegrees[126] = 1195;


   withoutOneOddTwoDecompositionCompositeDegrees[0] = 673;
   withoutOneOddTwoDecompositionCompositeDegrees[1] = 683;
   withoutOneOddTwoDecompositionCompositeDegrees[2] = 713;
   withoutOneOddTwoDecompositionCompositeDegrees[3] = 719;
   withoutOneOddTwoDecompositionCompositeDegrees[4] = 731;
   withoutOneOddTwoDecompositionCompositeDegrees[5] = 739;
   withoutOneOddTwoDecompositionCompositeDegrees[6] = 743;
   withoutOneOddTwoDecompositionCompositeDegrees[7] = 751;
   withoutOneOddTwoDecompositionCompositeDegrees[8] = 757;
   withoutOneOddTwoDecompositionCompositeDegrees[9] = 761;
   withoutOneOddTwoDecompositionCompositeDegrees[10] = 763;
   withoutOneOddTwoDecompositionCompositeDegrees[11] = 773;
   withoutOneOddTwoDecompositionCompositeDegrees[12] = 781;
   withoutOneOddTwoDecompositionCompositeDegrees[13] = 787;
   withoutOneOddTwoDecompositionCompositeDegrees[14] = 791;
   withoutOneOddTwoDecompositionCompositeDegrees[15] = 793;
   withoutOneOddTwoDecompositionCompositeDegrees[16] = 797;
   withoutOneOddTwoDecompositionCompositeDegrees[17] = 799;
   withoutOneOddTwoDecompositionCompositeDegrees[18] = 805;
   withoutOneOddTwoDecompositionCompositeDegrees[19] = 809;
   withoutOneOddTwoDecompositionCompositeDegrees[20] = 811;
   withoutOneOddTwoDecompositionCompositeDegrees[21] = 815;
   withoutOneOddTwoDecompositionCompositeDegrees[22] = 817;
   withoutOneOddTwoDecompositionCompositeDegrees[23] = 821;
   withoutOneOddTwoDecompositionCompositeDegrees[24] = 823;
   withoutOneOddTwoDecompositionCompositeDegrees[25] = 827;
   withoutOneOddTwoDecompositionCompositeDegrees[26] = 841;
   withoutOneOddTwoDecompositionCompositeDegrees[27] = 853;
   withoutOneOddTwoDecompositionCompositeDegrees[28] = 857;
   withoutOneOddTwoDecompositionCompositeDegrees[29] = 859;
   withoutOneOddTwoDecompositionCompositeDegrees[30] = 863;
   withoutOneOddTwoDecompositionCompositeDegrees[31] = 877;
   withoutOneOddTwoDecompositionCompositeDegrees[32] = 887;
   withoutOneOddTwoDecompositionCompositeDegrees[33] = 893;
   withoutOneOddTwoDecompositionCompositeDegrees[34] = 899;
   withoutOneOddTwoDecompositionCompositeDegrees[35] = 905;
   withoutOneOddTwoDecompositionCompositeDegrees[36] = 913;
   withoutOneOddTwoDecompositionCompositeDegrees[37] = 919;
   withoutOneOddTwoDecompositionCompositeDegrees[38] = 923;
   withoutOneOddTwoDecompositionCompositeDegrees[39] = 929;
   withoutOneOddTwoDecompositionCompositeDegrees[40] = 933;
   withoutOneOddTwoDecompositionCompositeDegrees[41] = 935;
   withoutOneOddTwoDecompositionCompositeDegrees[42] = 937;
   withoutOneOddTwoDecompositionCompositeDegrees[43] = 939;
   withoutOneOddTwoDecompositionCompositeDegrees[44] = 941;
   withoutOneOddTwoDecompositionCompositeDegrees[45] = 947;
   withoutOneOddTwoDecompositionCompositeDegrees[46] = 949;
   withoutOneOddTwoDecompositionCompositeDegrees[47] = 953;
   withoutOneOddTwoDecompositionCompositeDegrees[48] = 959;
   withoutOneOddTwoDecompositionCompositeDegrees[49] = 961;
   withoutOneOddTwoDecompositionCompositeDegrees[50] = 963;
   withoutOneOddTwoDecompositionCompositeDegrees[51] = 967;
   withoutOneOddTwoDecompositionCompositeDegrees[52] = 971;
   withoutOneOddTwoDecompositionCompositeDegrees[53] = 973;
   withoutOneOddTwoDecompositionCompositeDegrees[54] = 977;
   withoutOneOddTwoDecompositionCompositeDegrees[55] = 985;
   withoutOneOddTwoDecompositionCompositeDegrees[56] = 991;
   withoutOneOddTwoDecompositionCompositeDegrees[57] = 997;
   withoutOneOddTwoDecompositionCompositeDegrees[58] = 1001;
   withoutOneOddTwoDecompositionCompositeDegrees[59] = 1003;
   withoutOneOddTwoDecompositionCompositeDegrees[60] = 1007;
   withoutOneOddTwoDecompositionCompositeDegrees[61] = 1009;
   withoutOneOddTwoDecompositionCompositeDegrees[62] = 1013;
   withoutOneOddTwoDecompositionCompositeDegrees[63] = 1019;
   withoutOneOddTwoDecompositionCompositeDegrees[64] = 1021;
   withoutOneOddTwoDecompositionCompositeDegrees[65] = 1025;
   withoutOneOddTwoDecompositionCompositeDegrees[66] = 1027;
   withoutOneOddTwoDecompositionCompositeDegrees[67] = 1031;
   withoutOneOddTwoDecompositionCompositeDegrees[68] = 1033;
   withoutOneOddTwoDecompositionCompositeDegrees[69] = 1037;
   withoutOneOddTwoDecompositionCompositeDegrees[70] = 1039;
   withoutOneOddTwoDecompositionCompositeDegrees[71] = 1043;
   withoutOneOddTwoDecompositionCompositeDegrees[72] = 1045;
   withoutOneOddTwoDecompositionCompositeDegrees[73] = 1051;
   withoutOneOddTwoDecompositionCompositeDegrees[74] = 1055;
   withoutOneOddTwoDecompositionCompositeDegrees[75] = 1059;
   withoutOneOddTwoDecompositionCompositeDegrees[76] = 1061;
   withoutOneOddTwoDecompositionCompositeDegrees[77] = 1067;
   withoutOneOddTwoDecompositionCompositeDegrees[78] = 1069;
   withoutOneOddTwoDecompositionCompositeDegrees[79] = 1073;
   withoutOneOddTwoDecompositionCompositeDegrees[80] = 1079;
   withoutOneOddTwoDecompositionCompositeDegrees[81] = 1081;
   withoutOneOddTwoDecompositionCompositeDegrees[82] = 1083;
   withoutOneOddTwoDecompositionCompositeDegrees[83] = 1161;
   withoutOneOddTwoDecompositionCompositeDegrees[84] = 1171;
   withoutOneOddTwoDecompositionCompositeDegrees[85] = 1173;
   withoutOneOddTwoDecompositionCompositeDegrees[86] = 1175;
   withoutOneOddTwoDecompositionCompositeDegrees[87] = 1177;
   withoutOneOddTwoDecompositionCompositeDegrees[88] = 1179;
   withoutOneOddTwoDecompositionCompositeDegrees[89] = 1181;
   withoutOneOddTwoDecompositionCompositeDegrees[90] = 1183;
   withoutOneOddTwoDecompositionCompositeDegrees[91] = 1187;
   withoutOneOddTwoDecompositionCompositeDegrees[92] = 1189;
   withoutOneOddTwoDecompositionCompositeDegrees[93] = 1193;
   withoutOneOddTwoDecompositionCompositeDegrees[94] = 1195;
   withoutOneOddTwoDecompositionCompositeDegrees[95] = 1197;
   withoutOneOddTwoDecompositionCompositeDegrees[96] = 1199;

   EvenLargeTwoWithOneDecompositionCompositeDegrees[0] = 1238;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[1] = 1262;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[2] = 1294;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[3] = 1306;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[4] = 1318;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[5] = 1322;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[6] = 1334;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[7] = 1342;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[8] = 1366;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[9] = 1378;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[10] = 1382;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[11] = 1402;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[12] = 1406;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[13] = 1418;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[14] = 1430;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[15] = 1450;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[16] = 1454;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[17] = 1458;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[18] = 1462;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[19] = 1466;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[20] = 1478;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[21] = 1490;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[22] = 1502;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[23] = 1522;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[24] = 1526;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[25] = 1534;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[26] = 1538;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[27] = 1550;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[28] = 1574;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[29] = 1582;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[30] = 1586;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[31] = 1598;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[32] = 1606;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[33] = 1610;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[34] = 1618;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[35] = 1622;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[36] = 1630;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[37] = 1634;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[38] = 1642;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[39] = 1646;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[40] = 1654;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[41] = 1658;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[42] = 1666;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[43] = 1670;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[44] = 1678;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[45] = 1682;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[46] = 1686;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[47] = 1690;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[48] = 1694;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[49] = 1706;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[50] = 1714;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[51] = 1718;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[52] = 1726;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[53] = 1730;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[54] = 1734;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[55] = 1754;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[56] = 1758;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[57] = 1762;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[58] = 1766;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[59] = 1774;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[60] = 1778;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[61] = 1782;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[62] = 1786;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[63] = 1790;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[64] = 1794;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[65] = 1798;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[66] = 1806;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[67] = 1814;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[68] = 1822;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[69] = 1826;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[70] = 1834;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[71] = 1838;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[72] = 1846;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[73] = 1862;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[74] = 1870;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[75] = 1874;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[76] = 1882;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[77] = 1886;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[78] = 1894;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[79] = 1898;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[80] = 1906;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[81] = 1910;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[82] = 1914;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[83] = 1918;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[84] = 1922;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[85] = 1926;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[86] = 1930;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[87] = 1934;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[88] = 1942;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[89] = 1946;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[89] = 1954;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[90] = 1962;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[91] = 1970;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[92] = 1978;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[93] = 1982;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[94] = 1990;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[95] = 2002;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[96] = 2006;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[97] = 2018;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[98] = 2026;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[99] = 2030;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[100] = 2034;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[101] = 2038;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[102] = 2042;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[103] = 2046;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[104] = 2050;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[105] = 2062;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[106] = 2066;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[107] = 2070;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[108] = 2074;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[109] = 2078;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[110] = 2086;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[111] = 2090;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[112] = 2094;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[113] = 2098;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[114] = 2102;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[115] = 2106;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[116] = 2110;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[117] = 2114;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[118] = 2118;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[119] = 2126;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[120] = 2142;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[121] = 2146;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[122] = 2150;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[123] = 2154;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[124] = 2158;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[125] = 2162;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[126] = 2166;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[127] = 2170;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[128] = 2174;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[129] = 2187;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[130] = 2186;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[131] = 2190;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[132] = 2194;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[133] = 2198;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[134] = 2202;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[135] = 2206;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[136] = 2210;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[137] = 2214;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[138] = 2218;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[139] = 2222;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[140] = 2226;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[141] = 2230;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[142] = 2238;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[143] = 2242;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[144] = 2246;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[145] = 2250;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[146] = 2262;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[147] = 2266;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[148] = 2270;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[149] = 2278;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[150] = 2282;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[151] = 2286;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[152] = 2290;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[153] = 2294;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[154] = 2298;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[155] = 2302;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[156] = 2306;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[157] = 2310;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[158] = 2318;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[160] = 2326;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[161] = 2330;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[162] = 2334;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[163] = 2338;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[164] = 2342;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[165] = 2346;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[166] = 2350;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[167] = 2354;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[168] = 2358;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[169] = 2362;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[170] = 2370;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[171] = 2374;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[172] = 2378;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[173] = 2380;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[174] = 2386;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[175] = 2390;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[176] = 2394;
   EvenLargeTwoWithOneDecompositionCompositeDegrees[177] = 2398;

   EvenTwoWithOneDecompositionCompositeDegrees[0] = 716;
   EvenTwoWithOneDecompositionCompositeDegrees[1] = 736;
   EvenTwoWithOneDecompositionCompositeDegrees[2] = 760;
   EvenTwoWithOneDecompositionCompositeDegrees[3] = 764;
   EvenTwoWithOneDecompositionCompositeDegrees[4] = 772;
   EvenTwoWithOneDecompositionCompositeDegrees[5] = 776;
   EvenTwoWithOneDecompositionCompositeDegrees[6] = 788;
   EvenTwoWithOneDecompositionCompositeDegrees[7] = 820;
   EvenTwoWithOneDecompositionCompositeDegrees[8] = 824;
   EvenTwoWithOneDecompositionCompositeDegrees[9] = 832;
   EvenTwoWithOneDecompositionCompositeDegrees[10] = 836;
   EvenTwoWithOneDecompositionCompositeDegrees[11] = 856;
   EvenTwoWithOneDecompositionCompositeDegrees[12] = 860;
   EvenTwoWithOneDecompositionCompositeDegrees[13] = 904;
   EvenTwoWithOneDecompositionCompositeDegrees[14] = 908;
   EvenTwoWithOneDecompositionCompositeDegrees[15] = 916;
   EvenTwoWithOneDecompositionCompositeDegrees[16] = 928;
   EvenTwoWithOneDecompositionCompositeDegrees[17] = 932;
   EvenTwoWithOneDecompositionCompositeDegrees[18] = 956;
   EvenTwoWithOneDecompositionCompositeDegrees[19] = 964;
   EvenTwoWithOneDecompositionCompositeDegrees[20] = 972;
   EvenTwoWithOneDecompositionCompositeDegrees[21] = 980;
   EvenTwoWithOneDecompositionCompositeDegrees[22] = 984;
   EvenTwoWithOneDecompositionCompositeDegrees[23] = 988;
   EvenTwoWithOneDecompositionCompositeDegrees[24] = 1000;
   EvenTwoWithOneDecompositionCompositeDegrees[25] = 1012;
   EvenTwoWithOneDecompositionCompositeDegrees[26] = 1028;
   EvenTwoWithOneDecompositionCompositeDegrees[27] = 1036;
   EvenTwoWithOneDecompositionCompositeDegrees[28] = 1040;
   EvenTwoWithOneDecompositionCompositeDegrees[29] = 1044;
   EvenTwoWithOneDecompositionCompositeDegrees[30] = 1052;
   EvenTwoWithOneDecompositionCompositeDegrees[31] = 1064;
   EvenTwoWithOneDecompositionCompositeDegrees[32] = 1068;
   EvenTwoWithOneDecompositionCompositeDegrees[33] = 1072;
   EvenTwoWithOneDecompositionCompositeDegrees[34] = 1076;
   EvenTwoWithOneDecompositionCompositeDegrees[35] = 1084;
   EvenTwoWithOneDecompositionCompositeDegrees[36] = 1088;
   EvenTwoWithOneDecompositionCompositeDegrees[37] = 1100;
   EvenTwoWithOneDecompositionCompositeDegrees[38] = 1104;
   EvenTwoWithOneDecompositionCompositeDegrees[39] = 1108;
   EvenTwoWithOneDecompositionCompositeDegrees[40] = 1120;
   EvenTwoWithOneDecompositionCompositeDegrees[41] = 1124;
   EvenTwoWithOneDecompositionCompositeDegrees[42] = 1128;
   EvenTwoWithOneDecompositionCompositeDegrees[43] = 1136;
   EvenTwoWithOneDecompositionCompositeDegrees[44] = 1144;
   EvenTwoWithOneDecompositionCompositeDegrees[45] = 1152;
   EvenTwoWithOneDecompositionCompositeDegrees[46] = 1164;
   EvenTwoWithOneDecompositionCompositeDegrees[47] = 1168;
   EvenTwoWithOneDecompositionCompositeDegrees[48] = 1172;
   EvenTwoWithOneDecompositionCompositeDegrees[49] = 1176;
   EvenTwoWithOneDecompositionCompositeDegrees[50] = 1180;
   EvenTwoWithOneDecompositionCompositeDegrees[51] = 1188;
   EvenTwoWithOneDecompositionCompositeDegrees[52] = 1196;

   withOneThreeDecompositionCompositeDegrees[0] = 397;
   withOneThreeDecompositionCompositeDegrees[1] = 404;
   withOneThreeDecompositionCompositeDegrees[2] = 409;
   withOneThreeDecompositionCompositeDegrees[3] = 412;
   withOneThreeDecompositionCompositeDegrees[4] = 419;
   withOneThreeDecompositionCompositeDegrees[5] = 422;
   withOneThreeDecompositionCompositeDegrees[6] = 424;
   withOneThreeDecompositionCompositeDegrees[7] = 436;
   withOneThreeDecompositionCompositeDegrees[8] = 437;
   withOneThreeDecompositionCompositeDegrees[9] = 442;
   withOneThreeDecompositionCompositeDegrees[10] = 452;
   withOneThreeDecompositionCompositeDegrees[11] = 463;
   withOneThreeDecompositionCompositeDegrees[12] = 466;
   withOneThreeDecompositionCompositeDegrees[13] = 473;
   withOneThreeDecompositionCompositeDegrees[14] = 476;
   withOneThreeDecompositionCompositeDegrees[15] = 478;
   withOneThreeDecompositionCompositeDegrees[16] = 479;
   withOneThreeDecompositionCompositeDegrees[17] = 485;
   withOneThreeDecompositionCompositeDegrees[18] = 491;
   withOneThreeDecompositionCompositeDegrees[19] = 493;
   withOneThreeDecompositionCompositeDegrees[20] = 496;
   withOneThreeDecompositionCompositeDegrees[21] = 497;
   withOneThreeDecompositionCompositeDegrees[22] = 499;
   withOneThreeDecompositionCompositeDegrees[23] = 505;
   withOneThreeDecompositionCompositeDegrees[24] = 506;
   withOneThreeDecompositionCompositeDegrees[25] = 508;
   withOneThreeDecompositionCompositeDegrees[26] = 509;
   withOneThreeDecompositionCompositeDegrees[27] = 512;
   withOneThreeDecompositionCompositeDegrees[28] = 514;
   withOneThreeDecompositionCompositeDegrees[29] = 515;
   withOneThreeDecompositionCompositeDegrees[30] = 517;
   withOneThreeDecompositionCompositeDegrees[31] = 518;
   withOneThreeDecompositionCompositeDegrees[32] = 521;
   withOneThreeDecompositionCompositeDegrees[33] = 524;
   withOneThreeDecompositionCompositeDegrees[34] = 533;
   withOneThreeDecompositionCompositeDegrees[35] = 536;
   withOneThreeDecompositionCompositeDegrees[36] = 538;

   withoutOneThreeDecompositionCompositeDegrees[0] = 397;
   withoutOneThreeDecompositionCompositeDegrees[2] = 431;
   withoutOneThreeDecompositionCompositeDegrees[3] = 437;
   withoutOneThreeDecompositionCompositeDegrees[4] = 443;
   withoutOneThreeDecompositionCompositeDegrees[5] = 449;
   withoutOneThreeDecompositionCompositeDegrees[6] = 451;
   withoutOneThreeDecompositionCompositeDegrees[7] = 461;
   withoutOneThreeDecompositionCompositeDegrees[8] = 481;
   withoutOneThreeDecompositionCompositeDegrees[9] = 487;
   withoutOneThreeDecompositionCompositeDegrees[10] = 493;
   withoutOneThreeDecompositionCompositeDegrees[11] = 515;
   withoutOneThreeDecompositionCompositeDegrees[12] = 523;
   withoutOneThreeDecompositionCompositeDegrees[13] = 527;
   withoutOneThreeDecompositionCompositeDegrees[14] = 529;
   withoutOneThreeDecompositionCompositeDegrees[15] = 533;
   withoutOneThreeDecompositionCompositeDegrees[16] = 539;

   withOneFiveDecompositionCompositeDegrees[0] = 289;
   withOneFiveDecompositionCompositeDegrees[1] = 298;
   withOneFiveDecompositionCompositeDegrees[2] = 302;
   withOneFiveDecompositionCompositeDegrees[3] = 304;
   withOneFiveDecompositionCompositeDegrees[4] = 307;
   withOneFiveDecompositionCompositeDegrees[5] = 311;
   withOneFiveDecompositionCompositeDegrees[6] = 313;
   withOneFiveDecompositionCompositeDegrees[7] = 314;
   withOneFiveDecompositionCompositeDegrees[8] = 317;
   withOneFiveDecompositionCompositeDegrees[9] = 320;
   withOneFiveDecompositionCompositeDegrees[10] = 323;
   withOneFiveDecompositionCompositeDegrees[11] = 328;
   withOneFiveDecompositionCompositeDegrees[12] = 331;
   withOneFiveDecompositionCompositeDegrees[13] = 334;
   withOneFiveDecompositionCompositeDegrees[14] = 344;
   withOneFiveDecompositionCompositeDegrees[15] = 346;
   withOneFiveDecompositionCompositeDegrees[16] = 349;
   withOneFiveDecompositionCompositeDegrees[17] = 353;
   withOneFiveDecompositionCompositeDegrees[18] = 355;
   withOneFiveDecompositionCompositeDegrees[19] = 358;
   withOneFiveDecompositionCompositeDegrees[20] = 361;
   withOneFiveDecompositionCompositeDegrees[21] = 362;
   withOneFiveDecompositionCompositeDegrees[22] = 367;
   withOneFiveDecompositionCompositeDegrees[23] = 368;
   withOneFiveDecompositionCompositeDegrees[24] = 370;
   withOneFiveDecompositionCompositeDegrees[25] = 373;
   withOneFiveDecompositionCompositeDegrees[26] = 374;

   withoutOneFiveDecompositionCompositeDegrees[0] = 307;
   withoutOneFiveDecompositionCompositeDegrees[1] = 311;
   withoutOneFiveDecompositionCompositeDegrees[2] = 313;
   withoutOneFiveDecompositionCompositeDegrees[3] = 319;
   withoutOneFiveDecompositionCompositeDegrees[4] = 323;
   withoutOneFiveDecompositionCompositeDegrees[5] = 329;
   withoutOneFiveDecompositionCompositeDegrees[6] = 331;
   withoutOneFiveDecompositionCompositeDegrees[7] = 341;
   withoutOneFiveDecompositionCompositeDegrees[8] = 343;
   withoutOneFiveDecompositionCompositeDegrees[9] = 347;
   withoutOneFiveDecompositionCompositeDegrees[10] = 349;
   withoutOneFiveDecompositionCompositeDegrees[11] = 353;
   withoutOneFiveDecompositionCompositeDegrees[12] = 361;
   withoutOneFiveDecompositionCompositeDegrees[13] = 371;
   withoutOneFiveDecompositionCompositeDegrees[14] = 373;
   withoutOneFiveDecompositionCompositeDegrees[15] = 635;
   withoutOneFiveDecompositionCompositeDegrees[16] = 655;
   withoutOneFiveDecompositionCompositeDegrees[17] = 665;
   withoutOneFiveDecompositionCompositeDegrees[18] = 685;
   withoutOneFiveDecompositionCompositeDegrees[19] = 695;
   withoutOneFiveDecompositionCompositeDegrees[20] = 715;
   withoutOneFiveDecompositionCompositeDegrees[21] = 725;
   withoutOneFiveDecompositionCompositeDegrees[22] = 745;

   withOneSixDecompositionCompositeDegrees[0] = 244;
   withOneSixDecompositionCompositeDegrees[1] = 251;
   withOneSixDecompositionCompositeDegrees[2] = 257;
   withOneSixDecompositionCompositeDegrees[3] = 263;
   withOneSixDecompositionCompositeDegrees[4] = 268;
   withOneSixDecompositionCompositeDegrees[5] = 269;
   withOneSixDecompositionCompositeDegrees[6] = 271;
   withOneSixDecompositionCompositeDegrees[7] = 274;
   withOneSixDecompositionCompositeDegrees[8] = 283;
   withOneSixDecompositionCompositeDegrees[9] = 284;
   withOneSixDecompositionCompositeDegrees[10] = 286;
   withOneSixDecompositionCompositeDegrees[11] = 287;
   withOneSixDecompositionCompositeDegrees[12] = 289;
   withOneSixDecompositionCompositeDegrees[13] = 292;
   withOneSixDecompositionCompositeDegrees[14] = 298;
   withOneSixDecompositionCompositeDegrees[15] = 301;
   withOneSixDecompositionCompositeDegrees[16] = 302;
   withOneSixDecompositionCompositeDegrees[17] = 303;
   withOneSixDecompositionCompositeDegrees[18] = 304;
   withOneSixDecompositionCompositeDegrees[19] = 314;
   withOneSixDecompositionCompositeDegrees[20] = 316;
   withOneSixDecompositionCompositeDegrees[21] = 317;
   withOneSixDecompositionCompositeDegrees[22] = 323;
   withOneSixDecompositionCompositeDegrees[23] = 326;
   withOneSixDecompositionCompositeDegrees[24] = 654;

   withoutOneSixDecompositionCompositeDegrees[0] = 257;
   withoutOneSixDecompositionCompositeDegrees[1] = 263;
   withoutOneSixDecompositionCompositeDegrees[2] = 277;
   withoutOneSixDecompositionCompositeDegrees[3] = 281;
   withoutOneSixDecompositionCompositeDegrees[4] = 283;
   withoutOneSixDecompositionCompositeDegrees[5] = 293;
   withoutOneSixDecompositionCompositeDegrees[6] = 299;
   withoutOneSixDecompositionCompositeDegrees[7] = 305;
   withoutOneSixDecompositionCompositeDegrees[8] = 311;
   withoutOneSixDecompositionCompositeDegrees[9] = 313;
   withoutOneSixDecompositionCompositeDegrees[10] = 329;

   withOneSevenDecompositionCompositeDegrees[0] = 232;
   withOneSevenDecompositionCompositeDegrees[2] = 233;
   withOneSevenDecompositionCompositeDegrees[3] = 239;
   withOneSevenDecompositionCompositeDegrees[4] = 253;
   withOneSevenDecompositionCompositeDegrees[5] = 254;
   withOneSevenDecompositionCompositeDegrees[6] = 257;
   withOneSevenDecompositionCompositeDegrees[7] = 268;
   withOneSevenDecompositionCompositeDegrees[8] = 272;
   withOneSevenDecompositionCompositeDegrees[9] = 274;
   withOneSevenDecompositionCompositeDegrees[10] = 277;
   withOneSevenDecompositionCompositeDegrees[11] = 281;
   withOneSevenDecompositionCompositeDegrees[12] = 284;
   withOneSevenDecompositionCompositeDegrees[13] = 286;
   withOneSevenDecompositionCompositeDegrees[14] = 289;
   withOneSevenDecompositionCompositeDegrees[15] = 293;
   withOneSevenDecompositionCompositeDegrees[16] = 296;
   withOneSevenDecompositionCompositeDegrees[17] = 511;
   withOneSevenDecompositionCompositeDegrees[18] = 539;
   withOneSevenDecompositionCompositeDegrees[19] = 553;

   withoutOneSevenDecompositionCompositeDegrees[0] = 233;
   withoutOneSevenDecompositionCompositeDegrees[1] = 253;
   withoutOneSevenDecompositionCompositeDegrees[2] = 257;
   withoutOneSevenDecompositionCompositeDegrees[3] = 259;
   withoutOneSevenDecompositionCompositeDegrees[4] = 263;
   withoutOneSevenDecompositionCompositeDegrees[5] = 269;
   withoutOneSevenDecompositionCompositeDegrees[6] = 271;
   withoutOneSevenDecompositionCompositeDegrees[7] = 277;
   withoutOneSevenDecompositionCompositeDegrees[8] = 281;
   withoutOneSevenDecompositionCompositeDegrees[9] = 295;

   withOneOddTenDecompositionCompositeDegrees[0] = 223;
   withOneOddTenDecompositionCompositeDegrees[1] = 226;
   withOneOddTenDecompositionCompositeDegrees[2] = 229;
   withOneOddTenDecompositionCompositeDegrees[3] = 232;
   withOneOddTenDecompositionCompositeDegrees[4] = 233;
   withOneOddTenDecompositionCompositeDegrees[5] = 236;
   withOneOddTenDecompositionCompositeDegrees[6] = 238;
   withOneOddTenDecompositionCompositeDegrees[7] = 239;
   withOneOddTenDecompositionCompositeDegrees[8] = 241;
   withOneOddTenDecompositionCompositeDegrees[9] = 242;
   withOneOddTenDecompositionCompositeDegrees[10] = 244;
   withOneOddTenDecompositionCompositeDegrees[11] = 247;
   withOneOddTenDecompositionCompositeDegrees[12] = 248;
   withOneOddTenDecompositionCompositeDegrees[13] = 257;
   withOneOddTenDecompositionCompositeDegrees[14] = 259;
   withOneOddTenDecompositionCompositeDegrees[15] = 260;
   withOneOddTenDecompositionCompositeDegrees[16] = 266;
   withOneOddTenDecompositionCompositeDegrees[17] = 268;
   withOneOddTenDecompositionCompositeDegrees[18] = 271;
   withOneOddTenDecompositionCompositeDegrees[19] = 272;
   withOneOddTenDecompositionCompositeDegrees[20] = 274;
   withOneOddTenDecompositionCompositeDegrees[21] = 275;
   withOneOddTenDecompositionCompositeDegrees[22] = 277;
   withOneOddTenDecompositionCompositeDegrees[23] = 278;
   withOneOddTenDecompositionCompositeDegrees[24] = 281;
   withOneOddTenDecompositionCompositeDegrees[25] = 283;
   withOneOddTenDecompositionCompositeDegrees[26] = 284;
   withOneOddTenDecompositionCompositeDegrees[27] = 286;
   withOneOddTenDecompositionCompositeDegrees[28] = 289;
   withOneOddTenDecompositionCompositeDegrees[29] = 292;
   withOneOddTenDecompositionCompositeDegrees[30] = 298;
   withOneOddTenDecompositionCompositeDegrees[31] = 299;
   withOneOddTenDecompositionCompositeDegrees[32] = 301;
   withOneOddTenDecompositionCompositeDegrees[33] = 302;
   withOneOddTenDecompositionCompositeDegrees[34] = 303;
   withOneOddTenDecompositionCompositeDegrees[35] = 304;
   withOneOddTenDecompositionCompositeDegrees[36] = 305;
   withOneOddTenDecompositionCompositeDegrees[37] = 307;
   withOneOddTenDecompositionCompositeDegrees[38] = 308;
   withOneOddTenDecompositionCompositeDegrees[39] = 311;
   withOneOddTenDecompositionCompositeDegrees[40] = 312;
   withOneOddTenDecompositionCompositeDegrees[41] = 313;
   withOneOddTenDecompositionCompositeDegrees[42] = 314;
   withOneOddTenDecompositionCompositeDegrees[43] = 317;
   withOneOddTenDecompositionCompositeDegrees[44] = 319;
   withOneOddTenDecompositionCompositeDegrees[45] = 320;
   withOneOddTenDecompositionCompositeDegrees[46] = 322,
   withOneOddTenDecompositionCompositeDegrees[47] = 323;
   withOneOddTenDecompositionCompositeDegrees[48] = 324;
   withOneOddTenDecompositionCompositeDegrees[49] = 325;
   withOneOddTenDecompositionCompositeDegrees[50] = 328;
   withOneOddTenDecompositionCompositeDegrees[51] = 470;
   withOneOddTenDecompositionCompositeDegrees[52] = 530;
   withOneOddTenDecompositionCompositeDegrees[53] = 550;
   withOneOddTenDecompositionCompositeDegrees[54] = 590;
   withOneOddTenDecompositionCompositeDegrees[55] = 610;

   withoutOneOddTenDecompositionCompositeDegrees[0] = 223;
   withoutOneOddTenDecompositionCompositeDegrees[1] = 227;
   withoutOneOddTenDecompositionCompositeDegrees[2] = 233;
   withoutOneOddTenDecompositionCompositeDegrees[3] = 239;
   withoutOneOddTenDecompositionCompositeDegrees[4] = 241;
   withoutOneOddTenDecompositionCompositeDegrees[5] = 247;
   withoutOneOddTenDecompositionCompositeDegrees[6] = 257;
   withoutOneOddTenDecompositionCompositeDegrees[7] = 263;
   withoutOneOddTenDecompositionCompositeDegrees[8] = 269;
   withoutOneOddTenDecompositionCompositeDegrees[9] = 271;
   withoutOneOddTenDecompositionCompositeDegrees[10] = 277;
   withoutOneOddTenDecompositionCompositeDegrees[11] = 281;
   withoutOneOddTenDecompositionCompositeDegrees[12] = 283;
   withoutOneOddTenDecompositionCompositeDegrees[13] = 287;
   withoutOneOddTenDecompositionCompositeDegrees[14] = 293;
   withoutOneOddTenDecompositionCompositeDegrees[15] = 301;
   withoutOneOddTenDecompositionCompositeDegrees[16] = 305;
   withoutOneOddTenDecompositionCompositeDegrees[17] = 309;
   withoutOneOddTenDecompositionCompositeDegrees[18] = 311;
   withoutOneOddTenDecompositionCompositeDegrees[19] = 323;
   withoutOneOddTenDecompositionCompositeDegrees[20] = 325;
   withoutOneOddTenDecompositionCompositeDegrees[21] = 329;

   withOneElevenDecompositionCompositeDegrees[0] = 197;
   withOneElevenDecompositionCompositeDegrees[1] = 206;
   withOneElevenDecompositionCompositeDegrees[2] = 208;
   withOneElevenDecompositionCompositeDegrees[3] = 212;
   withOneElevenDecompositionCompositeDegrees[4] = 218;
   withOneElevenDecompositionCompositeDegrees[5] = 220;
   withOneElevenDecompositionCompositeDegrees[6] = 224;
   withOneElevenDecompositionCompositeDegrees[7] = 226;
   withOneElevenDecompositionCompositeDegrees[8] = 230;
   withOneElevenDecompositionCompositeDegrees[9] = 233;
   withOneElevenDecompositionCompositeDegrees[10] = 235;
   withOneElevenDecompositionCompositeDegrees[11] = 236;
   withOneElevenDecompositionCompositeDegrees[12] = 473;

   withoutOneElevenDecompositionCompositeDegrees[0] = 199;
   withoutOneElevenDecompositionCompositeDegrees[1] = 217;
   withoutOneElevenDecompositionCompositeDegrees[2] = 221;
   withoutOneElevenDecompositionCompositeDegrees[3] = 227;
   withoutOneElevenDecompositionCompositeDegrees[4] = 229;
   withoutOneElevenDecompositionCompositeDegrees[5] = 233;
   withoutOneElevenDecompositionCompositeDegrees[5] = 235;
   withoutOneElevenDecompositionCompositeDegrees[7] = 239;

   withOneTwelveDecompositionCompositeDegrees[0] = 178;
   withOneTwelveDecompositionCompositeDegrees[1] = 202;
   withOneTwelveDecompositionCompositeDegrees[1] = 206;
   withOneTwelveDecompositionCompositeDegrees[3] = 208;
   withOneTwelveDecompositionCompositeDegrees[4] = 209;
   withOneTwelveDecompositionCompositeDegrees[5] = 214;
   withOneTwelveDecompositionCompositeDegrees[6] = 217;
   withOneTwelveDecompositionCompositeDegrees[7] = 218;
   withOneTwelveDecompositionCompositeDegrees[8] = 227;
   withOneTwelveDecompositionCompositeDegrees[9] = 229;
   withOneTwelveDecompositionCompositeDegrees[10] = 232;
   withOneTwelveDecompositionCompositeDegrees[11] = 236;
   withOneTwelveDecompositionCompositeDegrees[12] = 238;

   withoutOneTwelveDecompositionCompositeDegrees[0] = 179;
   withoutOneTwelveDecompositionCompositeDegrees[1] = 193;
   withoutOneTwelveDecompositionCompositeDegrees[2] = 197;
   withoutOneTwelveDecompositionCompositeDegrees[3] = 199;
   withoutOneTwelveDecompositionCompositeDegrees[4] = 211;
   withoutOneTwelveDecompositionCompositeDegrees[5] = 215;
   withoutOneTwelveDecompositionCompositeDegrees[6] = 227;
   withoutOneTwelveDecompositionCompositeDegrees[7] = 229;
   withoutOneTwelveDecompositionCompositeDegrees[8] = 233;
   withoutOneTwelveDecompositionCompositeDegrees[9] = 235;
   withoutOneTwelveDecompositionCompositeDegrees[10] = 239;
  }
  DecompositionManager& DecompositionManager::Instance()
  {
    static DecompositionManager decompositionManager;
    return decompositionManager;
  }
//------------------------------------------------------------------------------
bool DecompositionManager::hevComposit(unsigned int CompositeDegrees[], uint n, uint degree)
{
  for(unsigned int i = 0; i <= n; i++)
   {
    if(degree == CompositeDegrees[i])
      return true;
   }
return false;
}
//------------------------------------------------------------------------------
bool DecompositionManager::TestComposit(std::string addres, uint degree) {


    if( strcmp(addres.c_str(),"table_5.txt") == 0) {
      return  hevComposit(&withOneOddTwoDecompositionCompositeDegrees[0], withOneOddTwoDecompositionCompositCount,degree);
    } else if( strcmp(addres.c_str(),"table_6.txt" ) == 0) {
       return  hevComposit(&withoutOneOddTwoDecompositionCompositeDegrees[0], withoutOneOddTwoDecompositionCompositeCount,degree);

    } else if(strcmp(addres.c_str(),"table_7.txt") == 0) {
         return  hevComposit(&EvenLargeTwoWithOneDecompositionCompositeDegrees[0], EvenLargeTwoWithOneDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_8.txt") == 0) {
         return  hevComposit(&EvenTwoWithOneDecompositionCompositeDegrees[0], EvenTwoWithOneDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_9.txt") == 0) {
         return  hevComposit(&withOneThreeDecompositionCompositeDegrees[0], withOneThreeDecompositionCompositCount,degree);
    } else if(strcmp(addres.c_str(),"table_10.txt") == 0) {
        return  hevComposit(&withoutOneThreeDecompositionCompositeDegrees[0], withoutOneThreeDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_11.txt") == 0) {
        return  hevComposit(&withOneFiveDecompositionCompositeDegrees[0], withOneFiveDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_12.txt") == 0) {
        return  hevComposit(&withoutOneFiveDecompositionCompositeDegrees[0], withoutOneFiveDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_13.txt") == 0) {
        return  hevComposit(&withOneSixDecompositionCompositeDegrees[0], withOneSixDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_14.txt") == 0) {
        return  hevComposit(&withoutOneSixDecompositionCompositeDegrees[0], withoutOneSixDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_15.txt") == 0) {
        return  hevComposit(&withOneSevenDecompositionCompositeDegrees[0], withOneSevenDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_16.txt") == 0) {
        return  hevComposit(&withoutOneSevenDecompositionCompositeDegrees[0], withoutOneSevenDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_17.txt") == 0) {
        return  hevComposit(&withOneOddTenDecompositionCompositeDegrees[0], withOneOddTenDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_18.txt") == 0) {
        return  hevComposit(&withoutOneOddTenDecompositionCompositeDegrees[0], withoutOneOddTenDecompositionCompositCount,degree);
    } else if(strcmp(addres.c_str(),"table_19.txt") == 0) {
        return  hevComposit(&withOneElevenDecompositionCompositeDegrees[0], withOneElevenDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_20.txt") == 0) {
        return  hevComposit(&withoutOneElevenDecompositionCompositeDegrees[0], withoutOneElevenDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_21.txt") == 0) {
        return  hevComposit(&withOneTwelveDecompositionCompositeDegrees[0], withOneTwelveDecompositionCompositeCount,degree);
    } else if(strcmp(addres.c_str(),"table_22.txt") == 0) {
        return  hevComposit(&withoutOneTwelveDecompositionCompositeDegrees[0], withoutOneTwelveDecompositionCompositeCount,degree);
    }

  return false;


}
//------------------------------------------------------------------------------
void DecompositionManager::NumberGenerator(std::string addres,std::string str_addres)
{
  FILE *fin,*fout;
  uint n_str;
        char str[1600];
        Integer mul("1");
        Integer pow;

    fin = fopen(("../Decompositions/"+addres).c_str(),"rt");
    fout = fopen(("../Decompositions/"+str_addres).c_str(),"wt");
    if(!fin)
    {
      throw new Exception("Файл с факторизациями не может быть открыт");
    }
    n_str = 0;
    while(!feof(fin))
    {
      fgets(str, 1600, fin);
      n_str = atoi(str);
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getEvenLargeTwoDegreeWithOneDecomposition(n_str));
      std::vector<DecompositionMember>::iterator it;
      for (it = vector.begin(); it != vector.end(); it++)
      {
          Integer number(it->getNumber());
          Integer degree(it->getDegree());
          pow.Pow(number,degree);
          mul =  mul*pow;
      }
     fprintf(fout,"{%i,%s} %s \n", n_str , ("../Decompositions/"+addres).c_str(), mul.ToString().c_str());
     mul.setOne(false);
    }
  fclose(fin);
  fclose(fout);
}
//------------------------------------------------------------------------------
void DecompositionManager::logTime(FILE* f, int checkpoint) {
  timeb buf;
  ftime(&buf);
  float t = (float)buf.time+(float)buf.millitm/1000.0;
  fprintf(f, "checkpoint # %d: %f\n", checkpoint, t);

}
//------------------------------------------------------------------------------
std::string DecompositionManager::FindEqualNumberInTheDecompositionsDB(const Integer &nmbr)
{
FILE *fin;
char *str_fact,*St,*fact;
char *str = new char[300];
char *buf = new char[900];
memset(str,'\0',300);
memset(buf,'\0',900);
Integer n("22");
//FILE* fout = fopen("log.txt", "a");
  for(Integer i(1);i <= n; i++)
   {
      std::string openFile = (std::string("../Decompositions/table_")+i.ToString()+std::string("_")+i.ToString()+std::string(".txt"));
      fin = fopen(openFile.c_str() ,"rt");
      std::vector<Integer> Multipliers;
      std::vector<std::string> Degrees;

      while(!feof(fin))
      {
        fgets(buf,900,fin);
//        DecompositionManager::Instance().logTime(fout,1);
        str_fact = strchr(buf, ' ') + 1;
//        DecompositionManager::Instance().logTime(fout,2);
        char *num = new char[strlen(str_fact)];
//        DecompositionManager::Instance().logTime(fout,3);
        fact = strstr(str_fact, " ");
//        DecompositionManager::Instance().logTime(fout,5);
        *fact = 0;
//        DecompositionManager::Instance().logTime(fout,6);
        strcpy(num, str_fact);
//        DecompositionManager::Instance().logTime(fout,7);
        std::string e = "";
//        DecompositionManager::Instance().logTime(fout,8);
        e = std::string(num);
//        DecompositionManager::Instance().logTime(fout,9);
        Integer r(e);
//        DecompositionManager::Instance().logTime(fout,10);
        Multipliers.push_back(r);
//        DecompositionManager::Instance().logTime(fout,11);
        St = strstr(buf,str_fact);
//        DecompositionManager::Instance().logTime(fout,12);
        *(St - 1) = 0;
//        DecompositionManager::Instance().logTime(fout,13);
        strcpy(str,buf);
//        DecompositionManager::Instance().logTime(fout,14);
        Degrees.push_back(str);
//        fprintf(fout, "%s\n", str);
        //*num = NULL;
       delete []num;
      }
      fclose(fin);
      if(Multipliers.size() != NULL) {
       std::string rez = Degrees[ Degrees.size()-1];
        int a = 0;
        int b = Multipliers.size()-1;
        if(nmbr == Multipliers[ b]) {
//            fclose(fout);
            delete []buf;
            delete []str;
            std::string openFile = (std::string("table_")+i.ToString()+std::string(".txt"));
            return Degrees[b]+std::string(",")+openFile;
        }
        while(b-a > 1) {
          if(nmbr > Multipliers[(a + b)/2]) {
            a = (a + b)/2;
          } else{
            if(nmbr < Multipliers[(a + b)/2]) {
             b = (a + b)/2;
            }
          }
          if(nmbr == Multipliers[(a + b)/2]) {
//            n = ((a + b)/2) + 1;
//            fclose(fout);
            delete []buf;
            delete []str;
            std::string openFile = (std::string("table_")+i.ToString()+std::string(".txt"));

            return Degrees[(a + b)/2]+std::string(",")+openFile;
          }
        }
       Multipliers.clear();
       Degrees.clear();
      }
    }
//   fclose(fout);
//throw std::invalid_argument("????? ?? ????? ?????????? ?? ??????? ?????????.");
delete []buf;
delete []str;
return std::string("");

}
//------------------------------------------------------------------------------
  DecVector DecompositionManager:: getDecomposition(const Integer & number, bool *composit)
  {  DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);


        /*????? ?????????? n-1*/
     Integer one("1");
     std::string n = "";
     std::string str_addres = "";
     int f = 0;
     std::string DegreeAndName = FindEqualNumberInTheDecompositionsDB(number );//- one);
     if(DegreeAndName[0] != NULL){
       for(unsigned int j = 0; j < DegreeAndName.size(); j++)
       {
         if(f == 0 && DegreeAndName[j] != ',') n += DegreeAndName[j];
         if(f == 1) str_addres += DegreeAndName[j];
         if (DegreeAndName[j] == ',') f = 1;
       }
       std::vector<DecompositionMember> vector(DecompositionManager::Instance().getDecompositionFromFile(str_addres, atoi((n).c_str())));
       *composit = DecompositionManager::Instance().TestComposit(str_addres, atoi((n).c_str()));
       return   vector;
     }
    return vector;
  }
//---------------------------------------------------------------------------------
      std::vector<int> DecompositionManager::FindBase(Integer num) {
        std::vector<int> result;
        Integer number = num;
        int div = 2;
        int degree = 0;
        int base;
        while(number != 1){
         Integer rez = number%div;
         if(rez == 0 ) {
           number = number/div;
           degree++;
         } else {
            div++;
            degree = 0;
           }
         if(div == 13){
                result.push_back(0);
                return result;
         }
        }
        result.push_back(div);
        result.push_back(degree);
        return  result;
      }
//-----------------------------------------------------------------------------
  DecVector DecompositionManager::getDecompositionFromFile(std::string str_addres,uint degree)
  {
    FILE *fin;
    uint n_str;
    char str[1500];
    char str_buf[1500];
    char *str_fact;
   // int pos = 0;
    DecVector vector;
    fin=fopen(("../Decompositions/"+str_addres).c_str(),"rt");
    if(!fin)
    {
      throw new Exception("Файл не найден");
    }
    n_str = 0;
    while(n_str != degree)
    {
      fgets(str,1500,fin);
      char* p;
      for(p=str; *p!=' ';p++){ if(*p==0)break; }
      *p=0;
      n_str=atoi(str);
      *p=' ';
      if(n_str > degree)
      {
       return vector;
      }
     // str = str_fact;
    }

    str_fact = strchr(str, ' ') + 1;
    str_fact[strcspn(str_fact,"\n")] = '\0';
    fclose(fin);

    // ???????? ????????
    str_buf[0]='\0';
    for(char* pos=strtok(str_fact," "); pos != NULL; pos = strtok(NULL," "))
    {
      strcat(str_buf, pos);
    }
    Integer Int_num("0",Dec);

    int param = 0;
    for(char* pos=strtok(str_buf,"{,}\r\n"); pos != NULL; pos = strtok(NULL,"{,}\r\n"))
    {
      if (param == 0)
      {
      Int_num.Parse(pos,Dec);
      param = 1;
      continue;
      }
      Integer Int_degree(pos,Dec);
      DecompositionMember a(Int_num,Int_degree);
       vector.push_back(a);
      param = 0;
    }
    //}
    if (vector.size() == 0)
      throw new Exception("База не содержит разложение для данного числа.");

    return  vector;


  }

//------------------------------------------------------------------------------


DecVector DecompositionManager::getCheckedDecompositionFromFile(uint degree, uint maxDegree, std::string fileName)
{
  if(degree > maxDegree)
  {
    DecVector vector;
    return  vector;
    //throw new Exception("Для данного числа разложение в базе отсутствует.");
  }
  return getDecompositionFromFile(fileName,degree);
}
//------------------------------------------------------------------------------


DecVector DecompositionManager::getTenDegreeDecomposition(uint degree, bool withOne)
{
  if(withOne)
  {
    return getCheckedDecompositionFromFile(degree, 150,"table_4.txt");
  }
  return getCheckedDecompositionFromFile(degree, 150,"table_3.txt");
}
//-----------------------------------------------------------------------------
DecVector DecompositionManager::getTwoDegreeDecomposition(uint degree, bool withOne)
{
  if(withOne)
  {
    return getCheckedDecompositionFromFile(degree, 400, "table_2.txt");
  }
  return getCheckedDecompositionFromFile(degree, 400, "table_1.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getOddTwoDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
  {
   return getCheckedDecompositionFromFile(degree, 1200,"table_6.txt");
  }
  return getCheckedDecompositionFromFile(degree, 1200, "table_5.txt");
}
//------------------------------------------------------------------------------
//2^n+1 n=4k-2 n<2400

DecVector DecompositionManager::getEvenLargeTwoDegreeWithOneDecomposition(uint degree)
{
  return getCheckedDecompositionFromFile(degree, 2400, "table_7.txt");
}
//------------------------------------------------------------------------------
 // 2^n+1   n=4k n<=1200

DecVector DecompositionManager::getEvenTwoDegreeWithOneDecomposition(uint degree)
{
  return getCheckedDecompositionFromFile(degree,1200, "table_8.txt");
}

 //----------------------------------------------------------------------------
DecVector DecompositionManager::getThreeDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
    {
     return getCheckedDecompositionFromFile(degree,1077 ,"table_10.txt");
    }
    return getCheckedDecompositionFromFile(degree,540 ,"table_9.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getFiveDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
    {
    return getCheckedDecompositionFromFile(degree,375 ,"table_12.txt");
    }
    return getCheckedDecompositionFromFile(degree,745 ,"table_11.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getSixDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
    {
    return getCheckedDecompositionFromFile(degree,654 ,"table_14.txt");
    }
  return getCheckedDecompositionFromFile(degree,330 ,"table_13.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getSevenDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
    {
    return getCheckedDecompositionFromFile(degree,595 ,"table_16.txt");
    }
  return getCheckedDecompositionFromFile(degree,300 ,"table_15.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getOddTenDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
    {
     return getCheckedDecompositionFromFile(degree,650 ,"table_18.txt");

    }
  return getCheckedDecompositionFromFile(degree,330 ,"table_17.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getElevenDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
  {
    return getCheckedDecompositionFromFile(degree,473,"table_20.txt");
  }
  return getCheckedDecompositionFromFile(degree, 239,"table_19.txt");
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getTwelveDegreeDecomposition(uint degree, bool withOne)
{
	if(withOne)
      {
      return getCheckedDecompositionFromFile(degree, 477,"table_22.txt");
      }
  return getCheckedDecompositionFromFile(degree, 240,"table_21.txt");
}
//------------------------------------------------------------------------------

   //(10^2n)-1
DecVector DecompositionManager::getSpecialTenDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 150))
  {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2, 150,"table_4.txt");
    DecVector vectorWithoutOne = getCheckedDecompositionFromFile(degree/2, 150,"table_3.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
  return  vector;
}
//-----------------------------------------------------------------------------
// (2^2n)-1
DecVector DecompositionManager::getSpecialTwoDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);
	if((degree%2 == 0) && (degree/2 <= 400))
  {
    DecVector vectorWithOne =  getCheckedDecompositionFromFile(degree/2, 400, "table_2.txt");
    DecVector vectorWithoutOne = getCheckedDecompositionFromFile(degree/2, 400, "table_1.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
  return vector;
}
//------------------------------------------------------------------------------
//(2^2n)-1
DecVector DecompositionManager::getSpecialOddTwoDegreeDecomposition(uint degree)
{    DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 1200))
  {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2, 1200,"table_6.txt");
    DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2, 1200, "table_5.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
  return vector;
}
//------------------------------------------------------------------------------
//2^n+1 n=4k-2 n<2400      ?

DecVector DecompositionManager::getSpecialEvenLargeTwoDegreeWithOneDecomposition(uint degree)
{
  int CompositeDegrees[200] = {1238,1262,1294,1306,1318,1322,1334,1342,1366,1378,1382,1402,1406,1418,1430,1450,1454,1458,1462,1466,1478,1490,1502,1522,1526,1534,1538,1550,1574,1582,1586,1598,1606,1610,1618,1622,1630,1634,16421646,1654,1658,1666,1670,1678,1682,1686,1690,1694,1706,1714,1718,1726,1730,1734,1754,1758,1762,1766,1774,1778,1782,1786,1790,1794,1798,1806,1814,1822,1826,1834,1838,1846,1862,1870,1874,1882,1886,1894,1898,1906,1910,1914,1918,1922,1926,1930,1934,1942,1946,1954,1962,1970,1978,1982,1990,2002,2006,2018,2026,2030,2034,2038,2042,2046,2050,2062,2066,2070,2074,2078,2086,2090,2094,2098,2102,2106,2110,2114,2118,2126,2142,2146,2150,2154,2158,2162,2166,2170,2174,2187,2186,2190,2194,2198,2202,2206,2210,2214,2218,2222,2226,2230,2238,2242,2246,2250,2262,2266,2270,2278,2282,2286,2290,2294,2298,2302,2306,2310,2318,23180,2326,2330,2334,2338,2342,2346,2350,2354,2358,2362,2370,2374,2378,2380,2386,2390,2394,2398};
  //Message(CompositeDegrees,181,degree);
  return getCheckedDecompositionFromFile(degree, 2400, "table_7.txt");
}
//------------------------------------------------------------------------------
 // 2^n+1   n=4k n<=1200     ?

DecVector DecompositionManager::getSpecialEvenTwoDegreeWithOneDecomposition(uint degree)
{
  int CompositeDegrees[54] = {716,736,760,764,772,776,788,820,824,832,836,856,860,904,908,916,928,932,956,964,972,980,984,988,1000,1012,1028,1036,1040,1044,1052,1064,1068,1072,1076,1084,1088,1100,1104,1108,1120,1124,1128,1136,1144,1152,1164,1168,1172,1176,1180,1188,1196};
  //Message(CompositeDegrees,48,degree);
  return getCheckedDecompositionFromFile(degree,1200, "table_8.txt");
}

 //----------------------------------------------------------------------------
 //(3^2n)-1
DecVector DecompositionManager::getSpecialThreeDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 540))
    {
     DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2,1077 ,"table_10.txt");
     DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2,540 ,"table_9.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;
}
//------------------------------------------------------------------------------
// (5^2n)-1
DecVector DecompositionManager::getSpecialFiveDegreeDecomposition(uint degree)
{    DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == degree) && (degree/2 <= 375))
    {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2,375 ,"table_12.txt");
    DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2,745 ,"table_11.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;
}
//------------------------------------------------------------------------------
//(6^2n)-1
DecVector DecompositionManager::getSpecialSixDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 330))
    {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2,654 ,"table_14.txt");
    DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2,330 ,"table_13.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;
}
//------------------------------------------------------------------------------
//(7^2n)-1
DecVector DecompositionManager::getSpecialSevenDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 300))
    {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2,595 ,"table_16.txt");
    DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2,300 ,"table_15.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;
}
//------------------------------------------------------------------------------
//(10^2n)-1
DecVector DecompositionManager::getSpecialOddTenDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 330))
    {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2, 650,"table_18.txt");
    DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2,330 ,"table_17.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;
}
//------------------------------------------------------------------------------
//(11^2n)-1
DecVector DecompositionManager::getSpecialElevenDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);
	if((degree%2 == 0) && (degree/2 <= 239))
  {
    DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2,473,"table_20.txt");
    DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2, 239,"table_19.txt");
    return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;

}
//------------------------------------------------------------------------------
// (12^2n)-1
DecVector DecompositionManager::getSpecialTwelveDegreeDecomposition(uint degree)
{   DecVector vector;
    DecompositionMember a(0,0);
    vector.push_back(a);

	if((degree%2 == 0) && (degree/2 <= 240))
      {
      DecVector vectorWithOne = getCheckedDecompositionFromFile(degree/2, 477,"table_22.txt");
      DecVector vectorWithoutOne =  getCheckedDecompositionFromFile(degree/2, 240,"table_21.txt");
      return  getSpecialDecomposition(vectorWithOne,  vectorWithoutOne);
  }
return vector;
}

//------------------------------------------------------------------------------
DecVector DecompositionManager::getSpecialDecomposition(DecVector vectorWithOne, DecVector vectorWithoutOne){
DecVector result;
DecVector::iterator iter,it;
iter = vectorWithoutOne.begin();
for(it = vectorWithOne.begin(); it != vectorWithOne.end(); it++){
  while(iter != vectorWithoutOne.end() && iter->getNumber() < it->getNumber()) {
    result.push_back(*iter);
    iter++;
  }
  if(iter != vectorWithoutOne.end() && iter->getNumber() == it->getNumber()) {
    Integer degree(iter->getDegree());
    degree = degree + it->getDegree();
    DecompositionMember a(iter->getNumber(),degree);
    result.push_back(a);
    iter++;
  }else{
    result.push_back(*it);
  }
}
while(iter != vectorWithoutOne.end()) {
  result.push_back(*iter);
  iter++;
}
return result;
}
//------------------------------------------------------------------------------
DecVector DecompositionManager::getDecompositionFromDB(Integer & number, bool *composit){
DecVector result;
  std::vector<int> BaseAndDegree = FindBase(number);
  unsigned int b =  BaseAndDegree[0];
  unsigned int n =  BaseAndDegree[1];
  if(n > 2400)
  {
    return result;
  }
  if(b == 0)
  {
    DecompositionMember rez(0,0);
    result.push_back(rez);
    //throw  std::domain_error("Разложение для данного числа в базе отсутствует.");
  }
  else
  {
  if(b > 2){
        if(n%2 == 1) {
                switch (b) {
                        case 3: return  getThreeDegreeDecomposition(n, false);
                        case 5: return  getFiveDegreeDecomposition(n, false);
                        case 6: return  getSixDegreeDecomposition(n, false);
                        case 7: return  getSevenDegreeDecomposition(n, false);
                        case 10: return  getOddTenDegreeDecomposition(n, false);
                        case 11: return  getElevenDegreeDecomposition(n, false);
                        case 12: return  getTwelveDegreeDecomposition(n,false);
                }
        }
        else {
                if(n == 2){
                        switch (b) {
                                case 3: return  getSpecialDecomposition(getThreeDegreeDecomposition(n/2, true), getThreeDegreeDecomposition(n/2, false));
                                case 5: return  getSpecialDecomposition(getFiveDegreeDecomposition(n/2, true), getFiveDegreeDecomposition(n/2, false));
                                case 6: return  getSpecialDecomposition(getSixDegreeDecomposition(n/2, true), getSixDegreeDecomposition(n/2, false));
                                case 7: return  getSpecialDecomposition(getSevenDegreeDecomposition(n/2, true), getSevenDegreeDecomposition(n/2, false));
                                case 10: return  getSpecialDecomposition(getOddTenDegreeDecomposition(n/2, true), getOddTenDegreeDecomposition(n/2, false));
                                case 11: return  getSpecialDecomposition(getElevenDegreeDecomposition(n/2, true), getElevenDegreeDecomposition(n/2, false));
                                case 12: return  getSpecialDecomposition(getTwelveDegreeDecomposition(n/2,true), getTwelveDegreeDecomposition(n/2,false));
                        }
                }
                else
                { std::vector<DecompositionMember> decomposition, newdecomposition;
                  n = n/2;
                  switch (b) {
                        case 3:  decomposition = getThreeDegreeDecomposition(n, true); break;
                        case 5:  decomposition = getFiveDegreeDecomposition(n, true); break;
                        case 6:  decomposition = getSixDegreeDecomposition(n, true); break;
                        case 7:  decomposition = getSevenDegreeDecomposition(n, true); break;
                        case 10: decomposition = getOddTenDegreeDecomposition(n, true); break;
                        case 11: decomposition = getElevenDegreeDecomposition(n, true); break;
                        case 12: decomposition = getTwelveDegreeDecomposition(n,true); break;
                  }
                  if(decomposition.size() < 1)
                         {
                           return result;
                         }
                 while(n != 1 && n%2 == 0) {
                        n = n/2;
                        if(n != 1) {
                        switch (b) {
                                case 3: newdecomposition = getSpecialDecomposition(getThreeDegreeDecomposition(n, true), decomposition); break;
                                case 5: newdecomposition = getSpecialDecomposition(getFiveDegreeDecomposition(n, true), decomposition);  break;
                                case 6: newdecomposition = getSpecialDecomposition(getSixDegreeDecomposition(n, true), decomposition);  break;
                                case 7: newdecomposition = getSpecialDecomposition(getSevenDegreeDecomposition(n, true), decomposition); break;
                                case 10: newdecomposition = getSpecialDecomposition(getOddTenDegreeDecomposition(n, true), decomposition); break;
                                case 11: newdecomposition = getSpecialDecomposition(getElevenDegreeDecomposition(n, true), decomposition); break;
                                case 12: newdecomposition = getSpecialDecomposition(getTwelveDegreeDecomposition(n,true), decomposition); break;
                        }
                         decomposition = newdecomposition;
                         if(decomposition.size() < 1)
                         {
                           return result;
                         }
                        }
                        else {
                        switch (b) {
                                case 3: newdecomposition = getSpecialDecomposition(getThreeDegreeDecomposition(n, true), getThreeDegreeDecomposition(n, false));  break;
                                case 5: newdecomposition = getSpecialDecomposition(getFiveDegreeDecomposition(n, true), getFiveDegreeDecomposition(n, false));  break;
                                case 6: newdecomposition = getSpecialDecomposition(getSixDegreeDecomposition(n, true), getSixDegreeDecomposition(n, false));  break;
                                case 7: newdecomposition = getSpecialDecomposition(getSevenDegreeDecomposition(n, true), getSevenDegreeDecomposition(n, false));  break;
                                case 10: newdecomposition = getSpecialDecomposition(getOddTenDegreeDecomposition(n, true), getOddTenDegreeDecomposition(n, false));  break;
                                case 11: newdecomposition = getSpecialDecomposition(getElevenDegreeDecomposition(n, true), getElevenDegreeDecomposition(n, false));  break;
                                case 12: newdecomposition = getSpecialDecomposition(getTwelveDegreeDecomposition(n,true), getTwelveDegreeDecomposition(n,false));  break;
                        }
                        switch (b) {
                                case 3: return getSpecialDecomposition(newdecomposition, decomposition);
                                case 5: return getSpecialDecomposition(newdecomposition, decomposition);
                                case 6: return getSpecialDecomposition(newdecomposition, decomposition);
                                case 7: return getSpecialDecomposition(newdecomposition, decomposition);
                                case 10: return getSpecialDecomposition(newdecomposition, decomposition);
                                case 11: return getSpecialDecomposition(newdecomposition, decomposition);
                                case 12: return getSpecialDecomposition(newdecomposition, decomposition);
                        }

                        }
                 }
                        switch (b) {
                                case 3: return  getSpecialDecomposition(decomposition, getThreeDegreeDecomposition(n, false));
                                case 5: return  getSpecialDecomposition(decomposition, getFiveDegreeDecomposition(n, false));
                                case 6: return  getSpecialDecomposition(decomposition, getSixDegreeDecomposition(n, false));
                                case 7: return  getSpecialDecomposition(decomposition, getSevenDegreeDecomposition(n, false));
                                case 10: return  getSpecialDecomposition(decomposition, getOddTenDegreeDecomposition(n, false));
                                case 11: return  getSpecialDecomposition(decomposition, getElevenDegreeDecomposition(n, false));
                                case 12: return  getSpecialDecomposition(decomposition, getTwelveDegreeDecomposition(n,false));
                        }

                }
        }

  }
  else
  {
    if(n%2 == 1){
      return getOddTwoDegreeDecomposition(n, false);
    }
    else
    {
      if((n/2)%2 == 1) {
        n = n/2;
        return getSpecialDecomposition(getOddTwoDegreeDecomposition(n, false), getOddTwoDegreeDecomposition(n, true));
      }
      else
      {
        std::vector<DecompositionMember> decomposition, newdecomposition;
        n = n/2;
        if(n%4 == 0){
          decomposition = getEvenTwoDegreeWithOneDecomposition(n);
        }
        else
        {
          decomposition = getEvenLargeTwoDegreeWithOneDecomposition(n);
        }
        while(n != 1 && n%2 == 0)
        {
          n = n/2;
          if(n%4 == 0)
          {
            newdecomposition =  getSpecialDecomposition(decomposition, getEvenTwoDegreeWithOneDecomposition(n));
          }
          else
          { if(n != 1)
              newdecomposition =  getSpecialDecomposition(decomposition, getEvenLargeTwoDegreeWithOneDecomposition(n));
          }
          decomposition = newdecomposition;
          if(n == 1){

            return  getSpecialDecomposition(decomposition, getOddTwoDegreeDecomposition(n, true));
          }
        }
        newdecomposition =  getSpecialDecomposition(getOddTwoDegreeDecomposition(n, false), getOddTwoDegreeDecomposition(n, true));
        return  getSpecialDecomposition(newdecomposition, decomposition);
      }
    }
  }
  }
  return result;
}
//------------------------------------------------------------------------------
// (c)Chernysheva
// разложение числа на простые
DecVector DecompositionManager::getPrimeDecomposition(uint number)
{
  return getDecompositionFromFile("DecompositionPrime.txt", number);
}
//------------------------------------------------------------------------------

};





















