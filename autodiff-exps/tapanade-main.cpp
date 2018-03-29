#include <iostream>
#include <string>
#include <chrono>
#include <set>

#include "shared/utils.h"
#include "shared/defs.h"

#if defined DO_BA
#include "tapanade/ba_d-all.h"

double sqsum(int n, double *x)
{
  int i;
  double res;
  res = 0;
  for (i = 0; i < n; i++)
    res = res + x[i] * x[i];
  return res;
}


int test_ba()
{
    // auto cam = vec(
    //     0.1, 0.1, 0.1,     // ROT_IDX = 0;    
    //     0.2,0.1,0.3,       // CENTER_IDX = 3;
    //     1.2,               // FOCAL_IDX = 6;
    //     0.01, 0.03,        // X0_IDX = 7;
    //     0.009, 1.2e-4      // RAD_IDX = 9;
    //     );

    // Vec3<Real> X = vec(0.03, 0.11, -0.7);
    double cam[] = { 0.1, 0.1, 0.1,     // ROT_IDX = 0;    
        0.2,0.1,0.3,       // CENTER_IDX = 3;
        1.2,               // FOCAL_IDX = 6;
        0.01, 0.03,        // X0_IDX = 7;
        0.009, 1.2e-4      // RAD_IDX = 9;
        };
    double X[] = {0.03, 0.11, -0.7};

    // boost::timer::auto_cpu_timer t;
    timer_t t = tic();

    // Debug 150s 
    // Release 1s
    double total = 0;
    int N = 10000000;
#ifdef _DEBUG
    N = N / 100;  // Debug is roughly this much slower than release -- multiply timings.
#endif
    for (int count = 0; count < N; ++count) {
        X[0] = 1.0 / (2.0 + count);
        cam[5] = 1.0 + count * 1e-6;

        double proj[2];
        double proj_d[2];
        project_d(cam, cam , X, X, proj, proj_d);

        total += sqsum(2, proj_d);
    }

    // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall/double(N) << "ns" << std::endl;
    // std::cout << "total =" << total << std::endl;
    auto elapsed = toc(t);
    printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
    
    return 0;
}

#elif defined DO_GMM
// #include "tapanade/gmm.h"
extern "C"
{
#if defined TAPENADE
#include "tapanade/gmm_all.h"
#else 
extern "C"
{
#include "diffsmooth/gmm_compact.h"
}
#endif
}

#include "diffsmooth/types.h"
const size_t GMM_K = 5;
const size_t GMM_D = 2;

double dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

array_array_number_t matrix_fill(card_t rows, card_t cols, number_t value) {
  array_array_number_t macroDef83 = (array_array_number_t)malloc(sizeof(int) * 2);
  macroDef83->length=rows;
  macroDef83->arr = (array_number_t*)malloc(sizeof(array_number_t) * rows);
    for(int r = 0; r < macroDef83->length; r++){
      array_number_t macroDef82 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef82->length=cols;
  macroDef82->arr = (number_t*)malloc(sizeof(number_t) * cols);
    for(int c = 0; c < macroDef82->length; c++){
      
      macroDef82->arr[c] = value;;
    }
      macroDef83->arr[r] = macroDef82;;
    }
  return macroDef83;
}

array_number_t vector_fill(card_t rows, number_t value) {
  return matrix_fill(1, rows, value)->arr[0];
}

void array_print(array_number_t arr) {
  printf("[");
  for (int i = 0; i < arr->length; i++) {
    printf("%f", arr->arr[i]);
    if (i != arr->length - 1)
      printf(", ");
  }
  printf("]\n");
}

#if defined DIFFSMOOTH 

#include "diffsmooth/fsmooth_core.h"

