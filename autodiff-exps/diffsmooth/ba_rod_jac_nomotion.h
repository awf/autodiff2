#pragma once

#include "fsharp.h"
#include <stdio.h>
#include <math.h>

array_array_array_number_t ba_rod_jac(array_number_t xs, index_t n) {
  index_t x1353 = (xs)->length;
  array_array_array_number_t x1652 = (array_array_array_number_t)storage_alloc(sizeof(int) * 2);x1652->length=x1353;x1652->arr = (array_array_number_t*)storage_alloc(sizeof(array_array_number_t) * x1353);
  for(int i = 0; i < x1652->length; i++){
    array_array_number_t x1651 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x1651->length=n;x1651->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * n);
    for(int i0 = 0; i0 < x1651->length; i0++){
      index_t x1354 = (3) * (i0);
      number_t x1355 = (xs->arr[0]);
      index_t x1356 = (i) == (0);
      index_t x1357;
      if (x1356) {
        x1357 = 1;
      } else {
        x1357 = 0;
      }
      number_t x1361 = (x1355) * (x1355);
      number_t x1362 = (x1357) * (x1355);
      number_t x1363 = (x1355) * (x1357);
      number_t x1364 = (x1362) + (x1363);
      number_t x1365 = (xs->arr[1]);
      index_t x1366 = (i) == (1);
      index_t x1367;
      if (x1366) {
        x1367 = 1;
      } else {
        x1367 = 0;
      }
      number_t x1371 = (x1365) * (x1365);
      number_t x1372 = (x1367) * (x1365);
      number_t x1373 = (x1365) * (x1367);
      number_t x1374 = (x1372) + (x1373);
      number_t x1375 = (xs->arr[2]);
      index_t x1376 = (i) == (2);
      index_t x1377;
      if (x1376) {
        x1377 = 1;
      } else {
        x1377 = 0;
      }
      number_t x1381 = (x1361) + (x1371);
      number_t x1382 = (x1364) + (x1374);
      number_t x1383 = (x1375) * (x1375);
      number_t x1384 = (x1377) * (x1375);
      number_t x1385 = (x1375) * (x1377);
      number_t x1386 = (x1384) + (x1385);
      number_t x1387 = (x1381) + (x1383);
      number_t x1388 = sqrt(x1387);
      number_t x1389 = (x1382) + (x1386);
      number_t x1390 = (1) / (x1388);
      number_t x1391 = (x1390) * (0.5);
      number_t x1392 = (x1389) * (x1391);
      number_t x1397 = -(x1392);
      number_t x1398 = (x1388) * (x1388);
      number_t x1399 = (x1397) / (x1398);
      index_t x1400 = (11) + (x1354);
      index_t x1401 = (2) + (x1400);
      number_t x1402 = (x1365) * (x1390);
      number_t x1403 = (x1367) * (x1390);
      number_t x1404 = (x1365) * (x1399);
      number_t x1405 = (x1403) + (x1404);
      number_t x1406 = (xs->arr[x1401]);
      index_t x1407 = (i) == (x1401);
      index_t x1408;
      if (x1407) {
        x1408 = 1;
      } else {
        x1408 = 0;
      }
      index_t x1417 = (1) + (x1400);
      number_t x1418 = (x1375) * (x1390);
      number_t x1419 = (x1377) * (x1390);
      number_t x1420 = (x1375) * (x1399);
      number_t x1421 = (x1419) + (x1420);
      number_t x1422 = (xs->arr[x1417]);
      index_t x1423 = (i) == (x1417);
      index_t x1424;
      if (x1423) {
        x1424 = 1;
      } else {
        x1424 = 0;
      }
      number_t x1425 = (x1402) * (x1406);
      number_t x1426 = (x1405) * (x1406);
      number_t x1427 = (x1402) * (x1408);
      number_t x1428 = (x1426) + (x1427);
      number_t x1429 = (x1418) * (x1422);
      number_t x1430 = (x1421) * (x1422);
      number_t x1431 = (x1418) * (x1424);
      number_t x1432 = (x1430) + (x1431);
      number_t x1445 = (xs->arr[x1400]);
      index_t x1446 = (i) == (x1400);
      index_t x1447;
      if (x1446) {
        x1447 = 1;
      } else {
        x1447 = 0;
      }
      number_t x1457 = (x1355) * (x1390);
      number_t x1458 = (x1357) * (x1390);
      number_t x1459 = (x1355) * (x1399);
      number_t x1460 = (x1458) + (x1459);
      number_t x1464 = (x1418) * (x1445);
      number_t x1465 = (x1421) * (x1445);
      number_t x1466 = (x1418) * (x1447);
      number_t x1467 = (x1465) + (x1466);
      number_t x1468 = (x1457) * (x1406);
      number_t x1469 = (x1460) * (x1406);
      number_t x1470 = (x1457) * (x1408);
      number_t x1471 = (x1469) + (x1470);
      number_t x1503 = (x1457) * (x1422);
      number_t x1504 = (x1460) * (x1422);
      number_t x1505 = (x1457) * (x1424);
      number_t x1506 = (x1504) + (x1505);
      number_t x1507 = (x1402) * (x1445);
      number_t x1508 = (x1405) * (x1445);
      number_t x1509 = (x1402) * (x1447);
      number_t x1510 = (x1508) + (x1509);
      number_t x1511 = (x1425) - (x1429);
      number_t x1512 = (x1428) - (x1432);
      tuple_number_t_number_t x1513 = (tuple_number_t_number_t){._1=x1511, ._2=x1512};
      number_t x1514 = (x1464) - (x1468);
      number_t x1515 = (x1467) - (x1471);
      tuple_number_t_number_t x1516 = (tuple_number_t_number_t){._1=x1514, ._2=x1515};
      number_t x1517 = (x1503) - (x1507);
      number_t x1518 = (x1506) - (x1510);
      tuple_number_t_number_t x1519 = (tuple_number_t_number_t){._1=x1517, ._2=x1518};
      array_tuple_number_t_number_t x1520 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x1520->length=3;x1520->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      x1520->arr[0] = x1513;
      x1520->arr[1] = x1516;
      x1520->arr[2] = x1519;
      number_t x1536 = (x1457) * (x1445);
      number_t x1537 = (x1460) * (x1445);
      number_t x1538 = (x1457) * (x1447);
      number_t x1539 = (x1537) + (x1538);
      number_t x1556 = (x1402) * (x1422);
      number_t x1557 = (x1405) * (x1422);
      number_t x1558 = (x1402) * (x1424);
      number_t x1559 = (x1557) + (x1558);
      number_t x1576 = (x1536) + (x1556);
      number_t x1577 = (x1539) + (x1559);
      number_t x1578 = (x1418) * (x1406);
      number_t x1579 = (x1421) * (x1406);
      number_t x1580 = (x1418) * (x1408);
      number_t x1581 = (x1579) + (x1580);
      number_t x1582 = cos(x1388);
      number_t x1587 = sin(x1388);
      number_t x1588 = -(x1587);
      number_t x1589 = (x1392) * (x1588);
      number_t x1590 = (x1576) + (x1578);
      number_t x1591 = (x1577) + (x1581);
      number_t x1592 = (1) - (x1582);
      number_t x1593 = -(x1589);
      array_number_t x1650 = (array_number_t)storage_alloc(sizeof(int) * 2);x1650->length=3;x1650->arr = (number_t*)storage_alloc(sizeof(number_t) * 3);
      for(int i00 = 0; i00 < x1650->length; i00++){
        index_t x1595 = (i00) + (x1400);
        number_t x1596 = (xs->arr[x1595]);
        index_t x1597 = (i) == (x1595);
        index_t x1598;
        if (x1597) {
          x1598 = 1;
        } else {
          x1598 = 0;
        }
        tuple_number_t_number_t x1607 = (x1520->arr[i00]);
        number_t x1608 = (x1607)._1;
        number_t x1609 = (x1607)._2;
        number_t x1616 = (x1392) * (x1582);
        number_t x1617 = (x1596) * (x1582);
        number_t x1618 = (x1598) * (x1582);
        number_t x1619 = (x1596) * (x1589);
        number_t x1620 = (x1618) + (x1619);
        number_t x1621 = (x1608) * (x1587);
        number_t x1622 = (x1609) * (x1587);
        number_t x1623 = (x1608) * (x1616);
        number_t x1624 = (x1622) + (x1623);
        number_t x1625 = (xs->arr[i00]);
        index_t x1626 = (i) == (i00);
        index_t x1627;
        if (x1626) {
          x1627 = 1;
        } else {
          x1627 = 0;
        }
        number_t x1632 = (x1625) * (x1390);
        number_t x1633 = (x1627) * (x1390);
        number_t x1634 = (x1625) * (x1399);
        number_t x1635 = (x1633) + (x1634);
        number_t x1636 = (x1590) * (x1592);
        number_t x1637 = (x1591) * (x1592);
        number_t x1638 = (x1590) * (x1593);
        number_t x1639 = (x1637) + (x1638);
        number_t x1640 = (x1617) + (x1621);
        number_t x1641 = (x1620) + (x1624);
        number_t x1642 = (x1632) * (x1636);
        number_t x1643 = (x1635) * (x1636);
        number_t x1644 = (x1632) * (x1639);
        number_t x1645 = (x1643) + (x1644);
        number_t x1646 = (x1640) + (x1642);
        number_t x1647 = (x1641) + (x1645);
        tuple_number_t_number_t x1648 = (tuple_number_t_number_t){._1=x1646, ._2=x1647};
        number_t x1649 = (x1648)._2;
        x1650->arr[i00] = x1649;
        
      }
      x1651->arr[i0] = x1650;
      
    }
    x1652->arr[i] = x1651;
    
  }
  return x1652;
}

