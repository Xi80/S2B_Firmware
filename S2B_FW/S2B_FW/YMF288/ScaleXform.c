/*
 * ScaleXform.c
 *
 * Created: 2022/03/23 10:11:43
 *  Author: Owner
 */ 

#include "ScaleXform.h"


const PROGMEM uint16_t fm_tone_table[768] = {
	1038,1039,1040,1041,1042,1043,1044,1045,
	1046,1047,1048,1048,1049,1050,1051,1052,
	1053,1054,1055,1056,1057,1058,1059,1060,
	1061,1062,1063,1064,1065,1066,1067,1068,
	1069,1069,1070,1071,1072,1073,1074,1075,
	1076,1077,1078,1079,1080,1081,1082,1083,
	1084,1085,1086,1087,1088,1089,1090,1091,
	1092,1093,1094,1095,1096,1097,1098,1099,
	1100,1101,1102,1103,1104,1105,1106,1107,
	1108,1109,1110,1111,1112,1113,1114,1115,
	1116,1117,1118,1119,1120,1121,1122,1123,
	1124,1125,1126,1127,1128,1129,1130,1131,
	1132,1133,1134,1135,1136,1137,1138,1139,
	1140,1141,1142,1143,1144,1145,1146,1147,
	1149,1150,1151,1152,1153,1154,1155,1156,
	1157,1158,1159,1160,1161,1162,1163,1164,
	1165,1166,1167,1168,1169,1170,1172,1173,
	1174,1175,1176,1177,1178,1179,1180,1181,
	1182,1183,1184,1185,1186,1188,1189,1190,
	1191,1192,1193,1194,1195,1196,1197,1198,
	1199,1200,1202,1203,1204,1205,1206,1207,
	1208,1209,1210,1211,1212,1214,1215,1216,
	1217,1218,1219,1220,1221,1222,1223,1225,
	1226,1227,1228,1229,1230,1231,1232,1233,
	1235,1236,1237,1238,1239,1240,1241,1242,
	1243,1245,1246,1247,1248,1249,1250,1251,
	1252,1254,1255,1256,1257,1258,1259,1260,
	1262,1263,1264,1265,1266,1267,1268,1270,
	1271,1272,1273,1274,1275,1276,1278,1279,
	1280,1281,1282,1283,1285,1286,1287,1288,
	1289,1290,1291,1293,1294,1295,1296,1297,
	1299,1300,1301,1302,1303,1304,1306,1307,
	1308,1309,1310,1311,1313,1314,1315,1316,
	1317,1319,1320,1321,1322,1323,1325,1326,
	1327,1328,1329,1331,1332,1333,1334,1335,
	1337,1338,1339,1340,1341,1343,1344,1345,
	1346,1347,1349,1350,1351,1352,1354,1355,
	1356,1357,1358,1360,1361,1362,1363,1365,
	1366,1367,1368,1370,1371,1372,1373,1374,
	1376,1377,1378,1379,1381,1382,1383,1384,
	1386,1387,1388,1389,1391,1392,1393,1394,
	1396,1397,1398,1400,1401,1402,1403,1405,
	1406,1407,1408,1410,1411,1412,1413,1415,
	1416,1417,1419,1420,1421,1422,1424,1425,
	1426,1428,1429,1430,1431,1433,1434,1435,
	1437,1438,1439,1441,1442,1443,1444,1446,
	1447,1448,1450,1451,1452,1454,1455,1456,
	1458,1459,1460,1461,1463,1464,1465,1467,
	1468,1469,1471,1472,1473,1475,1476,1477,
	1479,1480,1481,1483,1484,1485,1487,1488,
	1489,1491,1492,1493,1495,1496,1498,1499,
	1500,1502,1503,1504,1506,1507,1508,1510,
	1511,1512,1514,1515,1517,1518,1519,1521,
	1522,1523,1525,1526,1528,1529,1530,1532,
	1533,1534,1536,1537,1539,1540,1541,1543,
	1544,1546,1547,1548,1550,1551,1553,1554,
	1555,1557,1558,1560,1561,1562,1564,1565,
	1567,1568,1569,1571,1572,1574,1575,1577,
	1578,1579,1581,1582,1584,1585,1587,1588,
	1589,1591,1592,1594,1595,1597,1598,1600,
	1601,1602,1604,1605,1607,1608,1610,1611,
	1613,1614,1615,1617,1618,1620,1621,1623,
	1624,1626,1627,1629,1630,1632,1633,1635,
	1636,1637,1639,1640,1642,1643,1645,1646,
	1648,1649,1651,1652,1654,1655,1657,1658,
	1660,1661,1663,1664,1666,1667,1669,1670,
	1672,1673,1675,1676,1678,1679,1681,1682,
	1684,1685,1687,1689,1690,1692,1693,1695,
	1696,1698,1699,1701,1702,1704,1705,1707,
	1708,1710,1712,1713,1715,1716,1718,1719,
	1721,1722,1724,1725,1727,1729,1730,1732,
	1733,1735,1736,1738,1740,1741,1743,1744,
	1746,1747,1749,1751,1752,1754,1755,1757,
	1759,1760,1762,1763,1765,1766,1768,1770,
	1771,1773,1774,1776,1778,1779,1781,1782,
	1784,1786,1787,1789,1791,1792,1794,1795,
	1797,1799,1800,1802,1804,1805,1807,1808,
	1810,1812,1813,1815,1817,1818,1820,1822,
	1823,1825,1826,1828,1830,1831,1833,1835,
	1836,1838,1840,1841,1843,1845,1846,1848,
	1850,1851,1853,1855,1856,1858,1860,1861,
	1863,1865,1866,1868,1870,1871,1873,1875,
	1877,1878,1880,1882,1883,1885,1887,1888,
	1890,1892,1894,1895,1897,1899,1900,1902,
	1904,1906,1907,1909,1911,1912,1914,1916,
	1918,1919,1921,1923,1925,1926,1928,1930,
	1932,1933,1935,1937,1939,1940,1942,1944,
	1946,1947,1949,1951,1953,1954,1956,1958,
	1960,1961,1963,1965,1967,1969,1970,1972,
	1974,1976,1977,1979,1981,1983,1985,1986,
	1988,1990,1992,1994,1995,1997,1999,2001,
	2003,2004,2006,2008,2010,2012,2013,2015,
	2017,2019,2021,2023,2024,2026,2028,2030,
	2032,2034,2035,2037,2039,2041,2043,2045,
	2046,2048,2050,2052,2054,2056,2058,2059,
	2061,2063,2065,2067,2069,2071,2072,2074
};
const PROGMEM uint16_t psg_tone_table[768] ={
	284,283,283,283,
	283,282,282,282,
	282,281,281,281,
	281,280,280,280,
	280,279,279,279,
	279,278,278,278,
	278,277,277,277,
	277,276,276,276,
	276,275,275,275,
	275,274,274,274,
	274,273,273,273,
	273,272,272,272,
	272,271,271,271,
	271,270,270,270,
	270,269,269,269,
	269,268,268,268,
	268,267,267,267,
	267,266,266,266,
	266,265,265,265,
	265,265,264,264,
	264,264,263,263,
	263,263,262,262,
	262,262,261,261,
	261,261,260,260,
	260,260,260,259,
	259,259,259,258,
	258,258,258,257,
	257,257,257,257,
	256,256,256,256,
	255,255,255,255,
	254,254,254,254,
	254,253,253,253,
	253,252,252,252,
	252,251,251,251,
	251,251,250,250,
	250,250,249,249,
	249,249,249,248,
	248,248,248,247,
	247,247,247,247,
	246,246,246,246,
	245,245,245,245,
	245,244,244,244,
	244,243,243,243,
	243,243,242,242,
	242,242,241,241,
	241,241,241,240,
	240,240,240,239,
	239,239,239,239,
	238,238,238,238,
	238,237,237,237,
	237,236,236,236,
	236,236,235,235,
	235,235,235,234,
	234,234,234,233,
	233,233,233,233,
	232,232,232,232,
	232,231,231,231,
	231,231,230,230,
	230,230,230,229,
	229,229,229,228,
	228,228,228,228,
	227,227,227,227,
	227,226,226,226,
	226,226,225,225,
	225,225,225,224,
	224,224,224,224,
	223,223,223,223,
	223,222,222,222,
	222,222,221,221,
	221,221,221,220,
	220,220,220,220,
	219,219,219,219,
	219,218,218,218,
	218,218,217,217,
	217,217,217,216,
	216,216,216,216,
	215,215,215,215,
	215,214,214,214,
	214,214,213,213,
	213,213,213,213,
	212,212,212,212,
	212,211,211,211,
	211,211,210,210,
	210,210,210,209,
	209,209,209,209,
	209,208,208,208,
	208,208,207,207,
	207,207,207,206,
	206,206,206,206,
	206,205,205,205,
	205,205,204,204,
	204,204,204,203,
	203,203,203,203,
	203,202,202,202,
	202,202,201,201,
	201,201,201,201,
	200,200,200,200,
	200,199,199,199,
	199,199,199,198,
	198,198,198,198,
	198,197,197,197,
	197,197,196,196,
	196,196,196,196,
	195,195,195,195,
	195,194,194,194,
	194,194,194,193,
	193,193,193,193,
	193,192,192,192,
	192,192,192,191,
	191,191,191,191,
	190,190,190,190,
	190,190,189,189,
	189,189,189,189,
	188,188,188,188,
	188,188,187,187,
	187,187,187,187,
	186,186,186,186,
	186,186,185,185,
	185,185,185,185,
	184,184,184,184,
	184,184,183,183,
	183,183,183,183,
	182,182,182,182,
	182,182,181,181,
	181,181,181,181,
	180,180,180,180,
	180,180,179,179,
	179,179,179,179,
	178,178,178,178,
	178,178,177,177,
	177,177,177,177,
	177,176,176,176,
	176,176,176,175,
	175,175,175,175,
	175,174,174,174,
	174,174,174,174,
	173,173,173,173,
	173,173,172,172,
	172,172,172,172,
	171,171,171,171,
	171,171,171,170,
	170,170,170,170,
	170,169,169,169,
	169,169,169,169,
	168,168,168,168,
	168,168,168,167,
	167,167,167,167,
	167,166,166,166,
	166,166,166,166,
	165,165,165,165,
	165,165,165,164,
	164,164,164,164,
	164,163,163,163,
	163,163,163,163,
	162,162,162,162,
	162,162,162,161,
	161,161,161,161,
	161,161,160,160,
	160,160,160,160,
	160,159,159,159,
	159,159,159,159,
	158,158,158,158,
	158,158,158,157,
	157,157,157,157,
	157,157,156,156,
	156,156,156,156,
	156,155,155,155,
	155,155,155,155,
	154,154,154,154,
	154,154,154,153,
	153,153,153,153,
	153,153,152,152,
	152,152,152,152,
	152,151,151,151,
	151,151,151,151,
	151,150,150,150,
	150,150,150,150,
	149,149,149,149,
	149,149,149,149,
	148,148,148,148,
	148,148,148,147,
	147,147,147,147,
	147,147,147,146,
	146,146,146,146,
	146,146,145,145,
	145,145,145,145,
	145,145,144,144,
	144,144,144,144,
	144,143,143,143,
	143,143,143,143,
	143,142,142,142,
	142,142,142,142,

};