array_number_t gmm_objective3_d_alphas(array_array_number_t x, array_number_t alphas, array_array_number_t means, array_array_number_t qs, array_array_number_t ls, number_t wishart_gamma, number_t wishart_m) {
  array_number_t x27461 = (array_number_t)storage_alloc(sizeof(int) * 2);x27461->length=(alphas)->length;x27461->arr = (number_t*)storage_alloc(sizeof(number_t) * (alphas)->length);
  for(int i = 0; i < x27461->length; i++){
    tuple_number_t_index_t x14820 = {-1000, 0};
    for (int x13098 = 0; x13098 < (alphas)->length; x13098++) {
      tuple_number_t_index_t x13097 = x14820;
      tuple_number_t_index_t x27450;
      if (((x13097)._1) > ((alphas->arr[x13098]))) {
        x27450 = x13097;
      } else {
        index_t x27449;
        if ((i) = (x13098)) {
          x27449 = 1;
        } else {
          x27449 = 0;
        }
        x27450 = {(alphas->arr[x13098]), x27449};
      }
      x13097 = x27450;
      x14820 = x13097;
    }
    
    tuple_number_t_number_t x14864 = {0, 0};
    for (int x13172 = 0; x13172 < (alphas)->length; x13172++) {
      tuple_number_t_number_t x13171 = x14864;
      number_t x14092 = exp(((alphas->arr[x13172])) - ((x14820)._1));
      number_t x27451;
      if ((i) = (x13172)) {
        x27451 = ((x13171)._2) + (((1) - ((x14820)._2)) * (x14092));
      } else {
        x27451 = ((x13171)._2) + (((0) - ((x14820)._2)) * (x14092));
      }
      x13171 = {((x13171)._1) + (x14092), x27451};
      x14864 = x13171;
    }
    
    tuple_number_t_number_t x27459 = {0, 0};
    for (int x13154 = 0; x13154 < (x)->length; x13154++) {
      tuple_number_t_number_t x13153 = x27459;
      array_number_t x27444 = (x->arr[x13154]);
      array_number_t x27410 = (x->arr[x13154]);
      tuple_number_t_number_t x27378 = {-1000, 0};
      for (int x13228 = 0; x13228 < (alphas)->length; x13228++) {
        tuple_number_t_number_t x13227 = x27378;
        array_number_t x27406 = (qs->arr[x13228]);
        tuple_number_t_index_t x27442 = {0, 0};
        for (int x13362 = 0; x13362 < (x27406)->length; x13362++) {
          tuple_number_t_index_t x13361 = x27442;
          x13361 = {((x13361)._1) + ((x27406->arr[x13362])), (x13361)._2};
          x27442 = x13361;
        }
        
        array_number_t x27346 = (ls->arr[x13228]);
        tuple_number_t_number_t x27376 = {0, 0};
        for (int x13358 = 0; x13358 < (x27444)->length; x13358++) {
          tuple_number_t_number_t x13357 = x27376;
          number_t x27438 = ((x27444->arr[x13358])) - (((means->arr[x13228])->arr[x13358]));
          index_t x27402 = ((x13358) - (1)) + (1);
          index_t x27372 = (x13358) - (1);
          tuple_number_t_index_t x27400 = {0, 0};
          for (int x13498 = 0; x13498 < (x27346)->length; x13498++) {
            tuple_number_t_index_t x13497 = x27400;
            tuple_index_t_index_t x27452;
            if (((x13498) - (((x27372) * (x27402)) / (2))) >= (0)) {
              x27452 = {((x13498) - (((x27372) * (x27402)) / (2))) < (x13358), 0};
            } else {
              x27452 = {0, 0};
            }
            tuple_number_t_index_t x27453;
            if ((x27452)._1) {
              x27453 = {((x13497)._1) + (((x27346->arr[x13498])) * (((x27444->arr[(x13498) - (((x27372) * (x27402)) / (2))])) - (((means->arr[x13228])->arr[(x13498) - (((x27372) * (x27402)) / (2))])))), (x13497)._2};
            } else {
              x27453 = x13497;
            }
            x13497 = x27453;
            x27400 = x13497;
          }
          
          number_t x27310 = exp(((qs->arr[x13228])->arr[x13358]));
          number_t x27430 = ((x27400)._1) + ((x27310) * (x27438));
          number_t x27396 = ((x27400)._1) + ((x27310) * (x27438));
          x13357 = {((x13357)._1) + ((x27430) * (x27396)), ((x13357)._2) + ((((x27400)._2) * (x27396)) + ((x27430) * ((x27400)._2)))};
          x27376 = x13357;
        }
        
        tuple_number_t_number_t x27455;
        if (((x13227)._1) > ((((alphas->arr[x13228])) + ((x27442)._1)) - ((0.5) * ((x27376)._1)))) {
          x27455 = x13227;
        } else {
          number_t x27454;
          if ((i) = (x13228)) {
            x27454 = ((1) + ((x27442)._2)) - ((0.5) * ((x27376)._2));
          } else {
            x27454 = ((x27442)._2) - ((0.5) * ((x27376)._2));
          }
          x27455 = {(((alphas->arr[x13228])) + ((x27442)._1)) - ((0.5) * ((x27376)._1)), x27454};
        }
        x13227 = x27455;
        x27378 = x13227;
      }
      
      tuple_number_t_number_t x13892 = {0, 0};
      for (int x13266 = 0; x13266 < (alphas)->length; x13266++) {
        tuple_number_t_number_t x13265 = x13892;
        array_number_t x27428 = (qs->arr[x13266]);
        array_number_t x27394 = (ls->arr[x13266]);
        tuple_number_t_index_t x27426 = {0, 0};
        for (int x13458 = 0; x13458 < (x27428)->length; x13458++) {
          tuple_number_t_index_t x13457 = x27426;
          x13457 = {((x13457)._1) + ((x27428->arr[x13458])), (x13457)._2};
          x27426 = x13457;
        }
        
        tuple_number_t_number_t x27392 = {0, 0};
        for (int x13454 = 0; x13454 < (x27410)->length; x13454++) {
          tuple_number_t_number_t x13453 = x27392;
          number_t x27424 = ((x27410->arr[x13454])) - (((means->arr[x13266])->arr[x13454]));
          index_t x27390 = ((x13454) - (1)) + (1);
          index_t x27360 = (x13454) - (1);
          tuple_number_t_index_t x27388 = {0, 0};
          for (int x13614 = 0; x13614 < (x27394)->length; x13614++) {
            tuple_number_t_index_t x13613 = x27388;
            tuple_index_t_index_t x27456;
            if (((x13614) - (((x27360) * (x27390)) / (2))) >= (0)) {
              x27456 = {((x13614) - (((x27360) * (x27390)) / (2))) < (x13454), 0};
            } else {
              x27456 = {0, 0};
            }
            tuple_number_t_index_t x27457;
            if ((x27456)._1) {
              x27457 = {((x13613)._1) + (((x27394->arr[x13614])) * (((x27410->arr[(x13614) - (((x27360) * (x27390)) / (2))])) - (((means->arr[x13266])->arr[(x13614) - (((x27360) * (x27390)) / (2))])))), (x13613)._2};
            } else {
              x27457 = x13613;
            }
            x13613 = x27457;
            x27388 = x13613;
          }
          
          number_t x27296 = exp(((qs->arr[x13266])->arr[x13454]));
          number_t x27416 = ((x27388)._1) + ((x27296) * (x27424));
          number_t x27384 = ((x27388)._1) + ((x27296) * (x27424));
          x13453 = {((x13453)._1) + ((x27416) * (x27384)), ((x13453)._2) + ((((x27388)._2) * (x27384)) + ((x27416) * ((x27388)._2)))};
          x27392 = x13453;
        }
        
        number_t x14362 = exp(((((alphas->arr[x13266])) + ((x27426)._1)) - ((0.5) * ((x27392)._1))) - ((x27378)._1));
        number_t x27458;
        if ((i) = (x13266)) {
          x27458 = ((x13265)._2) + (((((1) + ((x27426)._2)) - ((0.5) * ((x27392)._2))) - ((x27378)._2)) * (x14362));
        } else {
          x27458 = ((x13265)._2) + (((((x27426)._2) - ((0.5) * ((x27392)._2))) - ((x27378)._2)) * (x14362));
        }
        x13265 = {((x13265)._1) + (x14362), x27458};
        x13892 = x13265;
      }
      
      x13153 = {((x13153)._1) + ((log((x13892)._1)) + ((x27378)._1)), ((x13153)._2) + ((((x13892)._2) / ((x13892)._1)) + ((x27378)._2))};
      x27459 = x13153;
    }
    
    tuple_number_t_index_t x27460 = {0, 0};
    for (int x13138 = 0; x13138 < (alphas)->length; x13138++) {
      tuple_number_t_index_t x13137 = x27460;
      array_number_t x27448 = (qs->arr[x13138]);
      array_number_t x27414 = (ls->arr[x13138]);
      tuple_number_t_index_t x27446 = {0, 0};
      for (int x13236 = 0; x13236 < (x27448)->length; x13236++) {
        tuple_number_t_index_t x13235 = x27446;
        number_t x13270 = exp((x27448->arr[x13236]));
        x13235 = {((x13235)._1) + ((x13270) * (x13270)), (x13235)._2};
        x27446 = x13235;
      }
      
      tuple_number_t_index_t x27412 = {0, 0};
      for (int x13232 = 0; x13232 < (x27414)->length; x13232++) {
        tuple_number_t_index_t x13231 = x27412;
        x13231 = {((x13231)._1) + (((x27414->arr[x13232])) * ((x27414->arr[x13232]))), (x13231)._2};
        x27412 = x13231;
      }
      
      x13137 = {((x13137)._1) + (((x27446)._1) + ((x27412)._1)), ((x13137)._2) + (((x27446)._2) + ((x27412)._2))};
      x27460 = x13137;
    }
    
    x27461->arr[i] = (((x27459)._2) - (((double)((x)->length)) * ((((x14864)._2) / ((x14864)._1)) + ((x14820)._2)))) + ((0.5) * ((x27460)._2));
    
  }
  return x27461;
}