array_array_array_number_t ba_proj_jac(array_number_t xs, index_t n) {
  array_array_array_number_t x6242 = (array_array_array_number_t)storage_alloc(sizeof(int) * 2);x6242->length=(xs)->length;x6242->arr = (array_array_number_t*)storage_alloc(sizeof(array_array_number_t) * (xs)->length);
  for(int i = 0; i < x6242->length; i++){
    array_array_number_t x6241 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x6241->length=n;x6241->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * n);
    for(int i0 = 0; i0 < x6241->length; i0++){
      index_t x5481 = (3) * (i0);
      number_t x5624 = (xs->arr[0]);
      index_t x5622;
      if ((i) == (0)) {
        x5622 = 1;
      } else {
        x5622 = 0;
      }
      number_t x5625 = (xs->arr[0]);
      index_t x5623;
      if ((i) == (0)) {
        x5623 = 1;
      } else {
        x5623 = 0;
      }
      number_t x5637 = (x5624) * (x5625);
      number_t x5635 = ((x5622) * (x5625)) + ((x5624) * (x5623));
      number_t x56240 = (xs->arr[1]);
      index_t x56220;
      if ((i) == (1)) {
        x56220 = 1;
      } else {
        x56220 = 0;
      }
      number_t x56250 = (xs->arr[1]);
      index_t x56230;
      if ((i) == (1)) {
        x56230 = 1;
      } else {
        x56230 = 0;
      }
      number_t x56360 = (0) + (x5637);
      number_t x56340 = (0) + (x5635);
      number_t x56370 = (x56240) * (x56250);
      number_t x56350 = ((x56220) * (x56250)) + ((x56240) * (x56230));
      number_t x56241 = (xs->arr[2]);
      index_t x56221;
      if ((i) == (2)) {
        x56221 = 1;
      } else {
        x56221 = 0;
      }
      number_t x56251 = (xs->arr[2]);
      index_t x56231;
      if ((i) == (2)) {
        x56231 = 1;
      } else {
        x56231 = 0;
      }
      number_t x56361 = (x56360) + (x56370);
      number_t x56341 = (x56340) + (x56350);
      number_t x56371 = (x56241) * (x56251);
      number_t x56351 = ((x56221) * (x56251)) + ((x56241) * (x56231));
      number_t x5515 = sqrt((x56361) + (x56371));
      number_t x5611 = ((x56341) + (x56351)) * (((1) / (x5515)) * (0.5));
      number_t x5942 = (xs->arr[1]);
      index_t x5940;
      if ((i) == (1)) {
        x5940 = 1;
      } else {
        x5940 = 0;
      }
      number_t x5943 = (1) / (x5515);
      number_t x5941 = (-(x5611)) / ((x5515) * (x5515));
      index_t x5883 = (11) + (x5481);
      index_t j0 = (2) + (x5883);
      number_t x6026 = (xs->arr[j0]);
      index_t x6024;
      if ((i) == (j0)) {
        x6024 = 1;
      } else {
        x6024 = 0;
      }
      number_t x6027 = (xs->arr[5]);
      index_t x6025;
      if ((i) == (5)) {
        x6025 = 1;
      } else {
        x6025 = 0;
      }
      number_t x5768 = (x5942) * (x5943);
      number_t x5766 = ((x5940) * (x5943)) + ((x5942) * (x5941));
      number_t x5769 = (x6026) - (x6027);
      index_t x5767 = (x6024) - (x6025);
      number_t x5930 = (xs->arr[2]);
      index_t x5928;
      if ((i) == (2)) {
        x5928 = 1;
      } else {
        x5928 = 0;
      }
      number_t x5931 = (1) / (x5515);
      number_t x5929 = (-(x5611)) / ((x5515) * (x5515));
      index_t x5871 = (11) + (x5481);
      index_t j10 = (1) + (x5871);
      number_t x6014 = (xs->arr[j10]);
      index_t x6012;
      if ((i) == (j10)) {
        x6012 = 1;
      } else {
        x6012 = 0;
      }
      number_t x6015 = (xs->arr[4]);
      index_t x6013;
      if ((i) == (4)) {
        x6013 = 1;
      } else {
        x6013 = 0;
      }
      number_t x5756 = (x5930) * (x5931);
      number_t x5754 = ((x5928) * (x5931)) + ((x5930) * (x5929));
      number_t x5757 = (x6014) - (x6015);
      index_t x5755 = (x6012) - (x6013);
      number_t x5672 = (x5768) * (x5769);
      number_t x5670 = ((x5766) * (x5769)) + ((x5768) * (x5767));
      number_t x5673 = (x5756) * (x5757);
      number_t x5671 = ((x5754) * (x5757)) + ((x5756) * (x5755));
      number_t x5966 = (xs->arr[2]);
      index_t x5964;
      if ((i) == (2)) {
        x5964 = 1;
      } else {
        x5964 = 0;
      }
      number_t x5967 = (1) / (x5515);
      number_t x5965 = (-(x5611)) / ((x5515) * (x5515));
      index_t j00 = (11) + (x5481);
      number_t x6050 = (xs->arr[j00]);
      index_t x6048;
      if ((i) == (j00)) {
        x6048 = 1;
      } else {
        x6048 = 0;
      }
      number_t x6051 = (xs->arr[3]);
      index_t x6049;
      if ((i) == (3)) {
        x6049 = 1;
      } else {
        x6049 = 0;
      }
      number_t x5792 = (x5966) * (x5967);
      number_t x5790 = ((x5964) * (x5967)) + ((x5966) * (x5965));
      number_t x5793 = (x6050) - (x6051);
      index_t x5791 = (x6048) - (x6049);
      number_t x5954 = (xs->arr[0]);
      index_t x5952;
      if ((i) == (0)) {
        x5952 = 1;
      } else {
        x5952 = 0;
      }
      number_t x5955 = (1) / (x5515);
      number_t x5953 = (-(x5611)) / ((x5515) * (x5515));
      index_t x5895 = (11) + (x5481);
      index_t j100 = (2) + (x5895);
      number_t x6038 = (xs->arr[j100]);
      index_t x6036;
      if ((i) == (j100)) {
        x6036 = 1;
      } else {
        x6036 = 0;
      }
      number_t x6039 = (xs->arr[5]);
      index_t x6037;
      if ((i) == (5)) {
        x6037 = 1;
      } else {
        x6037 = 0;
      }
      number_t x5780 = (x5954) * (x5955);
      number_t x5778 = ((x5952) * (x5955)) + ((x5954) * (x5953));
      number_t x5781 = (x6038) - (x6039);
      index_t x5779 = (x6036) - (x6037);
      number_t x5684 = (x5792) * (x5793);
      number_t x5682 = ((x5790) * (x5793)) + ((x5792) * (x5791));
      number_t x5685 = (x5780) * (x5781);
      number_t x5683 = ((x5778) * (x5781)) + ((x5780) * (x5779));
      number_t x5990 = (xs->arr[0]);
      index_t x5988;
      if ((i) == (0)) {
        x5988 = 1;
      } else {
        x5988 = 0;
      }
      number_t x5991 = (1) / (x5515);
      number_t x5989 = (-(x5611)) / ((x5515) * (x5515));
      index_t x5907 = (11) + (x5481);
      index_t j01 = (1) + (x5907);
      number_t x6074 = (xs->arr[j01]);
      index_t x6072;
      if ((i) == (j01)) {
        x6072 = 1;
      } else {
        x6072 = 0;
      }
      number_t x6075 = (xs->arr[4]);
      index_t x6073;
      if ((i) == (4)) {
        x6073 = 1;
      } else {
        x6073 = 0;
      }
      number_t x5816 = (x5990) * (x5991);
      number_t x5814 = ((x5988) * (x5991)) + ((x5990) * (x5989));
      number_t x5817 = (x6074) - (x6075);
      index_t x5815 = (x6072) - (x6073);
      number_t x5978 = (xs->arr[1]);
      index_t x5976;
      if ((i) == (1)) {
        x5976 = 1;
      } else {
        x5976 = 0;
      }
      number_t x5979 = (1) / (x5515);
      number_t x5977 = (-(x5611)) / ((x5515) * (x5515));
      index_t j101 = (11) + (x5481);
      number_t x6062 = (xs->arr[j101]);
      index_t x6060;
      if ((i) == (j101)) {
        x6060 = 1;
      } else {
        x6060 = 0;
      }
      number_t x6063 = (xs->arr[3]);
      index_t x6061;
      if ((i) == (3)) {
        x6061 = 1;
      } else {
        x6061 = 0;
      }
      number_t x5804 = (x5978) * (x5979);
      number_t x5802 = ((x5976) * (x5979)) + ((x5978) * (x5977));
      number_t x5805 = (x6062) - (x6063);
      index_t x5803 = (x6060) - (x6061);
      number_t x5696 = (x5816) * (x5817);
      number_t x5694 = ((x5814) * (x5817)) + ((x5816) * (x5815));
      number_t x5697 = (x5804) * (x5805);
      number_t x5695 = ((x5802) * (x5805)) + ((x5804) * (x5803));
      tuple_number_t_number_t x6232 = (tuple_number_t_number_t){._1=(x5672) - (x5673), ._2=(x5670) - (x5671)};
      tuple_number_t_number_t x6233 = (tuple_number_t_number_t){._1=(x5684) - (x5685), ._2=(x5682) - (x5683)};
      tuple_number_t_number_t x6234 = (tuple_number_t_number_t){._1=(x5696) - (x5697), ._2=(x5694) - (x5695)};
      array_tuple_number_t_number_t w_cross_X = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);w_cross_X->length=3;w_cross_X->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      w_cross_X->arr[0] = x6232;
      w_cross_X->arr[1] = x6233;
      w_cross_X->arr[2] = x6234;
      number_t x6098 = (xs->arr[0]);
      index_t x6096;
      if ((i) == (0)) {
        x6096 = 1;
      } else {
        x6096 = 0;
      }
      number_t x6099 = (1) / (x5515);
      number_t x6097 = (-(x5611)) / ((x5515) * (x5515));
      index_t x6123 = (11) + (x5481);
      index_t j000 = (0) + (x6123);
      index_t j1 = (0) + (3);
      number_t x6170 = (xs->arr[j000]);
      index_t x6168;
      if ((i) == (j000)) {
        x6168 = 1;
      } else {
        x6168 = 0;
      }
      number_t x6171 = (xs->arr[j1]);
      index_t x6169;
      if ((i) == (j1)) {
        x6169 = 1;
      } else {
        x6169 = 0;
      }
      number_t x6182 = (x6098) * (x6099);
      number_t x6180 = ((x6096) * (x6099)) + ((x6098) * (x6097));
      number_t x6183 = (x6170) - (x6171);
      index_t x6181 = (x6168) - (x6169);
      number_t x6195 = (x6182) * (x6183);
      number_t x6193 = ((x6180) * (x6183)) + ((x6182) * (x6181));
      number_t x60980 = (xs->arr[1]);
      index_t x60960;
      if ((i) == (1)) {
        x60960 = 1;
      } else {
        x60960 = 0;
      }
      number_t x60990 = (1) / (x5515);
      number_t x60970 = (-(x5611)) / ((x5515) * (x5515));
      index_t x61230 = (11) + (x5481);
      index_t j010 = (1) + (x61230);
      index_t j11 = (1) + (3);
      number_t x61700 = (xs->arr[j010]);
      index_t x61680;
      if ((i) == (j010)) {
        x61680 = 1;
      } else {
        x61680 = 0;
      }
      number_t x61710 = (xs->arr[j11]);
      index_t x61690;
      if ((i) == (j11)) {
        x61690 = 1;
      } else {
        x61690 = 0;
      }
      number_t x61820 = (x60980) * (x60990);
      number_t x61800 = ((x60960) * (x60990)) + ((x60980) * (x60970));
      number_t x61830 = (x61700) - (x61710);
      index_t x61810 = (x61680) - (x61690);
      number_t x61940 = (0) + (x6195);
      number_t x61920 = (0) + (x6193);
      number_t x61950 = (x61820) * (x61830);
      number_t x61930 = ((x61800) * (x61830)) + ((x61820) * (x61810));
      number_t x60981 = (xs->arr[2]);
      index_t x60961;
      if ((i) == (2)) {
        x60961 = 1;
      } else {
        x60961 = 0;
      }
      number_t x60991 = (1) / (x5515);
      number_t x60971 = (-(x5611)) / ((x5515) * (x5515));
      index_t x61231 = (11) + (x5481);
      index_t j0000 = (2) + (x61231);
      index_t j12 = (2) + (3);
      number_t x61701 = (xs->arr[j0000]);
      index_t x61681;
      if ((i) == (j0000)) {
        x61681 = 1;
      } else {
        x61681 = 0;
      }
      number_t x61711 = (xs->arr[j12]);
      index_t x61691;
      if ((i) == (j12)) {
        x61691 = 1;
      } else {
        x61691 = 0;
      }
      number_t x61821 = (x60981) * (x60991);
      number_t x61801 = ((x60961) * (x60991)) + ((x60981) * (x60971));
      number_t x61831 = (x61701) - (x61711);
      index_t x61811 = (x61681) - (x61691);
      number_t x61941 = (x61940) + (x61950);
      number_t x61921 = (x61920) + (x61930);
      number_t x61951 = (x61821) * (x61831);
      number_t x61931 = ((x61801) * (x61831)) + ((x61821) * (x61811));
      number_t x5855 = cos(x5515);
      number_t x5853 = (((x56341) + (x56351)) * (((1) / (x5515)) * (0.5))) * (-(sin(x5515)));
      number_t x5744 = (x61941) + (x61951);
      number_t x5742 = (x61921) + (x61931);
      number_t x5745 = (1) - (x5855);
      number_t x5743 = -(x5853);
      array_tuple_number_t_number_t x6236 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6236->length=3;x6236->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      for(int x5843 = 0; x5843 < x6236->length; x5843++){
        index_t x5919 = (11) + (x5481);
        index_t j = (x5843) + (x5919);
        index_t j0100 = (x5843) + (3);
        number_t x6086 = (xs->arr[j]);
        index_t x6084;
        if ((i) == (j)) {
          x6084 = 1;
        } else {
          x6084 = 0;
        }
        number_t x6087 = (xs->arr[j0100]);
        index_t x6085;
        if ((i) == (j0100)) {
          x6085 = 1;
        } else {
          x6085 = 0;
        }
        number_t x6110 = (x6086) - (x6087);
        index_t x6108 = (x6084) - (x6085);
        number_t x6111 = cos(x5515);
        number_t x6109 = (((x56341) + (x56351)) * (((1) / (x5515)) * (0.5))) * (-(sin(x5515)));
        tuple_number_t_number_t xi0 = (w_cross_X->arr[x5843]);
        number_t x6146 = (xi0)._1;
        number_t x6144 = (xi0)._2;
        number_t x6147 = sin(x5515);
        number_t x6145 = (((x56341) + (x56351)) * (((1) / (x5515)) * (0.5))) * (cos(x5515));
        number_t x6158 = (x6110) * (x6111);
        number_t x6156 = ((x6108) * (x6111)) + ((x6110) * (x6109));
        number_t x6159 = (x6146) * (x6147);
        number_t x6157 = ((x6144) * (x6147)) + ((x6146) * (x6145));
        number_t x6206 = (xs->arr[x5843]);
        index_t x6204;
        if ((i) == (x5843)) {
          x6204 = 1;
        } else {
          x6204 = 0;
        }
        number_t x6207 = (1) / (x5515);
        number_t x6205 = (-(x5611)) / ((x5515) * (x5515));
        number_t x6218 = (x6206) * (x6207);
        number_t x6216 = ((x6204) * (x6207)) + ((x6206) * (x6205));
        number_t x6219 = (x5744) * (x5745);
        number_t x6217 = ((x5742) * (x5745)) + ((x5744) * (x5743));
        number_t x6230 = (x6158) + (x6159);
        number_t x6228 = (x6156) + (x6157);
        number_t x6231 = (x6218) * (x6219);
        number_t x6229 = ((x6216) * (x6219)) + ((x6218) * (x6217));
        tuple_number_t_number_t x6235 = (tuple_number_t_number_t){._1=(x6230) + (x6231), ._2=(x6228) + (x6229)};
        x6236->arr[x5843] = x6235;
        
      }
      array_tuple_number_t_number_t Xcam = x6236;
      tuple_number_t_number_t x5501 = (Xcam->arr[2]);
      number_t x5505 = (x5501)._1;
      number_t x5503 = (x5501)._2;
      tuple_number_t_number_t xi = (Xcam->arr[0]);
      number_t x5648 = (xi)._1;
      number_t x5646 = (xi)._2;
      number_t x5649 = (1) / (x5505);
      number_t x5647 = (-(x5503)) / ((x5505) * (x5505));
      number_t x5732 = (x5648) * (x5649);
      number_t x5730 = ((x5646) * (x5649)) + ((x5648) * (x5647));
      number_t x5733 = (x5648) * (x5649);
      number_t x5731 = ((x5646) * (x5649)) + ((x5648) * (x5647));
      number_t x5841 = (x5732) * (x5733);
      number_t x5839 = ((x5730) * (x5733)) + ((x5732) * (x5731));
      tuple_number_t_number_t xi0 = (Xcam->arr[1]);
      number_t x56480 = (xi0)._1;
      number_t x56460 = (xi0)._2;
      number_t x56490 = (1) / (x5505);
      number_t x56470 = (-(x5503)) / ((x5505) * (x5505));
      number_t x57320 = (x56480) * (x56490);
      number_t x57300 = ((x56460) * (x56490)) + ((x56480) * (x56470));
      number_t x57330 = (x56480) * (x56490);
      number_t x57310 = ((x56460) * (x56490)) + ((x56480) * (x56470));
      number_t x58400 = (0) + (x5841);
      number_t x58380 = (0) + (x5839);
      number_t x58410 = (x57320) * (x57330);
      number_t x58390 = ((x57300) * (x57330)) + ((x57320) * (x57310));
      number_t x5600 = (xs->arr[9]);
      index_t x5598;
      if ((i) == (9)) {
        x5598 = 1;
      } else {
        x5598 = 0;
      }
      number_t x5601 = (x58400) + (x58410);
      number_t x5599 = (x58380) + (x58390);
      number_t x5577 = (x5600) * (x5601);
      number_t x5575 = ((x5598) * (x5601)) + ((x5600) * (x5599));
      number_t x5588 = (xs->arr[10]);
      index_t x5586;
      if ((i) == (10)) {
        x5586 = 1;
      } else {
        x5586 = 0;
      }
      number_t x5589 = (x58400) + (x58410);
      number_t x5587 = (x58380) + (x58390);
      number_t x5564 = (x5588) * (x5589);
      number_t x5562 = ((x5586) * (x5589)) + ((x5588) * (x5587));
      number_t x5565 = (x58400) + (x58410);
      number_t x5563 = (x58380) + (x58390);
      number_t x5546 = (1) + (x5577);
      number_t x5547 = (x5564) * (x5565);
      number_t x5545 = ((x5562) * (x5565)) + ((x5564) * (x5563));
      array_tuple_number_t_number_t x6238 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6238->length=2;x6238->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 2);
      for(int x5553 = 0; x5553 < x6238->length; x5553++){
        tuple_number_t_number_t xi1 = (Xcam->arr[x5553]);
        number_t x5720 = (xi1)._1;
        number_t x5718 = (xi1)._2;
        number_t x5721 = (1) / (x5505);
        number_t x5719 = (-(x5503)) / ((x5505) * (x5505));
        number_t x5828 = (x5720) * (x5721);
        number_t x5826 = ((x5718) * (x5721)) + ((x5720) * (x5719));
        number_t x5829 = (x5546) + (x5547);
        number_t x5827 = (x5575) + (x5545);
        tuple_number_t_number_t x6237 = (tuple_number_t_number_t){._1=(x5828) * (x5829), ._2=((x5826) * (x5829)) + ((x5828) * (x5827))};
        x6238->arr[x5553] = x6237;
        
      }
      array_tuple_number_t_number_t distorted = x6238;
      array_tuple_number_t_number_t m = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);m->length=2;m->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 2);
      for(int x5511 = 0; x5511 < m->length; x5511++){
        index_t j0100 = (x5511) + (7);
        tuple_number_t_number_t xi1 = (distorted->arr[x5511]);
        number_t x5660 = (xi1)._1;
        number_t x5658 = (xi1)._2;
        number_t x5661 = (xs->arr[6]);
        index_t x5659;
        if ((i) == (6)) {
          x5659 = 1;
        } else {
          x5659 = 0;
        }
        number_t x5708 = (xs->arr[j0100]);
        index_t x5706;
        if ((i) == (j0100)) {
          x5706 = 1;
        } else {
          x5706 = 0;
        }
        number_t x5709 = (x5660) * (x5661);
        number_t x5707 = ((x5658) * (x5661)) + ((x5660) * (x5659));
        tuple_number_t_number_t x6239 = (tuple_number_t_number_t){._1=(x5708) + (x5709), ._2=(x5706) + (x5707)};
        m->arr[x5511] = x6239;
        
      }
      array_number_t x6240 = (array_number_t)storage_alloc(sizeof(int) * 2);x6240->length=(m)->length;x6240->arr = (number_t*)storage_alloc(sizeof(number_t) * (m)->length);
      for(int i00 = 0; i00 < x6240->length; i00++){
        tuple_number_t_number_t s = (m->arr[i00]);
        x6240->arr[i00] = (s)._2;
        
      }
      x6241->arr[i0] = x6240;
      
    }
    x6242->arr[i] = x6241;
    
  }
  return x6242;
}
