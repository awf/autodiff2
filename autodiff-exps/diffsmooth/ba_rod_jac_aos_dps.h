#pragma once

#include "fsharp.h"
#include <stdio.h>
#include <math.h>

array_array_array_number_t ba_rod_jac_dps(storage_t st, array_number_t xs, index_t n) {
  number_t x1353 = (xs->arr[0]);
  number_t x1355 = (x1353) * (x1353);
  number_t x1356 = (xs->arr[1]);
  number_t x1358 = (x1356) * (x1356);
  number_t x1359 = (xs->arr[2]);
  number_t x1361 = (x1355) + (x1358);
  number_t x1362 = (x1359) * (x1359);
  number_t x1363 = (x1361) + (x1362);
  number_t x1364 = sqrt(x1363);
  number_t x1366 = (1) / (x1364);
  number_t x1367 = (x1356) * (x1366);
  number_t x1370 = (x1359) * (x1366);
  number_t x1376 = (x1353) * (x1366);
  number_t x1392 = cos(x1364);
  number_t x1393 = (1) - (x1392);
  number_t x1395 = sin(x1364);
  index_t x1397 = (xs)->length;
  number_t x1422 = (x1366) * (0.5);
  number_t x1427 = (x1364) * (x1364);
  number_t x1501 = -(x1395);
  array_array_array_number_t x1652 = (array_array_array_number_t)st;
  for(int i = 0; i < x1652->length; i++){
    index_t x1398 = (i) == (0);
    index_t x1399;
    if (x1398) {
      x1399 = 1;
    } else {
      x1399 = 0;
    }
    number_t x1402 = (x1399) * (x1353);
    number_t x1403 = (x1353) * (x1399);
    number_t x1404 = (x1402) + (x1403);
    index_t x1405 = (i) == (1);
    index_t x1406;
    if (x1405) {
      x1406 = 1;
    } else {
      x1406 = 0;
    }
    number_t x1409 = (x1406) * (x1356);
    number_t x1410 = (x1356) * (x1406);
    number_t x1411 = (x1409) + (x1410);
    index_t x1412 = (i) == (2);
    index_t x1413;
    if (x1412) {
      x1413 = 1;
    } else {
      x1413 = 0;
    }
    number_t x1416 = (x1404) + (x1411);
    number_t x1417 = (x1413) * (x1359);
    number_t x1418 = (x1359) * (x1413);
    number_t x1419 = (x1417) + (x1418);
    number_t x1420 = (x1416) + (x1419);
    number_t x1423 = (x1420) * (x1422);
    number_t x1426 = -(x1423);
    number_t x1428 = (x1426) / (x1427);
    number_t x1429 = (x1406) * (x1366);
    number_t x1430 = (x1356) * (x1428);
    number_t x1431 = (x1429) + (x1430);
    number_t x1437 = (x1413) * (x1366);
    number_t x1438 = (x1359) * (x1428);
    number_t x1439 = (x1437) + (x1438);
    number_t x1453 = (x1399) * (x1366);
    number_t x1454 = (x1353) * (x1428);
    number_t x1455 = (x1453) + (x1454);
    number_t x1502 = (x1423) * (x1501);
    number_t x1503 = -(x1502);
    number_t x1516 = (x1423) * (x1392);
    array_array_number_t x1651 = x1652->arr[i];
    for(int i0 = 0; i0 < x1651->length; i0++){
      index_t x1520 = (3) * (i0);
      index_t x1521 = (11) + (x1520);
      index_t x1522 = (2) + (x1521);
      number_t x1523 = (xs->arr[x1522]);
      index_t x1524 = (i) == (x1522);
      index_t x1525;
      if (x1524) {
        x1525 = 1;
      } else {
        x1525 = 0;
      }
      index_t x1527 = (1) + (x1521);
      number_t x1528 = (xs->arr[x1527]);
      index_t x1529 = (i) == (x1527);
      index_t x1530;
      if (x1529) {
        x1530 = 1;
      } else {
        x1530 = 0;
      }
      number_t x1531 = (x1367) * (x1523);
      number_t x1532 = (x1431) * (x1523);
      number_t x1533 = (x1367) * (x1525);
      number_t x1534 = (x1532) + (x1533);
      number_t x1535 = (x1370) * (x1528);
      number_t x1536 = (x1439) * (x1528);
      number_t x1537 = (x1370) * (x1530);
      number_t x1538 = (x1536) + (x1537);
      number_t x1540 = (xs->arr[x1521]);
      index_t x1541 = (i) == (x1521);
      index_t x1542;
      if (x1541) {
        x1542 = 1;
      } else {
        x1542 = 0;
      }
      number_t x1548 = (x1370) * (x1540);
      number_t x1549 = (x1439) * (x1540);
      number_t x1550 = (x1370) * (x1542);
      number_t x1551 = (x1549) + (x1550);
      number_t x1552 = (x1376) * (x1523);
      number_t x1553 = (x1455) * (x1523);
      number_t x1554 = (x1376) * (x1525);
      number_t x1555 = (x1553) + (x1554);
      number_t x1565 = (x1376) * (x1528);
      number_t x1566 = (x1455) * (x1528);
      number_t x1567 = (x1376) * (x1530);
      number_t x1568 = (x1566) + (x1567);
      number_t x1569 = (x1367) * (x1540);
      number_t x1570 = (x1431) * (x1540);
      number_t x1571 = (x1367) * (x1542);
      number_t x1572 = (x1570) + (x1571);
      number_t x1573 = (x1531) - (x1535);
      number_t x1574 = (x1534) - (x1538);
      tuple_number_t_number_t x1575 = (tuple_number_t_number_t){._1=x1573, ._2=x1574};
      number_t x1576 = (x1548) - (x1552);
      number_t x1577 = (x1551) - (x1555);
      tuple_number_t_number_t x1578 = (tuple_number_t_number_t){._1=x1576, ._2=x1577};
      number_t x1579 = (x1565) - (x1569);
      number_t x1580 = (x1568) - (x1572);
      tuple_number_t_number_t x1581 = (tuple_number_t_number_t){._1=x1579, ._2=x1580};
      array_tuple_number_t_number_t x1582 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x1582->length=3;x1582->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      x1582->arr[0] = x1575;
      x1582->arr[1] = x1578;
      x1582->arr[2] = x1581;
      number_t x1587 = (x1376) * (x1540);
      number_t x1588 = (x1455) * (x1540);
      number_t x1589 = (x1376) * (x1542);
      number_t x1590 = (x1588) + (x1589);
      number_t x1596 = (x1367) * (x1528);
      number_t x1597 = (x1431) * (x1528);
      number_t x1598 = (x1367) * (x1530);
      number_t x1599 = (x1597) + (x1598);
      number_t x1605 = (x1587) + (x1596);
      number_t x1606 = (x1590) + (x1599);
      number_t x1607 = (x1370) * (x1523);
      number_t x1608 = (x1439) * (x1523);
      number_t x1609 = (x1370) * (x1525);
      number_t x1610 = (x1608) + (x1609);
      number_t x1611 = (x1605) + (x1607);
      number_t x1612 = (x1606) + (x1610);
      number_t x1614 = (x1611) * (x1393);
      number_t x1615 = (x1612) * (x1393);
      number_t x1616 = (x1611) * (x1503);
      number_t x1617 = (x1615) + (x1616);
      array_number_t x1650 = x1651->arr[i0];
      for(int i00 = 0; i00 < x1650->length; i00++){
        index_t x1618 = (i00) + (x1521);
        number_t x1619 = (xs->arr[x1618]);
        index_t x1620 = (i) == (x1618);
        index_t x1621;
        if (x1620) {
          x1621 = 1;
        } else {
          x1621 = 0;
        }
        tuple_number_t_number_t x1622 = (x1582->arr[i00]);
        number_t x1623 = (x1622)._1;
        number_t x1624 = (x1622)._2;
        number_t x1625 = (x1619) * (x1392);
        number_t x1626 = (x1621) * (x1392);
        number_t x1627 = (x1619) * (x1502);
        number_t x1628 = (x1626) + (x1627);
        number_t x1629 = (x1623) * (x1395);
        number_t x1630 = (x1624) * (x1395);
        number_t x1631 = (x1623) * (x1516);
        number_t x1632 = (x1630) + (x1631);
        number_t x1633 = (xs->arr[i00]);
        index_t x1634 = (i) == (i00);
        index_t x1635;
        if (x1634) {
          x1635 = 1;
        } else {
          x1635 = 0;
        }
        number_t x1636 = (x1633) * (x1366);
        number_t x1637 = (x1635) * (x1366);
        number_t x1638 = (x1633) * (x1428);
        number_t x1639 = (x1637) + (x1638);
        number_t x1640 = (x1625) + (x1629);
        number_t x1641 = (x1628) + (x1632);
        number_t x1642 = (x1636) * (x1614);
        number_t x1643 = (x1639) * (x1614);
        number_t x1644 = (x1636) * (x1617);
        number_t x1645 = (x1643) + (x1644);
        number_t x1646 = (x1640) + (x1642);
        number_t x1647 = (x1641) + (x1645);
        tuple_number_t_number_t x1648 = (tuple_number_t_number_t){._1=x1646, ._2=x1647};
        number_t x1649 = (x1648)._2;
        x1650->arr[i00] = x1649;
        
      }
    }
  }
  return x1652;
}