number_t gmm_objective3_d(array_array_number_t x, array_number_t alphas, array_array_number_t means, array_array_number_t qs, array_array_number_t ls, number_t wishart_gamma, number_t wishart_m, array_number_t alphasd, array_array_number_t meansd, array_array_number_t qsd, array_array_number_t lsd) {
  tuple_number_t_number_t x9786 = {-1000, 0};
  for (int x7912 = 0; x7912 < (alphas)->length; x7912++) {
    tuple_number_t_number_t x7911 = x9786;
    tuple_number_t_number_t x30713;
    if (((x7911)._1) > ((alphas->arr[x7912]))) {
      x30713 = x7911;
    } else {
      x30713 = {(alphas->arr[x7912]), (alphasd->arr[x7912])};
    }
    x7911 = x30713;
    x9786 = x7911;
  }
  
  tuple_number_t_number_t x10248 = {0, 0};
  for (int x7986 = 0; x7986 < (alphas)->length; x7986++) {
    tuple_number_t_number_t x7985 = x10248;
    number_t x9456 = exp(((alphas->arr[x7986])) - ((x9786)._1));
    x7985 = {((x7985)._1) + (x9456), ((x7985)._2) + ((((alphasd->arr[x7986])) - ((x9786)._2)) * (x9456))};
    x10248 = x7985;
  }
  
  tuple_number_t_number_t x30719 = {0, 0};
  for (int x7968 = 0; x7968 < (x)->length; x7968++) {
    tuple_number_t_number_t x7967 = x30719;
    array_number_t x30706 = (x->arr[x7968]);
    array_number_t x30600 = (x->arr[x7968]);
    tuple_number_t_number_t x30650 = {-1000, 0};
    for (int x8042 = 0; x8042 < (alphas)->length; x8042++) {
      tuple_number_t_number_t x8041 = x30650;
      array_number_t x30648 = (ls->arr[x8042]);
      tuple_number_t_number_t x30702 = {0, 0};
      for (int x8172 = 0; x8172 < (x30600)->length; x8172++) {
        tuple_number_t_number_t x8171 = x30702;
        number_t x30696 = ((x30600->arr[x8172])) - (((means->arr[x8042])->arr[x8172]));
        number_t x30642 = exp(((qs->arr[x8042])->arr[x8172]));
        number_t x30694 = (((((qsd->arr[x8042])->arr[x8172])) * (x30642)) * (x30696)) + ((x30642) * ((0) - (((meansd->arr[x8042])->arr[x8172]))));
        index_t x30388 = (((x8172) - (1)) * (((x8172) - (1)) + (1))) / (2);
        tuple_number_t_number_t x30446 = {0, 0};
        for (int x8312 = 0; x8312 < (x30648)->length; x8312++) {
          tuple_number_t_number_t x8311 = x30446;
          index_t x30636 = (x8312) - (x30388);
          number_t x30690 = ((x30600->arr[(x8312) - (x30388)])) - (((means->arr[x8042])->arr[x30636]));
          number_t x30590 = (x30648->arr[x8312]);
          tuple_index_t_index_t x30714;
          if (((x8312) - (x30388)) >= (0)) {
            x30714 = {((x8312) - (x30388)) < (x8172), 0};
          } else {
            x30714 = {0, 0};
          }
          tuple_number_t_number_t x30715;
          if ((x30714)._1) {
            x30715 = {((x8311)._1) + ((x30590) * (x30690)), ((x8311)._2) + (((((lsd->arr[x8042])->arr[x8312])) * (x30690)) + ((x30590) * ((0) - (((meansd->arr[x8042])->arr[x30636])))))};
          } else {
            x30715 = x8311;
          }
          x8311 = x30715;
          x30446 = x8311;
        }
        
        number_t x30536 = (x30446)._2;
        number_t x30486 = (x30446)._1;
        number_t x30340 = (x30642) * (x30696);
        number_t x30630 = (x30486) + (x30340);
        number_t x30580 = (x30486) + (x30340);
        x8171 = {((x8171)._1) + ((x30580) * (x30630)), ((x8171)._2) + ((((x30536) + (x30694)) * (x30630)) + ((x30580) * ((x30536) + (x30694))))};
        x30702 = x8171;
      }
      
      array_number_t x30492 = (qs->arr[x8042]);
      tuple_number_t_number_t x30542 = {0, 0};
      for (int x8176 = 0; x8176 < (x30492)->length; x8176++) {
        tuple_number_t_number_t x8175 = x30542;
        x8175 = {((x8175)._1) + ((x30492->arr[x8176])), ((x8175)._2) + (((qsd->arr[x8042])->arr[x8176]))};
        x30542 = x8175;
      }
      
      number_t x30598 = ((alphas->arr[x8042])) + ((x30542)._1);
      number_t x30430 = (0.5) * ((x30702)._1);
      tuple_number_t_number_t x30716;
      if (((x8041)._1) > ((x30598) - (x30430))) {
        x30716 = x8041;
      } else {
        x30716 = {(x30598) - (x30430), (((alphasd->arr[x8042])) + ((x30542)._2)) - ((0.5) * ((x30702)._2))};
      }
      x8041 = x30716;
      x30650 = x8041;
    }
    
    tuple_number_t_number_t x10326 = {0, 0};
    for (int x8080 = 0; x8080 < (alphas)->length; x8080++) {
      tuple_number_t_number_t x8079 = x10326;
      array_number_t x30678 = (qs->arr[x8080]);
      array_number_t x30626 = (ls->arr[x8080]);
      tuple_number_t_number_t x30676 = {0, 0};
      for (int x8272 = 0; x8272 < (x30678)->length; x8272++) {
        tuple_number_t_number_t x8271 = x30676;
        x8271 = {((x8271)._1) + ((x30678->arr[x8272])), ((x8271)._2) + (((qsd->arr[x8080])->arr[x8272]))};
        x30676 = x8271;
      }
      
      tuple_number_t_number_t x30624 = {0, 0};
      for (int x8268 = 0; x8268 < (x30706)->length; x8268++) {
        tuple_number_t_number_t x8267 = x30624;
        number_t x30674 = ((x30706->arr[x8268])) - (((means->arr[x8080])->arr[x8268]));
        number_t x30622 = exp(((qs->arr[x8080])->arr[x8268]));
        number_t x30672 = (((((qsd->arr[x8080])->arr[x8268])) * (x30622)) * (x30674)) + ((x30622) * ((0) - (((meansd->arr[x8080])->arr[x8268]))));
        index_t x30370 = (((x8268) - (1)) * (((x8268) - (1)) + (1))) / (2);
        tuple_number_t_number_t x30420 = {0, 0};
        for (int x8428 = 0; x8428 < (x30626)->length; x8428++) {
          tuple_number_t_number_t x8427 = x30420;
          index_t x30616 = (x8428) - (x30370);
          number_t x30668 = ((x30706->arr[(x8428) - (x30370)])) - (((means->arr[x8080])->arr[x30616]));
          number_t x30566 = (x30626->arr[x8428]);
          tuple_index_t_index_t x30717;
          if (((x8428) - (x30370)) >= (0)) {
            x30717 = {((x8428) - (x30370)) < (x8268), 0};
          } else {
            x30717 = {0, 0};
          }
          tuple_number_t_number_t x30718;
          if ((x30717)._1) {
            x30718 = {((x8427)._1) + ((x30566) * (x30668)), ((x8427)._2) + (((((lsd->arr[x8080])->arr[x8428])) * (x30668)) + ((x30566) * ((0) - (((meansd->arr[x8080])->arr[x30616])))))};
          } else {
            x30718 = x8427;
          }
          x8427 = x30718;
          x30420 = x8427;
        }
        
        number_t x30514 = (x30420)._2;
        number_t x30466 = (x30420)._1;
        number_t x30320 = (x30622) * (x30674);
        number_t x30610 = (x30466) + (x30320);
        number_t x30556 = (x30466) + (x30320);
        x8267 = {((x8267)._1) + ((x30556) * (x30610)), ((x8267)._2) + ((((x30514) + (x30672)) * (x30610)) + ((x30556) * ((x30514) + (x30672))))};
        x30624 = x8267;
      }
      
      number_t x10636 = exp(((((alphas->arr[x8080])) + ((x30676)._1)) - ((0.5) * ((x30624)._1))) - ((x30650)._1));
      x8079 = {((x8079)._1) + (x10636), ((x8079)._2) + ((((((alphasd->arr[x8080])) + ((x30676)._2)) - ((0.5) * ((x30624)._2))) - ((x30650)._2)) * (x10636))};
      x10326 = x8079;
    }
    
    x7967 = {((x7967)._1) + ((log((x10326)._1)) + ((x30650)._1)), ((x7967)._2) + ((((x10326)._2) / ((x10326)._1)) + ((x30650)._2))};
    x30719 = x7967;
  }
  
  tuple_number_t_number_t x30720 = {0, 0};
  for (int x7952 = 0; x7952 < (alphas)->length; x7952++) {
    tuple_number_t_number_t x7951 = x30720;
    array_number_t x30712 = (qs->arr[x7952]);
    array_number_t x30606 = (ls->arr[x7952]);
    tuple_number_t_number_t x30656 = {0, 0};
    for (int x8046 = 0; x8046 < (x30606)->length; x8046++) {
      tuple_number_t_number_t x8045 = x30656;
      number_t x30708 = (x30606->arr[x8046]);
      number_t x30652 = (x30606->arr[x8046]);
      x8045 = {((x8045)._1) + ((x30708) * (x30652)), ((x8045)._2) + (((((lsd->arr[x7952])->arr[x8046])) * (x30652)) + ((x30708) * (((lsd->arr[x7952])->arr[x8046]))))};
      x30656 = x8045;
    }
    
    tuple_number_t_number_t x30552 = {0, 0};
    for (int x8050 = 0; x8050 < (x30712)->length; x8050++) {
      tuple_number_t_number_t x8049 = x30552;
      number_t x9418 = exp((x30712->arr[x8050]));
      x8049 = {((x8049)._1) + ((x9418) * (x9418)), ((x8049)._2) + ((((((qsd->arr[x7952])->arr[x8050])) * (x9418)) * (x9418)) + ((x9418) * ((((qsd->arr[x7952])->arr[x8050])) * (x9418))))};
      x30552 = x8049;
    }
    
    x7951 = {((x7951)._1) + (((x30552)._1) + ((x30656)._1)), ((x7951)._2) + (((x30552)._2) + ((x30656)._2))};
    x30720 = x7951;
  }
  
  return (((x30719)._2) - (((double)((x)->length)) * ((((x10248)._2) / ((x10248)._1)) + ((x9786)._2)))) + ((0.5) * ((x30720)._2));
}