struct FNumber_t getPSGFnum(uint8_t noteNumber,uint8_t pbs,uint16_t pb){
	short dpb = (uint8_t)(pb >> 7) - 64;
	
	uint16_t internal_tone = ((noteNumber + 3) << 6) + (dpb * pbs);
	
	uint8_t oct = internal_tone / 768;
	uint16_t tone = internal_tone - (oct * 768);
	
	struct FNumber_t ret;
	uint16_t readTone = pgm_read_word_near(psg_tone_table + tone);
	if(oct > 6){
		ret.fNumber = readTone >> (oct - 6);
		} else {
		ret.fNumber = readTone << (6 - oct);
	}
	return ret;
}

struct FNumber_t getOPNAFnum(uint8_t noteNumber,uint8_t pbs,uint16_t pb){
	short dpb = (uint8_t)(pb >> 7) - 64;
	
	uint16_t internal_tone = ((noteNumber + 3) << 6) + (dpb * pbs);
	
	uint8_t oct = internal_tone / 768;
	uint16_t tone = internal_tone - (oct * 768);
	
	struct FNumber_t ret;
	
	ret.block = oct - 2;
	
	ret.fNumber = pgm_read_word_near(fm_tone_table + tone);

	return ret;
}

struct FNumber_t Scale_GetFnumber(enum TG_t tg,uint8_t noteNumber,uint8_t pbs,uint16_t pb){
	switch(tg){
		case OPNA:
			return getOPNAFnum(noteNumber,pbs,pb);
		case PSG:	
		default:
			return getPSGFnum(noteNumber,pbs,pb);
	}	
}