array_array_array_number_t ba_proj_jac_dps(storage_t st, array_number_t xs, index_t n) {
  number_t x6232 = (xs->arr[0]);
  number_t x6234 = (x6232) * (x6232);
  number_t x6235 = (xs->arr[1]);
  number_t x6237 = (x6235) * (x6235);
  number_t x6238 = (xs->arr[2]);
  number_t x6240 = (x6234) + (x6237);
  number_t x6241 = (x6238) * (x6238);
  number_t x6242 = (x6240) + (x6241);
  number_t x6243 = sqrt(x6242);
  number_t x6245 = (1) / (x6243);
  number_t x6246 = (xs->arr[5]);
  number_t x6247 = (x6235) * (x6245);
  number_t x6250 = (xs->arr[4]);
  number_t x6251 = (x6238) * (x6245);
  number_t x6254 = (xs->arr[3]);
  number_t x6259 = (x6232) * (x6245);
  number_t x6280 = cos(x6243);
  number_t x6281 = (1) - (x6280);
  number_t x6282 = (xs->arr[9]);
  number_t x6283 = (xs->arr[10]);
  number_t x6284 = (xs->arr[6]);
  index_t x6285 = (xs)->length;
  number_t x6310 = (x6245) * (0.5);
  number_t x6315 = (x6243) * (x6243);
  number_t x6406 = sin(x6243);
  number_t x6407 = -(x6406);
  array_array_array_number_t x6689 = (array_array_array_number_t)st;
  for(int i = 0; i < x6689->length; i++){
    index_t x6286 = (i) == (0);
    index_t x6287;
    if (x6286) {
      x6287 = 1;
    } else {
      x6287 = 0;
    }
    number_t x6290 = (x6287) * (x6232);
    number_t x6291 = (x6232) * (x6287);
    number_t x6292 = (x6290) + (x6291);
    index_t x6293 = (i) == (1);
    index_t x6294;
    if (x6293) {
      x6294 = 1;
    } else {
      x6294 = 0;
    }
    number_t x6297 = (x6294) * (x6235);
    number_t x6298 = (x6235) * (x6294);
    number_t x6299 = (x6297) + (x6298);
    index_t x6300 = (i) == (2);
    index_t x6301;
    if (x6300) {
      x6301 = 1;
    } else {
      x6301 = 0;
    }
    number_t x6304 = (x6292) + (x6299);
    number_t x6305 = (x6301) * (x6238);
    number_t x6306 = (x6238) * (x6301);
    number_t x6307 = (x6305) + (x6306);
    number_t x6308 = (x6304) + (x6307);
    number_t x6311 = (x6308) * (x6310);
    number_t x6314 = -(x6311);
    number_t x6316 = (x6314) / (x6315);
    index_t x6317 = (i) == (5);
    index_t x6318;
    if (x6317) {
      x6318 = 1;
    } else {
      x6318 = 0;
    }
    number_t x6319 = (x6294) * (x6245);
    number_t x6320 = (x6235) * (x6316);
    number_t x6321 = (x6319) + (x6320);
    index_t x6327 = (i) == (4);
    index_t x6328;
    if (x6327) {
      x6328 = 1;
    } else {
      x6328 = 0;
    }
    number_t x6329 = (x6301) * (x6245);
    number_t x6330 = (x6238) * (x6316);
    number_t x6331 = (x6329) + (x6330);
    index_t x6337 = (i) == (3);
    index_t x6338;
    if (x6337) {
      x6338 = 1;
    } else {
      x6338 = 0;
    }
    number_t x6349 = (x6287) * (x6245);
    number_t x6350 = (x6232) * (x6316);
    number_t x6351 = (x6349) + (x6350);
    number_t x6408 = (x6311) * (x6407);
    number_t x6409 = -(x6408);
    index_t x6410 = (i) == (9);
    index_t x6411;
    if (x6410) {
      x6411 = 1;
    } else {
      x6411 = 0;
    }
    index_t x6412 = (i) == (10);
    index_t x6413;
    if (x6412) {
      x6413 = 1;
    } else {
      x6413 = 0;
    }
    index_t x6414 = (i) == (6);
    index_t x6415;
    if (x6414) {
      x6415 = 1;
    } else {
      x6415 = 0;
    }
    number_t x6542 = (x6311) * (x6280);
    array_array_number_t x6688 = (array_array_number_t)x6689->arr[i];
    for(int i0 = 0; i0 < x6688->length; i0++){
      index_t x6416 = (3) * (i0);
      index_t x6417 = (11) + (x6416);
      index_t x6418 = (2) + (x6417);
      number_t x6419 = (xs->arr[x6418]);
      index_t x6420 = (i) == (x6418);
      index_t x6421;
      if (x6420) {
        x6421 = 1;
      } else {
        x6421 = 0;
      }
      number_t x6422 = (x6419) - (x6246);
      index_t x6423 = (x6421) - (x6318);
      index_t x6425 = (1) + (x6417);
      number_t x6426 = (xs->arr[x6425]);
      index_t x6427 = (i) == (x6425);
      index_t x6428;
      if (x6427) {
        x6428 = 1;
      } else {
        x6428 = 0;
      }
      number_t x6429 = (x6426) - (x6250);
      index_t x6430 = (x6428) - (x6328);
      number_t x6431 = (x6247) * (x6422);
      number_t x6432 = (x6321) * (x6422);
      number_t x6433 = (x6247) * (x6423);
      number_t x6434 = (x6432) + (x6433);
      number_t x6435 = (x6251) * (x6429);
      number_t x6436 = (x6331) * (x6429);
      number_t x6437 = (x6251) * (x6430);
      number_t x6438 = (x6436) + (x6437);
      number_t x6440 = (xs->arr[x6417]);
      index_t x6441 = (i) == (x6417);
      index_t x6442;
      if (x6441) {
        x6442 = 1;
      } else {
        x6442 = 0;
      }
      number_t x6443 = (x6440) - (x6254);
      index_t x6444 = (x6442) - (x6338);
      number_t x6452 = (x6251) * (x6443);
      number_t x6453 = (x6331) * (x6443);
      number_t x6454 = (x6251) * (x6444);
      number_t x6455 = (x6453) + (x6454);
      number_t x6456 = (x6259) * (x6422);
      number_t x6457 = (x6351) * (x6422);
      number_t x6458 = (x6259) * (x6423);
      number_t x6459 = (x6457) + (x6458);
      number_t x6473 = (x6259) * (x6429);
      number_t x6474 = (x6351) * (x6429);
      number_t x6475 = (x6259) * (x6430);
      number_t x6476 = (x6474) + (x6475);
      number_t x6477 = (x6247) * (x6443);
      number_t x6478 = (x6321) * (x6443);
      number_t x6479 = (x6247) * (x6444);
      number_t x6480 = (x6478) + (x6479);
      number_t x6481 = (x6431) - (x6435);
      number_t x6482 = (x6434) - (x6438);
      tuple_number_t_number_t x6483 = (tuple_number_t_number_t){._1=x6481, ._2=x6482};
      number_t x6484 = (x6452) - (x6456);
      number_t x6485 = (x6455) - (x6459);
      tuple_number_t_number_t x6486 = (tuple_number_t_number_t){._1=x6484, ._2=x6485};
      number_t x6487 = (x6473) - (x6477);
      number_t x6488 = (x6476) - (x6480);
      tuple_number_t_number_t x6489 = (tuple_number_t_number_t){._1=x6487, ._2=x6488};
      array_tuple_number_t_number_t x6490 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6490->length=3;x6490->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      x6490->arr[0] = x6483;
      x6490->arr[1] = x6486;
      x6490->arr[2] = x6489;
      number_t x6497 = (x6259) * (x6443);
      number_t x6498 = (x6351) * (x6443);
      number_t x6499 = (x6259) * (x6444);
      number_t x6500 = (x6498) + (x6499);
      number_t x6508 = (x6247) * (x6429);
      number_t x6509 = (x6321) * (x6429);
      number_t x6510 = (x6247) * (x6430);
      number_t x6511 = (x6509) + (x6510);
      number_t x6519 = (x6497) + (x6508);
      number_t x6520 = (x6500) + (x6511);
      number_t x6521 = (x6251) * (x6422);
      number_t x6522 = (x6331) * (x6422);
      number_t x6523 = (x6251) * (x6423);
      number_t x6524 = (x6522) + (x6523);
      number_t x6525 = (x6519) + (x6521);
      number_t x6526 = (x6520) + (x6524);
      number_t x6547 = (x6525) * (x6281);
      number_t x6548 = (x6526) * (x6281);
      number_t x6549 = (x6525) * (x6409);
      number_t x6550 = (x6548) + (x6549);
      array_tuple_number_t_number_t x6588 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6588->length=3;x6588->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      for(int x5843 = 0; x5843 < x6588->length; x5843++){
        index_t x6551 = (x5843) + (x6417);
        index_t x6552 = (x5843) + (3);
        number_t x6553 = (xs->arr[x6551]);
        index_t x6554 = (i) == (x6551);
        index_t x6555;
        if (x6554) {
          x6555 = 1;
        } else {
          x6555 = 0;
        }
        number_t x6556 = (xs->arr[x6552]);
        index_t x6557 = (i) == (x6552);
        index_t x6558;
        if (x6557) {
          x6558 = 1;
        } else {
          x6558 = 0;
        }
        number_t x6559 = (x6553) - (x6556);
        index_t x6560 = (x6555) - (x6558);
        tuple_number_t_number_t x6561 = (x6490->arr[x5843]);
        number_t x6562 = (x6561)._1;
        number_t x6563 = (x6561)._2;
        number_t x6564 = (x6559) * (x6280);
        number_t x6565 = (x6560) * (x6280);
        number_t x6566 = (x6559) * (x6408);
        number_t x6567 = (x6565) + (x6566);
        number_t x6568 = (x6562) * (x6406);
        number_t x6569 = (x6563) * (x6406);
        number_t x6570 = (x6562) * (x6542);
        number_t x6571 = (x6569) + (x6570);
        number_t x6572 = (xs->arr[x5843]);
        index_t x6573 = (i) == (x5843);
        index_t x6574;
        if (x6573) {
          x6574 = 1;
        } else {
          x6574 = 0;
        }
        number_t x6575 = (x6572) * (x6245);
        number_t x6576 = (x6574) * (x6245);
        number_t x6577 = (x6572) * (x6316);
        number_t x6578 = (x6576) + (x6577);
        number_t x6579 = (x6564) + (x6568);
        number_t x6580 = (x6567) + (x6571);
        number_t x6581 = (x6575) * (x6547);
        number_t x6582 = (x6578) * (x6547);
        number_t x6583 = (x6575) * (x6550);
        number_t x6584 = (x6582) + (x6583);
        number_t x6585 = (x6579) + (x6581);
        number_t x6586 = (x6580) + (x6584);
        tuple_number_t_number_t x6587 = (tuple_number_t_number_t){._1=x6585, ._2=x6586};
        x6588->arr[x5843] = x6587;
        
      }
      array_tuple_number_t_number_t x6589 = x6588;
      tuple_number_t_number_t x6590 = (x6589->arr[2]);
      number_t x6591 = (x6590)._1;
      number_t x6592 = (x6590)._2;
      tuple_number_t_number_t x6593 = (x6589->arr[0]);
      number_t x6594 = (x6593)._1;
      number_t x6595 = (x6593)._2;
      number_t x6596 = (1) / (x6591);
      number_t x6597 = -(x6592);
      number_t x6598 = (x6591) * (x6591);
      number_t x6599 = (x6597) / (x6598);
      number_t x6600 = (x6594) * (x6596);
      number_t x6601 = (x6595) * (x6596);
      number_t x6602 = (x6594) * (x6599);
      number_t x6603 = (x6601) + (x6602);
      number_t x6608 = (x6600) * (x6600);
      number_t x6609 = (x6603) * (x6600);
      number_t x6610 = (x6600) * (x6603);
      number_t x6611 = (x6609) + (x6610);
      tuple_number_t_number_t x6612 = (x6589->arr[1]);
      number_t x6613 = (x6612)._1;
      number_t x6614 = (x6612)._2;
      number_t x6619 = (x6613) * (x6596);
      number_t x6620 = (x6614) * (x6596);
      number_t x6621 = (x6613) * (x6599);
      number_t x6622 = (x6620) + (x6621);
      number_t x6627 = (x6619) * (x6619);
      number_t x6628 = (x6622) * (x6619);
      number_t x6629 = (x6619) * (x6622);
      number_t x6630 = (x6628) + (x6629);
      number_t x6631 = (x6608) + (x6627);
      number_t x6632 = (x6611) + (x6630);
      number_t x6633 = (x6282) * (x6631);
      number_t x6634 = (x6411) * (x6631);
      number_t x6635 = (x6282) * (x6632);
      number_t x6636 = (x6634) + (x6635);
      number_t x6639 = (x6283) * (x6631);
      number_t x6640 = (x6413) * (x6631);
      number_t x6641 = (x6283) * (x6632);
      number_t x6642 = (x6640) + (x6641);
      number_t x6645 = (1) + (x6633);
      number_t x6646 = (x6639) * (x6631);
      number_t x6647 = (x6642) * (x6631);
      number_t x6648 = (x6639) * (x6632);
      number_t x6649 = (x6647) + (x6648);
      number_t x6654 = (x6645) + (x6646);
      number_t x6655 = (x6636) + (x6649);
      array_tuple_number_t_number_t x6669 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6669->length=2;x6669->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 2);
      for(int x5553 = 0; x5553 < x6669->length; x5553++){
        tuple_number_t_number_t x6657 = (x6589->arr[x5553]);
        number_t x6658 = (x6657)._1;
        number_t x6659 = (x6657)._2;
        number_t x6660 = (x6658) * (x6596);
        number_t x6661 = (x6659) * (x6596);
        number_t x6662 = (x6658) * (x6599);
        number_t x6663 = (x6661) + (x6662);
        number_t x6664 = (x6660) * (x6654);
        number_t x6665 = (x6663) * (x6654);
        number_t x6666 = (x6660) * (x6655);
        number_t x6667 = (x6665) + (x6666);
        tuple_number_t_number_t x6668 = (tuple_number_t_number_t){._1=x6664, ._2=x6667};
        x6669->arr[x5553] = x6668;
        
      }
      array_tuple_number_t_number_t x6670 = x6669;
      array_number_t x6687 = x6688->arr[i0];
      for(int i00 = 0; i00 < x6687->length; i00++){
        index_t x6672 = (i00) + (7);
        tuple_number_t_number_t x6673 = (x6670->arr[i00]);
        number_t x6674 = (x6673)._1;
        number_t x6675 = (x6673)._2;
        number_t x6676 = (xs->arr[x6672]);
        index_t x6677 = (i) == (x6672);
        index_t x6678;
        if (x6677) {
          x6678 = 1;
        } else {
          x6678 = 0;
        }
        number_t x6679 = (x6674) * (x6284);
        number_t x6680 = (x6675) * (x6284);
        number_t x6681 = (x6674) * (x6415);
        number_t x6682 = (x6680) + (x6681);
        number_t x6683 = (x6676) + (x6679);
        number_t x6684 = (x6678) + (x6682);
        tuple_number_t_number_t x6685 = (tuple_number_t_number_t){._1=x6683, ._2=x6684};
        number_t x6686 = (x6685)._2;
        x6687->arr[i00] = x6686;
        
      }
      // x6688->arr[i0] = x6687;
      
    }
    // x6689->arr[i] = x6688;
    
  }
  return x6689;
}