number_t gmm_objective3(array_array_number_t x, array_number_t alphas, array_array_number_t means, array_array_number_t qs, array_array_number_t ls, number_t wishart_gamma, number_t wishart_m) {
  index_t x16718 = (x)->length;
  index_t x21030 = (alphas)->length;
  number_t x21020 = -1000;
  for (int idx = 0; idx < (alphas)->length; idx++) {
    number_t acc = x21020;
    number_t cur = (alphas->arr[idx]);
    number_t x21031;
    if ((acc) > (cur)) {
      x21031 = acc;
    } else {
      x21031 = cur;
    }
    acc = x21031;
    x21020 = acc;
  }
  
  number_t x21044 = 0;
  for (int idx = 0; idx < x16718; idx++) {
    number_t acc = x21044;
    array_number_t x21026 = (x->arr[idx]);
    array_number_t x21016 = (x->arr[idx]);
    number_t x21004 = -1000;
    for (int idx0 = 0; idx0 < x21030; idx0++) {
      number_t acc0 = x21004;
      array_number_t x21024 = (ls->arr[idx0]);
      array_number_t x21012 = (qs->arr[idx0]);
      number_t x21032 = 0;
      for (int idx00 = 0; idx00 < (x21012)->length; idx00++) {
        number_t acc00 = x21032;
        acc00 = (acc00) + ((x21012->arr[idx00]));
        x21032 = acc00;
      }
      
      number_t x21036 = 0;
      for (int idx00 = 0; idx00 < (x21026)->length; idx00++) {
        number_t acc00 = x21036;
        index_t x16548 = (idx00) - (1);
        number_t x21035 = 0;
        for (int idx000 = 0; idx000 < (x21024)->length; idx000++) {
          number_t acc000 = x21035;
          index_t j = (idx000) - (((x16548) * ((x16548) + (1))) / (2));
          index_t x21033;
          if ((j) >= (0)) {
            x21033 = (j) < (idx00);
          } else {
            x21033 = 0;
          }
          number_t x21034;
          if (x21033) {
            x21034 = (acc000) + (((x21024->arr[idx000])) * (((x21026->arr[j])) - (((means->arr[idx0])->arr[j]))));
          } else {
            x21034 = acc000;
          }
          acc000 = x21034;
          x21035 = acc000;
        }
        
        number_t x16752 = (x21035) + ((exp(((qs->arr[idx0])->arr[idx00]))) * (((x21026->arr[idx00])) - (((means->arr[idx0])->arr[idx00]))));
        acc00 = (acc00) + ((x16752) * (x16752));
        x21036 = acc00;
      }
      
      number_t cur = (((alphas->arr[idx0])) + (x21032)) - ((0.5) * (x21036));
      number_t x21037;
      if ((acc0) > (cur)) {
        x21037 = acc0;
      } else {
        x21037 = cur;
      }
      acc0 = x21037;
      x21004 = acc0;
    }
    
    number_t x21043 = 0;
    for (int idx0 = 0; idx0 < x21030; idx0++) {
      number_t acc0 = x21043;
      array_number_t x21022 = (qs->arr[idx0]);
      array_number_t x21010 = (ls->arr[idx0]);
      number_t x21038 = 0;
      for (int idx00 = 0; idx00 < (x21022)->length; idx00++) {
        number_t acc00 = x21038;
        acc00 = (acc00) + ((x21022->arr[idx00]));
        x21038 = acc00;
      }
      
      number_t x21042 = 0;
      for (int idx00 = 0; idx00 < (x21016)->length; idx00++) {
        number_t acc00 = x21042;
        index_t x16548 = (idx00) - (1);
        number_t x21041 = 0;
        for (int idx000 = 0; idx000 < (x21010)->length; idx000++) {
          number_t acc000 = x21041;
          index_t j = (idx000) - (((x16548) * ((x16548) + (1))) / (2));
          index_t x21039;
          if ((j) >= (0)) {
            x21039 = (j) < (idx00);
          } else {
            x21039 = 0;
          }
          number_t x21040;
          if (x21039) {
            x21040 = (acc000) + (((x21010->arr[idx000])) * (((x21016->arr[j])) - (((means->arr[idx0])->arr[j]))));
          } else {
            x21040 = acc000;
          }
          acc000 = x21040;
          x21041 = acc000;
        }
        
        number_t x16720 = (x21041) + ((exp(((qs->arr[idx0])->arr[idx00]))) * (((x21016->arr[idx00])) - (((means->arr[idx0])->arr[idx00]))));
        acc00 = (acc00) + ((x16720) * (x16720));
        x21042 = acc00;
      }
      
      acc0 = (acc0) + (exp(((((alphas->arr[idx0])) + (x21038)) - ((0.5) * (x21042))) - (x21004)));
      x21043 = acc0;
    }
    
    acc = (acc) + ((log(x21043)) + (x21004));
    x21044 = acc;
  }
  
  number_t x21045 = 0;
  for (int idx = 0; idx < (alphas)->length; idx++) {
    number_t acc = x21045;
    acc = (acc) + (exp(((alphas->arr[idx])) - (x21020)));
    x21045 = acc;
  }
  
  number_t x21048 = 0;
  for (int idx = 0; idx < x21030; idx++) {
    number_t acc = x21048;
    array_number_t x21028 = (qs->arr[idx]);
    array_number_t x21018 = (ls->arr[idx]);
    number_t x21046 = 0;
    for (int idx0 = 0; idx0 < (x21028)->length; idx0++) {
      number_t acc0 = x21046;
      number_t x16768 = exp((x21028->arr[idx0]));
      acc0 = (acc0) + ((x16768) * (x16768));
      x21046 = acc0;
    }
    
    number_t x21047 = 0;
    for (int idx0 = 0; idx0 < (x21018)->length; idx0++) {
      number_t acc0 = x21047;
      number_t x16770 = (x21018->arr[idx0]);
      acc0 = (acc0) + ((x16770) * (x16770));
      x21047 = acc0;
    }
    
    acc = (acc) + ((x21046) + (x21047));
    x21048 = acc;
  }
  
  return ((x21044) - (((double)(x16718)) * ((log(x21045)) + (x21020)))) + ((0.5) * (x21048));
}
#else

