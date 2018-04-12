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
