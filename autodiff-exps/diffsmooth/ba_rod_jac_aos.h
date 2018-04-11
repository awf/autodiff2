#pragma once

#include "fsharp.h"
#include <stdio.h>
#include <math.h>


array_array_array_number_t ba_rod_jac(array_number_t xs, index_t n) {
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
  array_array_array_number_t x1652 = (array_array_array_number_t)storage_alloc(sizeof(int) * 2);x1652->length=x1397;x1652->arr = (array_array_number_t*)storage_alloc(sizeof(array_array_number_t) * x1397);
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
    array_array_number_t x1651 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x1651->length=n;x1651->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * n);
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
      array_number_t x1650 = (array_number_t)storage_alloc(sizeof(int) * 2);x1650->length=3;x1650->arr = (number_t*)storage_alloc(sizeof(number_t) * 3);
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
      x1651->arr[i0] = x1650;
      
    }
    x1652->arr[i] = x1651;
    
  }
  return x1652;
}

array_array_array_number_t ba_proj_jac(array_number_t xs, index_t n) {
  number_t x6230 = (xs->arr[0]);
  number_t x6232 = (x6230) * (x6230);
  number_t x6233 = (xs->arr[1]);
  number_t x6235 = (x6233) * (x6233);
  number_t x6236 = (xs->arr[2]);
  number_t x6238 = (x6232) + (x6235);
  number_t x6239 = (x6236) * (x6236);
  number_t x6240 = (x6238) + (x6239);
  number_t x6241 = sqrt(x6240);
  number_t x6243 = (1) / (x6241);
  number_t x6244 = (xs->arr[5]);
  number_t x6245 = (x6233) * (x6243);
  number_t x6248 = (xs->arr[4]);
  number_t x6249 = (x6236) * (x6243);
  number_t x6252 = (xs->arr[3]);
  number_t x6257 = (x6230) * (x6243);
  number_t x6278 = cos(x6241);
  number_t x6279 = (1) - (x6278);
  number_t x6280 = (xs->arr[9]);
  number_t x6281 = (xs->arr[10]);
  number_t x6282 = (xs->arr[6]);
  index_t x6284 = (xs)->length;
  number_t x6309 = (x6243) * (0.5);
  number_t x6314 = (x6241) * (x6241);
  number_t x6405 = sin(x6241);
  number_t x6406 = -(x6405);
  array_array_array_number_t x6679 = (array_array_array_number_t)storage_alloc(sizeof(int) * 2);x6679->length=x6284;x6679->arr = (array_array_number_t*)storage_alloc(sizeof(array_array_number_t) * x6284);
  for(int i = 0; i < x6679->length; i++){
    index_t x6285 = (i) == (0);
    index_t x6286;
    if (x6285) {
      x6286 = 1;
    } else {
      x6286 = 0;
    }
    number_t x6289 = (x6286) * (x6230);
    number_t x6290 = (x6230) * (x6286);
    number_t x6291 = (x6289) + (x6290);
    index_t x6292 = (i) == (1);
    index_t x6293;
    if (x6292) {
      x6293 = 1;
    } else {
      x6293 = 0;
    }
    number_t x6296 = (x6293) * (x6233);
    number_t x6297 = (x6233) * (x6293);
    number_t x6298 = (x6296) + (x6297);
    index_t x6299 = (i) == (2);
    index_t x6300;
    if (x6299) {
      x6300 = 1;
    } else {
      x6300 = 0;
    }
    number_t x6303 = (x6291) + (x6298);
    number_t x6304 = (x6300) * (x6236);
    number_t x6305 = (x6236) * (x6300);
    number_t x6306 = (x6304) + (x6305);
    number_t x6307 = (x6303) + (x6306);
    number_t x6310 = (x6307) * (x6309);
    number_t x6313 = -(x6310);
    number_t x6315 = (x6313) / (x6314);
    index_t x6316 = (i) == (5);
    index_t x6317;
    if (x6316) {
      x6317 = 1;
    } else {
      x6317 = 0;
    }
    number_t x6318 = (x6293) * (x6243);
    number_t x6319 = (x6233) * (x6315);
    number_t x6320 = (x6318) + (x6319);
    index_t x6326 = (i) == (4);
    index_t x6327;
    if (x6326) {
      x6327 = 1;
    } else {
      x6327 = 0;
    }
    number_t x6328 = (x6300) * (x6243);
    number_t x6329 = (x6236) * (x6315);
    number_t x6330 = (x6328) + (x6329);
    index_t x6336 = (i) == (3);
    index_t x6337;
    if (x6336) {
      x6337 = 1;
    } else {
      x6337 = 0;
    }
    number_t x6348 = (x6286) * (x6243);
    number_t x6349 = (x6230) * (x6315);
    number_t x6350 = (x6348) + (x6349);
    number_t x6407 = (x6310) * (x6406);
    number_t x6408 = -(x6407);
    index_t x6409 = (i) == (9);
    index_t x6410;
    if (x6409) {
      x6410 = 1;
    } else {
      x6410 = 0;
    }
    index_t x6411 = (i) == (10);
    index_t x6412;
    if (x6411) {
      x6412 = 1;
    } else {
      x6412 = 0;
    }
    index_t x6413 = (i) == (6);
    index_t x6414;
    if (x6413) {
      x6414 = 1;
    } else {
      x6414 = 0;
    }
    number_t x6543 = (x6310) * (x6278);
    array_array_number_t x6678 = (array_array_number_t)storage_alloc(sizeof(int) * 2);x6678->length=n;x6678->arr = (array_number_t*)storage_alloc(sizeof(array_number_t) * n);
    for(int i0 = 0; i0 < x6678->length; i0++){
      index_t x6417 = (3) * (i0);
      index_t x6418 = (11) + (x6417);
      index_t x6419 = (2) + (x6418);
      number_t x6420 = (xs->arr[x6419]);
      index_t x6421 = (i) == (x6419);
      index_t x6422;
      if (x6421) {
        x6422 = 1;
      } else {
        x6422 = 0;
      }
      number_t x6423 = (x6420) - (x6244);
      index_t x6424 = (x6422) - (x6317);
      index_t x6426 = (1) + (x6418);
      number_t x6427 = (xs->arr[x6426]);
      index_t x6428 = (i) == (x6426);
      index_t x6429;
      if (x6428) {
        x6429 = 1;
      } else {
        x6429 = 0;
      }
      number_t x6430 = (x6427) - (x6248);
      index_t x6431 = (x6429) - (x6327);
      number_t x6432 = (x6245) * (x6423);
      number_t x6433 = (x6320) * (x6423);
      number_t x6434 = (x6245) * (x6424);
      number_t x6435 = (x6433) + (x6434);
      number_t x6436 = (x6249) * (x6430);
      number_t x6437 = (x6330) * (x6430);
      number_t x6438 = (x6249) * (x6431);
      number_t x6439 = (x6437) + (x6438);
      number_t x6441 = (xs->arr[x6418]);
      index_t x6442 = (i) == (x6418);
      index_t x6443;
      if (x6442) {
        x6443 = 1;
      } else {
        x6443 = 0;
      }
      number_t x6444 = (x6441) - (x6252);
      index_t x6445 = (x6443) - (x6337);
      number_t x6453 = (x6249) * (x6444);
      number_t x6454 = (x6330) * (x6444);
      number_t x6455 = (x6249) * (x6445);
      number_t x6456 = (x6454) + (x6455);
      number_t x6457 = (x6257) * (x6423);
      number_t x6458 = (x6350) * (x6423);
      number_t x6459 = (x6257) * (x6424);
      number_t x6460 = (x6458) + (x6459);
      number_t x6474 = (x6257) * (x6430);
      number_t x6475 = (x6350) * (x6430);
      number_t x6476 = (x6257) * (x6431);
      number_t x6477 = (x6475) + (x6476);
      number_t x6478 = (x6245) * (x6444);
      number_t x6479 = (x6320) * (x6444);
      number_t x6480 = (x6245) * (x6445);
      number_t x6481 = (x6479) + (x6480);
      number_t x6482 = (x6432) - (x6436);
      number_t x6483 = (x6435) - (x6439);
      tuple_number_t_number_t x6484 = (tuple_number_t_number_t){._1=x6482, ._2=x6483};
      number_t x6485 = (x6453) - (x6457);
      number_t x6486 = (x6456) - (x6460);
      tuple_number_t_number_t x6487 = (tuple_number_t_number_t){._1=x6485, ._2=x6486};
      number_t x6488 = (x6474) - (x6478);
      number_t x6489 = (x6477) - (x6481);
      tuple_number_t_number_t x6490 = (tuple_number_t_number_t){._1=x6488, ._2=x6489};
      array_tuple_number_t_number_t x6491 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6491->length=3;x6491->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      x6491->arr[0] = x6484;
      x6491->arr[1] = x6487;
      x6491->arr[2] = x6490;
      number_t x6498 = (x6257) * (x6444);
      number_t x6499 = (x6350) * (x6444);
      number_t x6500 = (x6257) * (x6445);
      number_t x6501 = (x6499) + (x6500);
      number_t x6509 = (x6245) * (x6430);
      number_t x6510 = (x6320) * (x6430);
      number_t x6511 = (x6245) * (x6431);
      number_t x6512 = (x6510) + (x6511);
      number_t x6520 = (x6498) + (x6509);
      number_t x6521 = (x6501) + (x6512);
      number_t x6522 = (x6249) * (x6423);
      number_t x6523 = (x6330) * (x6423);
      number_t x6524 = (x6249) * (x6424);
      number_t x6525 = (x6523) + (x6524);
      number_t x6526 = (x6520) + (x6522);
      number_t x6527 = (x6521) + (x6525);
      number_t x6548 = (x6526) * (x6279);
      number_t x6549 = (x6527) * (x6279);
      number_t x6550 = (x6526) * (x6408);
      number_t x6551 = (x6549) + (x6550);
      array_tuple_number_t_number_t x6589 = (array_tuple_number_t_number_t)storage_alloc(sizeof(int) * 2);x6589->length=3;x6589->arr = (tuple_number_t_number_t*)storage_alloc(sizeof(tuple_number_t_number_t) * 3);
      for(int x5793 = 0; x5793 < x6589->length; x5793++){
        index_t x6552 = (x5793) + (x6418);
        index_t x6553 = (x5793) + (3);
        number_t x6554 = (xs->arr[x6552]);
        index_t x6555 = (i) == (x6552);
        index_t x6556;
        if (x6555) {
          x6556 = 1;
        } else {
          x6556 = 0;
        }
        number_t x6557 = (xs->arr[x6553]);
        index_t x6558 = (i) == (x6553);
        index_t x6559;
        if (x6558) {
          x6559 = 1;
        } else {
          x6559 = 0;
        }
        number_t x6560 = (x6554) - (x6557);
        index_t x6561 = (x6556) - (x6559);
        tuple_number_t_number_t x6562 = (x6491->arr[x5793]);
        number_t x6563 = (x6562)._1;
        number_t x6564 = (x6562)._2;
        number_t x6565 = (x6560) * (x6278);
        number_t x6566 = (x6561) * (x6278);
        number_t x6567 = (x6560) * (x6407);
        number_t x6568 = (x6566) + (x6567);
        number_t x6569 = (x6563) * (x6405);
        number_t x6570 = (x6564) * (x6405);
        number_t x6571 = (x6563) * (x6543);
        number_t x6572 = (x6570) + (x6571);
        number_t x6573 = (xs->arr[x5793]);
        index_t x6574 = (i) == (x5793);
        index_t x6575;
        if (x6574) {
          x6575 = 1;
        } else {
          x6575 = 0;
        }
        number_t x6576 = (x6573) * (x6243);
        number_t x6577 = (x6575) * (x6243);
        number_t x6578 = (x6573) * (x6315);
        number_t x6579 = (x6577) + (x6578);
        number_t x6580 = (x6565) + (x6569);
        number_t x6581 = (x6568) + (x6572);
        number_t x6582 = (x6576) * (x6548);
        number_t x6583 = (x6579) * (x6548);
        number_t x6584 = (x6576) * (x6551);
        number_t x6585 = (x6583) + (x6584);
        number_t x6586 = (x6580) + (x6582);
        number_t x6587 = (x6581) + (x6585);
        tuple_number_t_number_t x6588 = (tuple_number_t_number_t){._1=x6586, ._2=x6587};
        x6589->arr[x5793] = x6588;
        
      }
      array_tuple_number_t_number_t x6590 = x6589;
      tuple_number_t_number_t x6591 = (x6590->arr[2]);
      number_t x6592 = (x6591)._1;
      number_t x6593 = (x6591)._2;
      tuple_number_t_number_t x6594 = (x6590->arr[0]);
      number_t x6595 = (x6594)._1;
      number_t x6596 = (x6594)._2;
      number_t x6597 = (1) / (x6592);
      number_t x6598 = -(x6593);
      number_t x6599 = (x6592) * (x6592);
      number_t x6600 = (x6598) / (x6599);
      number_t x6601 = (x6595) * (x6597);
      number_t x6602 = (x6596) * (x6597);
      number_t x6603 = (x6595) * (x6600);
      number_t x6604 = (x6602) + (x6603);
      number_t x6609 = (x6601) * (x6601);
      number_t x6610 = (x6604) * (x6601);
      number_t x6611 = (x6601) * (x6604);
      number_t x6612 = (x6610) + (x6611);
      tuple_number_t_number_t x6613 = (x6590->arr[1]);
      number_t x6614 = (x6613)._1;
      number_t x6615 = (x6613)._2;
      number_t x6620 = (x6614) * (x6597);
      number_t x6621 = (x6615) * (x6597);
      number_t x6622 = (x6614) * (x6600);
      number_t x6623 = (x6621) + (x6622);
      number_t x6628 = (x6620) * (x6620);
      number_t x6629 = (x6623) * (x6620);
      number_t x6630 = (x6620) * (x6623);
      number_t x6631 = (x6629) + (x6630);
      number_t x6632 = (x6609) + (x6628);
      number_t x6633 = (x6612) + (x6631);
      number_t x6634 = (x6280) * (x6632);
      number_t x6635 = (x6410) * (x6632);
      number_t x6636 = (x6280) * (x6633);
      number_t x6637 = (x6635) + (x6636);
      number_t x6640 = (x6281) * (x6632);
      number_t x6641 = (x6412) * (x6632);
      number_t x6642 = (x6281) * (x6633);
      number_t x6643 = (x6641) + (x6642);
      number_t x6646 = (1) + (x6634);
      number_t x6647 = (x6640) * (x6632);
      number_t x6648 = (x6643) * (x6632);
      number_t x6649 = (x6640) * (x6633);
      number_t x6650 = (x6648) + (x6649);
      number_t x6651 = (x6646) + (x6647);
      number_t x6652 = (x6637) + (x6650);
      array_number_t x6677 = (array_number_t)storage_alloc(sizeof(int) * 2);x6677->length=2;x6677->arr = (number_t*)storage_alloc(sizeof(number_t) * 2);
      for(int i00 = 0; i00 < x6677->length; i00++){
        index_t x6654 = (i00) + (7);
        tuple_number_t_number_t x6655 = (x6590->arr[i00]);
        number_t x6656 = (x6655)._1;
        number_t x6657 = (x6655)._2;
        number_t x6658 = (x6656) * (x6282);
        number_t x6659 = (x6657) * (x6282);
        number_t x6660 = (x6656) * (x6414);
        number_t x6661 = (x6659) + (x6660);
        number_t x6662 = (x6658) * (x6651);
        number_t x6663 = (x6661) * (x6651);
        number_t x6664 = (x6658) * (x6652);
        number_t x6665 = (x6663) + (x6664);
        number_t x6666 = (xs->arr[x6654]);
        index_t x6667 = (i) == (x6654);
        index_t x6668;
        if (x6667) {
          x6668 = 1;
        } else {
          x6668 = 0;
        }
        number_t x6669 = (x6662) * (x6282);
        number_t x6670 = (x6665) * (x6282);
        number_t x6671 = (x6662) * (x6414);
        number_t x6672 = (x6670) + (x6671);
        number_t x6673 = (x6666) + (x6669);
        number_t x6674 = (x6668) + (x6672);
        tuple_number_t_number_t x6675 = (tuple_number_t_number_t){._1=x6673, ._2=x6674};
        number_t x6676 = (x6675)._2;
        x6677->arr[i00] = x6676;
        
      }
      x6678->arr[i0] = x6677;
      
    }
    x6679->arr[i] = x6678;
    
  }
  return x6679;
}