double arr_max(int n, double* x)
{
  double m;
  int i;

  m = x[0];
  for (i = 1; i < n; i++)
  {
    if (x[i] > m)
      m = x[i];
  }
  return m;
}

double logsumexp(int n, double* x)
{
  int i;
  double mx, semx;

  mx = arr_max(n, x);
  semx = 0.;
  for (i = 0; i < n; i++)
  {
    semx += exp(x[i] - mx);
  }
  return log(semx) + mx;
}

double sqnorm(int d,
  double* x)
{
  int i;
  double out;

  out = 0;
  for (i = 0; i < d; i++)
  {
    out += x[i] * x[i];
  }
  return out;
}

double log_wishart_prior(int p, int k, 
  double wishart_gamma, 
  double wishart_m,
  double *sum_qs,
  double *Qdiags,
  double* icf)
{
  int n, ik, icf_sz;
  double out, C, frobenius;

  icf_sz = p*(p + 1) / 2;

  out = 0;
  for (ik = 0; ik < k; ik++)
  {
    frobenius = sqnorm(p, &Qdiags[ik*p]) + sqnorm(icf_sz - p, &icf[ik*icf_sz + p]);
    out = out + 0.5 * frobenius;
  }

  // the last bit is here so that tapenade would recognize that means and inv_cov_factors are variables
  return out /* - k*C + (Qdiags[0] - Qdiags[0]) + (icf[0] - icf[0]) */;
}

void preprocess_qs(int d, int k,
  double* icf,
  double* sum_qs,
  double* Qdiags)
{
  int icf_sz, ik, id;
  double q;

  icf_sz = d*(d + 1) / 2;
  for (ik = 0; ik < k; ik++)
  {
    sum_qs[ik] = 0.;
    for (id = 0; id < d; id++)
    {
      q = icf[ik*icf_sz + id];
      sum_qs[ik] += q;
      Qdiags[ik*d + id] = exp(q);
    }
  }
}

void Qtimesx(int d,
  double* Qdiag,
  double* ltri, // strictly lower triangular part
  double* x,
  double* out)
{
  int id, i, j, Lparamsidx;

  for (id = 0; id < d; id++)
    out[id] = Qdiag[id] * x[id];

  Lparamsidx = 0;
  for (i = 0; i < d; i++)
  {
    for (j = i + 1; j < d; j++)
    {
      out[j] = out[j] + ltri[Lparamsidx] * x[i];
      Lparamsidx = Lparamsidx + 1;
    }
  }
}

// out = a - b
void subtract(int d,
  double* x,
  double* y,
  double* out)
{
  int id;
  for (id = 0; id < d; id++)
  {
    out[id] = x[id] - y[id];
  }
}
void gmm_objective2(int d, int k, int n,
  double* alphas, 
  double* means,
  double* icf, 
  double* x,
  double wishart_gamma, 
  double wishart_m,
  double *err)
{
  int ik, ix, icf_sz;
  double *main_term, *sum_qs, *Qdiags, *xcentered, *Qxcentered;
  double slse, lse_alphas, CONSTANT;
  // CONSTANT = -n*d*0.5*log(2 * PI);
  icf_sz = d*(d + 1) / 2;

  sum_qs = (double *)malloc(k*sizeof(double));
  Qdiags = (double *)malloc(d*k*sizeof(double));

  preprocess_qs(d, k, icf, sum_qs, Qdiags);
  main_term = (double *)malloc(k*sizeof(double));
  xcentered = (double *)malloc(d*sizeof(double));
  Qxcentered = (double *)malloc(d*sizeof(double));

  slse = 0.;
  for (ix = 0; ix < n; ix++)
  {

    for (ik = 0; ik < k; ik++)
    {
      subtract(d, &x[ix*d], &means[ik*d], xcentered);
      Qtimesx(d, &Qdiags[ik*d], &icf[ik*icf_sz + d], xcentered, Qxcentered);

      main_term[ik] = alphas[ik] + sum_qs[ik] - 0.5*sqnorm(d, Qxcentered);
    }
    slse = slse + logsumexp(k, main_term);
  }
  free(main_term);
  free(xcentered);
  free(Qxcentered);


  lse_alphas = logsumexp(k, alphas);
  *err = /*CONSTANT + */slse - n*lse_alphas;

  *err = *err + log_wishart_prior(d, k, wishart_gamma, wishart_m, sum_qs, Qdiags, icf);

  free(sum_qs);
  free(Qdiags);

  // this is here so that tapenade would recognize that means and inv_cov_factors are variables
  *err = *err /* + ((means[0] - means[0]) +
    (icf[0] - icf[0])) */;
}
#endif


void test_gmm()
{
  int rng = 42;
  srand(rng);
  // std::mt19937 rng(42);
  // std::uniform_real_distribution<Real> dist(0, 1);

  // Problem size
  size_t n = 100000;
  size_t d = GMM_D;
  size_t K = GMM_K;
  size_t td = ((d) * ((d) + (1))) / (2);
  

  // Declare and fill GMM coeffs
  // Vector alphas{ K };
  // Vec<VectorD> means{ K, VectorD{ d } };
  // Vec<VectorD> qs{ K, VectorD{ d } };
  // Vector l0{ size_t(tri(d)) };
  // Vec<Vector> ls{ K, l0 };
#if defined TAPENADE
  array_number_t alphas = vector_fill(K, 0);
  array_number_t means = vector_fill(K * d, 0);
  array_number_t qs = vector_fill(K * d, 0);
  array_number_t ls = vector_fill(K * td, 0);
  array_number_t icf = vector_fill(K * td, 0);
  for (int k = 0; k < K; ++k) {
    alphas->arr[k] = dist(rng);
    for (int j = 0; j < d; ++j) {
      means->arr[k * d + j] = dist(rng) - 0.5;
      qs->arr[k * d + j] = 10.0*dist(rng) - 5.0;
    }
    for (int j = 0; j < td; ++j) {
      ls->arr[k * td + j] = dist(rng) - 0.5;
      if(j >= td - d)
        ls->arr[k * td + j] = 0;
      if(j < d) {
        icf->arr[k * td + j] = qs->arr[k * d + j];
      } else {
        icf->arr[k * td + j] = ls->arr[k * td + j - d];
      }
    }
  }

  // Declare and fill xs
  // Vec<VectorD> xs{ n, Vector{ d } };
  array_number_t xsd = vector_fill(n * d, 0);
  array_number_t xs = vector_fill(n * d, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < d; ++j)
      xs->arr[i * d + j] = dist(rng);

#else 
  array_number_t alphas = vector_fill(K, 0);
  array_array_number_t means = matrix_fill(K, d, 0);
  array_array_number_t qs = matrix_fill(K, d, 0);
  array_array_number_t ls = matrix_fill(K, td, 0);
  for (int k = 0; k < K; ++k) {
    alphas->arr[k] = dist(rng);
    for (int j = 0; j < d; ++j) {
      means->arr[k]->arr[j] = dist(rng) - 0.5;
      qs->arr[k]->arr[j] = 10.0*dist(rng) - 5.0;
    }
    for (int j = 0; j < ls->arr[k]->length; ++j) {
      ls->arr[k]->arr[j] = dist(rng) - 0.5;
      if(j >= ls->arr[k]->length - d)
        ls->arr[k]->arr[j] = 0;
    }
  }

  // Declare and fill xs
  // Vec<VectorD> xs{ n, Vector{ d } };
  array_array_number_t xs = matrix_fill(n, d, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < d; ++j)
      xs->arr[i]->arr[j] = dist(rng);
#endif

  // TOP_LEVEL_usecases_gmm_Qtimesv_test(0);

  // boost::timer::auto_cpu_timer t;
  timer_t t = tic();

  gmm_init(d, K, n);

  // Debug 150s 
    // Release 1s
  double total = 0;
  int N = 100;
#ifdef _DEBUG
  N = N / 10;  // Debug is roughly this much slower than release -- multiply timings.
#endif
  double wishart_m = 2.0;
  for (int count = 0; count < N; ++count) {
    alphas->arr[0] += 1;
    double wishart_gamma = 1.0 / (1.0 + count);
    double res, tmp;

    // TODO icf instead of qs and ls
#if defined TAPENADE
    // gmm_objective2(d, K, n, alphas->arr, means->arr, icf->arr, xs->arr, wishart_gamma, wishart_m, &res);
    gmm_objective_d(d, K, n, alphas->arr, alphas->arr, means->arr, means->arr, icf->arr, icf->arr, xs->arr, xsd->arr, wishart_gamma, wishart_m, &tmp, &res);
#else
    // res = gmm_objective3(xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
    // res = gmm_objective_d(xs, alphas, means, qs, ls, wishart_gamma, wishart_m, xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
    res = gmm_objective3_d(xs, alphas, means, qs, ls, wishart_gamma, wishart_m, alphas, means, qs, ls);
#endif
    total += res;
  }

  // std::cout << "total =" << total << ", time per call = " << t.elapsed().wall / double(N) / 1000.0 << "us" << std::endl;
  double elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / (double)(N));
}



#elif defined DO_MICRO

Real dist(int seed) {
  return ((double)rand()/(double)RAND_MAX);
}

#ifdef ADD3
#define DIM 100
#elif DOT
#include "tapanade/dot_prod_d-all.h"
#define DIM 100
#elif CROSS
#define DIM 3
#endif

array_number_t vector_fill(card_t rows, number_t value) {
  array_number_t macroDef82 = (array_number_t)malloc(sizeof(int) * 2);
  macroDef82->length=rows;
  macroDef82->arr = (number_t*)malloc(sizeof(number_t) * rows);
  for(int i =0; i<rows; i++) {
    macroDef82->arr[i] = 0;
  }
  return macroDef82;
}

void test_micro(cardinality_t N)
{
  int rng = 42;
  srand(rng);
  array_number_t vec1 = vector_fill(DIM, 0.0);
  array_number_t vec2 = vector_fill(DIM, 0.0);
  array_number_t vec3 = vector_fill(DIM, 0.0);

  for (cardinality_t k = 0; k < DIM; ++k) {
    vec1->arr[k] = dist(rng);
    vec2->arr[k] = dist(rng);
    vec3->arr[k] = dist(rng);
  }

  timer_t t = tic();

  double total = 0;

  for (cardinality_t count = 0; count < N; ++count) {
    vec1->arr[0] += 1.0 / (2.0 + vec1->arr[0]);
    vec2->arr[1] += 1.0 / (2.0 + vec2->arr[1]);
#ifdef ADD3
#elif DOT
    double realResult;
    total +=  dot_prod_d(vec1, vec1, vec2, vec2, &realResult);
#elif CROSS
#endif
  }

  auto elapsed = toc(t);
  printf("total =%f, time per call = %f ms\n", total, elapsed / double(N));
}

#endif

int main(int argc, char *argv[])
{
#if defined DO_BA
  test_ba();
#elif defined DO_GMM
  test_gmm();
#elif defined DO_MICRO
  if(argc != 2) {
    printf("You should use the following format for running this program: %s <Number of Iterations>\n", argv[0]);
    exit(1);
  }
  cardinality_t N = atoi(argv[1]);
  test_micro(N);
#endif
}


