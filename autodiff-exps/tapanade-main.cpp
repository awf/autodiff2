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
#if defined TAPENADE
  #include "tapanade/gmm_all.h"
  #if defined REV_MODE
  extern "C" {
    #include "tapanade/submitted/2/gmm_b-all.h"
  }
  #endif
  #if defined MULT_MODE
  extern "C" {
    #include "tapanade/submitted/2/gmm_dv-all.h"
  }
  #endif
#elif defined DIFFSMOOTH
  extern "C"
  {
    #include "diffsmooth/gmm_compact.h"
  }
#elif defined TAP_FUSED
  extern "C"
  {
  #if defined REV_MODE
    #include "tapanade/submitted/5/gmm_fused.h_b-all.h"
  #else
    #include "tapanade/submitted/5/gmm_fused.h_d-all.h"
  #endif
  }
#elif defined TAP_UNFUSED
  extern "C"
  {
    #include "tapanade/submitted/7/gmm_unfused.h"
  #if defined REV_MODE
    #include "tapanade/submitted/7/gmm_unfused_b-all.h"
  #else
    #include "tapanade/submitted/7/gmm_unfused_d-all.h"
  #endif
  }
#endif 

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

number_t vector_sum(array_number_t m) {
  number_t result = 0;
  for(int i=0; i<m->length; i++) {
    result += m->arr[i];
  }
  return result;
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
        if ((i) == (x13098)) {
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
      if ((i) == (x13172)) {
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
          if ((i) == (x13228)) {
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
        if ((i) == (x13266)) {
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

array_number_t gmm_objective3_d_alphas_1(array_array_number_t x, array_number_t alphas, array_array_number_t means, array_array_number_t qs, array_array_number_t ls, number_t wishart_gamma, number_t wishart_m) {
  array_number_t x30014 = (array_number_t)storage_alloc(sizeof(int) * 2);x30014->length=(alphas)->length;x30014->arr = (number_t*)storage_alloc(sizeof(number_t) * (alphas)->length);
  for(int i = 0; i < x30014->length; i++){
    tuple_number_t_index_t x29973 = (tuple_number_t_index_t){._1=-1000, ._2=0};
    tuple_number_t_index_t x17341 = x29973;
    for (int x15619 = 0; x15619 < (alphas)->length; x15619++) {
      tuple_number_t_index_t x15618 = x17341;
      tuple_number_t_index_t x29972;
      if (((x15618)._1) > ((alphas->arr[x15619]))) {
        x29972 = x15618;
      } else {
        index_t x29970;
        if ((i) == (x15619)) {
          x29970 = 1;
        } else {
          x29970 = 0;
        }
        tuple_number_t_index_t x29971 = (tuple_number_t_index_t){._1=(alphas->arr[x15619]), ._2=x29970};
        x29972 = x29971;
      }
      x15618 = x29972;
      x17341 = x15618;
    }
    
    tuple_number_t_number_t x29976 = (tuple_number_t_number_t){._1=0, ._2=0};
    tuple_number_t_number_t x17385 = x29976;
    for (int x15693 = 0; x15693 < (alphas)->length; x15693++) {
      tuple_number_t_number_t x15692 = x17385;
      number_t x16613 = exp(((alphas->arr[x15693])) - ((x17341)._1));
      number_t x29974;
      if ((i) == (x15693)) {
        x29974 = ((x15692)._2) + (((1) - ((x17341)._2)) * (x16613));
      } else {
        x29974 = ((x15692)._2) + (((0) - ((x17341)._2)) * (x16613));
      }
      tuple_number_t_number_t x29975 = (tuple_number_t_number_t){._1=((x15692)._1) + (x16613), ._2=x29974};
      x15692 = x29975;
      x17385 = x15692;
    }
    
    tuple_number_t_number_t x30005 = (tuple_number_t_number_t){._1=0, ._2=0};
    tuple_number_t_number_t x30006 = x30005;
    for (int x15675 = 0; x15675 < (x)->length; x15675++) {
      tuple_number_t_number_t x15674 = x30006;
      array_number_t x29965 = (x->arr[x15675]);
      array_number_t x29931 = (x->arr[x15675]);
      tuple_number_t_number_t x29990 = (tuple_number_t_number_t){._1=-1000, ._2=0};
      tuple_number_t_number_t x29899 = x29990;
      for (int x15749 = 0; x15749 < (alphas)->length; x15749++) {
        tuple_number_t_number_t x15748 = x29899;
        array_number_t x29927 = (qs->arr[x15749]);
        tuple_number_t_index_t x29978 = (tuple_number_t_index_t){._1=0, ._2=0};
        tuple_number_t_index_t x29963 = x29978;
        for (int x15883 = 0; x15883 < (x29927)->length; x15883++) {
          tuple_number_t_index_t x15882 = x29963;
          tuple_number_t_index_t x29977 = (tuple_number_t_index_t){._1=((x15882)._1) + ((x29927->arr[x15883])), ._2=(x15882)._2};
          x15882 = x29977;
          x29963 = x15882;
        }
        
        array_number_t x29867 = (ls->arr[x15749]);
        tuple_number_t_number_t x29986 = (tuple_number_t_number_t){._1=0, ._2=0};
        tuple_number_t_number_t x29897 = x29986;
        for (int x15879 = 0; x15879 < (x29965)->length; x15879++) {
          tuple_number_t_number_t x15878 = x29897;
          number_t x29959 = ((x29965->arr[x15879])) - (((means->arr[x15749])->arr[x15879]));
          index_t x29923 = ((x15879) - (1)) + (1);
          index_t x29893 = (x15879) - (1);
          tuple_number_t_index_t x29984 = (tuple_number_t_index_t){._1=0, ._2=0};
          tuple_number_t_index_t x29921 = x29984;
          for (int x16019 = 0; x16019 < (x29867)->length; x16019++) {
            tuple_number_t_index_t x16018 = x29921;
            tuple_index_t_index_t x29981;
            if (((x16019) - (((x29893) * (x29923)) / (2))) >= (0)) {
              tuple_index_t_index_t x29979 = (tuple_index_t_index_t){._1=((x16019) - (((x29893) * (x29923)) / (2))) < (x15879), ._2=0};
              x29981 = x29979;
            } else {
              tuple_index_t_index_t x29980 = (tuple_index_t_index_t){._1=0, ._2=0};
              x29981 = x29980;
            }
            tuple_number_t_index_t x29983;
            if ((x29981)._1) {
              tuple_number_t_index_t x29982 = (tuple_number_t_index_t){._1=((x16018)._1) + (((x29867->arr[x16019])) * (((x29965->arr[(x16019) - (((x29893) * (x29923)) / (2))])) - (((means->arr[x15749])->arr[(x16019) - (((x29893) * (x29923)) / (2))])))), ._2=(x16018)._2};
              x29983 = x29982;
            } else {
              x29983 = x16018;
            }
            x16018 = x29983;
            x29921 = x16018;
          }
          
          number_t x29831 = exp(((qs->arr[x15749])->arr[x15879]));
          number_t x29951 = ((x29921)._1) + ((x29831) * (x29959));
          number_t x29917 = ((x29921)._1) + ((x29831) * (x29959));
          tuple_number_t_number_t x29985 = (tuple_number_t_number_t){._1=((x15878)._1) + ((x29951) * (x29917)), ._2=((x15878)._2) + ((((x29921)._2) * (x29917)) + ((x29951) * ((x29921)._2)))};
          x15878 = x29985;
          x29897 = x15878;
        }
        
        tuple_number_t_number_t x29989;
        if (((x15748)._1) > ((((alphas->arr[x15749])) + ((x29963)._1)) - ((0.5) * ((x29897)._1)))) {
          x29989 = x15748;
        } else {
          number_t x29987;
          if ((i) == (x15749)) {
            x29987 = ((1) + ((x29963)._2)) - ((0.5) * ((x29897)._2));
          } else {
            x29987 = ((x29963)._2) - ((0.5) * ((x29897)._2));
          }
          tuple_number_t_number_t x29988 = (tuple_number_t_number_t){._1=(((alphas->arr[x15749])) + ((x29963)._1)) - ((0.5) * ((x29897)._1)), ._2=x29987};
          x29989 = x29988;
        }
        x15748 = x29989;
        x29899 = x15748;
      }
      
      tuple_number_t_number_t x30003 = (tuple_number_t_number_t){._1=0, ._2=0};
      tuple_number_t_number_t x16413 = x30003;
      for (int x15787 = 0; x15787 < (alphas)->length; x15787++) {
        tuple_number_t_number_t x15786 = x16413;
        array_number_t x29949 = (qs->arr[x15787]);
        array_number_t x29915 = (ls->arr[x15787]);
        tuple_number_t_index_t x29992 = (tuple_number_t_index_t){._1=0, ._2=0};
        tuple_number_t_index_t x29947 = x29992;
        for (int x15979 = 0; x15979 < (x29949)->length; x15979++) {
          tuple_number_t_index_t x15978 = x29947;
          tuple_number_t_index_t x29991 = (tuple_number_t_index_t){._1=((x15978)._1) + ((x29949->arr[x15979])), ._2=(x15978)._2};
          x15978 = x29991;
          x29947 = x15978;
        }
        
        tuple_number_t_number_t x30000 = (tuple_number_t_number_t){._1=0, ._2=0};
        tuple_number_t_number_t x29913 = x30000;
        for (int x15975 = 0; x15975 < (x29931)->length; x15975++) {
          tuple_number_t_number_t x15974 = x29913;
          number_t x29945 = ((x29931->arr[x15975])) - (((means->arr[x15787])->arr[x15975]));
          index_t x29911 = ((x15975) - (1)) + (1);
          index_t x29881 = (x15975) - (1);
          tuple_number_t_index_t x29998 = (tuple_number_t_index_t){._1=0, ._2=0};
          tuple_number_t_index_t x29909 = x29998;
          for (int x16135 = 0; x16135 < (x29915)->length; x16135++) {
            tuple_number_t_index_t x16134 = x29909;
            tuple_index_t_index_t x29995;
            if (((x16135) - (((x29881) * (x29911)) / (2))) >= (0)) {
              tuple_index_t_index_t x29993 = (tuple_index_t_index_t){._1=((x16135) - (((x29881) * (x29911)) / (2))) < (x15975), ._2=0};
              x29995 = x29993;
            } else {
              tuple_index_t_index_t x29994 = (tuple_index_t_index_t){._1=0, ._2=0};
              x29995 = x29994;
            }
            tuple_number_t_index_t x29997;
            if ((x29995)._1) {
              tuple_number_t_index_t x29996 = (tuple_number_t_index_t){._1=((x16134)._1) + (((x29915->arr[x16135])) * (((x29931->arr[(x16135) - (((x29881) * (x29911)) / (2))])) - (((means->arr[x15787])->arr[(x16135) - (((x29881) * (x29911)) / (2))])))), ._2=(x16134)._2};
              x29997 = x29996;
            } else {
              x29997 = x16134;
            }
            x16134 = x29997;
            x29909 = x16134;
          }
          
          number_t x29817 = exp(((qs->arr[x15787])->arr[x15975]));
          number_t x29937 = ((x29909)._1) + ((x29817) * (x29945));
          number_t x29905 = ((x29909)._1) + ((x29817) * (x29945));
          tuple_number_t_number_t x29999 = (tuple_number_t_number_t){._1=((x15974)._1) + ((x29937) * (x29905)), ._2=((x15974)._2) + ((((x29909)._2) * (x29905)) + ((x29937) * ((x29909)._2)))};
          x15974 = x29999;
          x29913 = x15974;
        }
        
        number_t x16883 = exp(((((alphas->arr[x15787])) + ((x29947)._1)) - ((0.5) * ((x29913)._1))) - ((x29899)._1));
        number_t x30001;
        if ((i) == (x15787)) {
          x30001 = ((x15786)._2) + (((((1) + ((x29947)._2)) - ((0.5) * ((x29913)._2))) - ((x29899)._2)) * (x16883));
        } else {
          x30001 = ((x15786)._2) + (((((x29947)._2) - ((0.5) * ((x29913)._2))) - ((x29899)._2)) * (x16883));
        }
        tuple_number_t_number_t x30002 = (tuple_number_t_number_t){._1=((x15786)._1) + (x16883), ._2=x30001};
        x15786 = x30002;
        x16413 = x15786;
      }
      
      tuple_number_t_number_t x30004 = (tuple_number_t_number_t){._1=((x15674)._1) + ((log((x16413)._1)) + ((x29899)._1)), ._2=((x15674)._2) + ((((x16413)._2) / ((x16413)._1)) + ((x29899)._2))};
      x15674 = x30004;
      x30006 = x15674;
    }
    
    tuple_number_t_index_t x30012 = (tuple_number_t_index_t){._1=0, ._2=0};
    tuple_number_t_index_t x30013 = x30012;
    for (int x15659 = 0; x15659 < (alphas)->length; x15659++) {
      tuple_number_t_index_t x15658 = x30013;
      array_number_t x29969 = (qs->arr[x15659]);
      array_number_t x29935 = (ls->arr[x15659]);
      tuple_number_t_index_t x30008 = (tuple_number_t_index_t){._1=0, ._2=0};
      tuple_number_t_index_t x29967 = x30008;
      for (int x15757 = 0; x15757 < (x29969)->length; x15757++) {
        tuple_number_t_index_t x15756 = x29967;
        number_t x15791 = exp((x29969->arr[x15757]));
        tuple_number_t_index_t x30007 = (tuple_number_t_index_t){._1=((x15756)._1) + ((x15791) * (x15791)), ._2=(x15756)._2};
        x15756 = x30007;
        x29967 = x15756;
      }
      
      tuple_number_t_index_t x30010 = (tuple_number_t_index_t){._1=0, ._2=0};
      tuple_number_t_index_t x29933 = x30010;
      for (int x15753 = 0; x15753 < (x29935)->length; x15753++) {
        tuple_number_t_index_t x15752 = x29933;
        tuple_number_t_index_t x30009 = (tuple_number_t_index_t){._1=((x15752)._1) + (((x29935->arr[x15753])) * ((x29935->arr[x15753]))), ._2=(x15752)._2};
        x15752 = x30009;
        x29933 = x15752;
      }
      
      tuple_number_t_index_t x30011 = (tuple_number_t_index_t){._1=((x15658)._1) + (((x29967)._1) + ((x29933)._1)), ._2=((x15658)._2) + (((x29967)._2) + ((x29933)._2))};
      x15658 = x30011;
      x30013 = x15658;
    }
    
    x30014->arr[i] = (((x30006)._2) - (((double)((x)->length)) * ((((x17385)._2) / ((x17385)._1)) + ((x17341)._2)))) + ((0.5) * ((x30013)._2));
    
  }
  return x30014;
}


array_number_t gmm_objective3_d_alphas_2(array_array_number_t x, array_number_t alphas, array_array_number_t means, array_array_number_t qs, array_array_number_t ls, number_t wishart_gamma, number_t wishart_m) {
  index_t x26516 = (x)->length;
  number_t x26517 = x26516;
  number_t x26518 = (double)(x26517);
  index_t x26526 = (alphas)->length;
  tuple_index_t_index_t x27037 = (tuple_index_t_index_t){._1=0, ._2=0};
  tuple_index_t_index_t x26527 = x27037;
  for (int x19711 = 0; x19711 < x26526; x19711++) {
    tuple_index_t_index_t x19710 = x26527;
    index_t x26519 = (x19710)._1;
    number_t x26520 = (alphas->arr[x26519]);
    number_t x26521 = (alphas->arr[x19711]);
    index_t x26522 = (x26520) > (x26521);
    tuple_index_t_index_t x26524;
    if (x26522) {
      x26524 = x19710;
    } else {
      tuple_index_t_index_t x26523 = (tuple_index_t_index_t){._1=x19711, ._2=0};
      x26524 = x26523;
    }
    x19710 = x26524;
    x26527 = x19710;
  }
  
  index_t x26528 = (x26527)._1;
  tuple_number_t_index_t x27040 = (tuple_number_t_index_t){._1=0, ._2=0};
  tuple_number_t_index_t x26564 = x27040;
  for (int x19751 = 0; x19751 < x26526; x19751++) {
    tuple_number_t_index_t x19750 = x26564;
    array_number_t x26529 = (ls->arr[x19751]);
    array_number_t x26530 = (qs->arr[x19751]);
    index_t x26539 = (x26530)->length;
    tuple_number_t_index_t x27038 = (tuple_number_t_index_t){._1=0, ._2=0};
    tuple_number_t_index_t x26540 = x27038;
    for (int x19849 = 0; x19849 < x26539; x19849++) {
      tuple_number_t_index_t x19848 = x26540;
      number_t x26531 = (x26530->arr[x19849]);
      number_t x26532 = exp(x26531);
      number_t x26533 = (x19848)._1;
      number_t x26534 = (x26532) * (x26532);
      number_t x26535 = (x26533) + (x26534);
      index_t x26536 = (x19848)._2;
      tuple_number_t_index_t x26537 = (tuple_number_t_index_t){._1=x26535, ._2=x26536};
      x19848 = x26537;
      x26540 = x19848;
    }
    
    index_t x26549 = (x26529)->length;
    tuple_number_t_index_t x27039 = (tuple_number_t_index_t){._1=0, ._2=0};
    tuple_number_t_index_t x26550 = x27039;
    for (int x19845 = 0; x19845 < x26549; x19845++) {
      tuple_number_t_index_t x19844 = x26550;
      number_t x26541 = (x19844)._1;
      number_t x26542 = (x26529->arr[x19845]);
      number_t x26544 = (x26542) * (x26542);
      number_t x26545 = (x26541) + (x26544);
      index_t x26546 = (x19844)._2;
      tuple_number_t_index_t x26547 = (tuple_number_t_index_t){._1=x26545, ._2=x26546};
      x19844 = x26547;
      x26550 = x19844;
    }
    
    number_t x26551 = (x19750)._1;
    number_t x26552 = (x26540)._1;
    number_t x26553 = (x26550)._1;
    number_t x26554 = (x26552) + (x26553);
    number_t x26555 = (x26551) + (x26554);
    index_t x26556 = (x19750)._2;
    index_t x26557 = (x26540)._2;
    index_t x26558 = (x26550)._2;
    index_t x26559 = (x26557) + (x26558);
    index_t x26560 = (x26556) + (x26559);
    tuple_number_t_index_t x26561 = (tuple_number_t_index_t){._1=x26555, ._2=x26560};
    x19750 = x26561;
    x26564 = x19750;
  }
  
  array_number_t x27036 = (array_number_t)storage_alloc(sizeof(int) * 2);x27036->length=x26526;x27036->arr = (number_t*)storage_alloc(sizeof(number_t) * x26526);
  for(int i = 0; i < x27036->length; i++){
    tuple_number_t_number_t x27055 = (tuple_number_t_number_t){._1=0, ._2=0};
    tuple_number_t_number_t x26991 = x27055;
    for (int x19767 = 0; x19767 < x26516; x19767++) {
      tuple_number_t_number_t x19766 = x26991;
      array_number_t x26566 = (x->arr[x19767]);
      tuple_index_t_index_t x27047 = (tuple_index_t_index_t){._1=0, ._2=0};
      tuple_index_t_index_t x26731 = x27047;
      for (int x19841 = 0; x19841 < x26526; x19841++) {
        tuple_index_t_index_t x19840 = x26731;
        index_t x26570 = (x19840)._1;
        array_number_t x26571 = (qs->arr[x26570]);
        array_number_t x26573 = (ls->arr[x26570]);
        array_number_t x26574 = (ls->arr[x19841]);
        array_number_t x26575 = (qs->arr[x19841]);
        number_t x26577 = (alphas->arr[x26570]);
        index_t x26584 = (x26571)->length;
        tuple_number_t_index_t x27041 = (tuple_number_t_index_t){._1=0, ._2=0};
        tuple_number_t_index_t x26585 = x27041;
        for (int x20067 = 0; x20067 < x26584; x20067++) {
          tuple_number_t_index_t x20066 = x26585;
          number_t x26578 = (x20066)._1;
          number_t x26579 = (x26571->arr[x20067]);
          number_t x26580 = (x26578) + (x26579);
          index_t x26581 = (x20066)._2;
          tuple_number_t_index_t x26582 = (tuple_number_t_index_t){._1=x26580, ._2=x26581};
          x20066 = x26582;
          x26585 = x20066;
        }
        
        number_t x26586 = (x26585)._1;
        number_t x26587 = (x26577) + (x26586);
        index_t x26648 = (x26566)->length;
        tuple_number_t_number_t x27043 = (tuple_number_t_number_t){._1=0, ._2=0};
        tuple_number_t_number_t x26649 = x27043;
        for (int x20063 = 0; x20063 < x26648; x20063++) {
          tuple_number_t_number_t x20062 = x26649;
          index_t x26588 = (x20063) - (1);
          index_t x26590 = (x26588) + (1);
          number_t x26593 = (x26571->arr[x20063]);
          number_t x26594 = exp(x26593);
          number_t x26595 = (x26566->arr[x20063]);
          array_number_t x26597 = (means->arr[x26570]);
          number_t x26598 = (x26597->arr[x20063]);
          number_t x26599 = (x26595) - (x26598);
          index_t x26628 = (x26573)->length;
          tuple_number_t_index_t x27042 = (tuple_number_t_index_t){._1=0, ._2=0};
          tuple_number_t_index_t x26629 = x27042;
          for (int x20271 = 0; x20271 < x26628; x20271++) {
            tuple_number_t_index_t x20270 = x26629;
            index_t x26600 = (x26588) * (x26590);
            index_t x26601 = (x26600) / (2);
            index_t x26602 = (x20271) - (x26601);
            index_t x26603 = (x26602) >= (0);
            index_t x26608;
            if (x26603) {
              index_t x26607 = (x26602) < (x20063);
              x26608 = x26607;
            } else {
              x26608 = 0;
            }
            tuple_number_t_index_t x26626;
            if (x26608) {
              number_t x26609 = (x20270)._1;
              number_t x26610 = (x26573->arr[x20271]);
              number_t x26614 = (x26566->arr[x26602]);
              number_t x26620 = (x26597->arr[x26602]);
              number_t x26621 = (x26614) - (x26620);
              number_t x26622 = (x26610) * (x26621);
              number_t x26623 = (x26609) + (x26622);
              index_t x26624 = (x20270)._2;
              tuple_number_t_index_t x26625 = (tuple_number_t_index_t){._1=x26623, ._2=x26624};
              x26626 = x26625;
            } else {
              x26626 = x20270;
            }
            x20270 = x26626;
            x26629 = x20270;
          }
          
          number_t x26630 = (x26629)._1;
          number_t x26631 = (x26594) * (x26599);
          number_t x26632 = (x26630) + (x26631);
          number_t x26636 = (x20062)._1;
          number_t x26637 = (x26632) * (x26632);
          number_t x26638 = (x26636) + (x26637);
          number_t x26639 = (x20062)._2;
          index_t x26640 = (x26629)._2;
          number_t x26641 = (x26640) * (x26632);
          number_t x26643 = (x26632) * (x26640);
          number_t x26644 = (x26641) + (x26643);
          number_t x26645 = (x26639) + (x26644);
          tuple_number_t_number_t x26646 = (tuple_number_t_number_t){._1=x26638, ._2=x26645};
          x20062 = x26646;
          x26649 = x20062;
        }
        
        number_t x26650 = (x26649)._1;
        number_t x26651 = (0.5) * (x26650);
        number_t x26652 = (x26587) - (x26651);
        number_t x26653 = (alphas->arr[x19841]);
        index_t x26660 = (x26575)->length;
        tuple_number_t_index_t x27044 = (tuple_number_t_index_t){._1=0, ._2=0};
        tuple_number_t_index_t x26661 = x27044;
        for (int x20075 = 0; x20075 < x26660; x20075++) {
          tuple_number_t_index_t x20074 = x26661;
          number_t x26654 = (x20074)._1;
          number_t x26655 = (x26575->arr[x20075]);
          number_t x26656 = (x26654) + (x26655);
          index_t x26657 = (x20074)._2;
          tuple_number_t_index_t x26658 = (tuple_number_t_index_t){._1=x26656, ._2=x26657};
          x20074 = x26658;
          x26661 = x20074;
        }
        
        number_t x26662 = (x26661)._1;
        number_t x26663 = (x26653) + (x26662);
        tuple_number_t_number_t x27046 = (tuple_number_t_number_t){._1=0, ._2=0};
        tuple_number_t_number_t x26722 = x27046;
        for (int x20071 = 0; x20071 < x26648; x20071++) {
          tuple_number_t_number_t x20070 = x26722;
          index_t x26664 = (x20071) - (1);
          index_t x26666 = (x26664) + (1);
          number_t x26668 = (x26575->arr[x20071]);
          number_t x26669 = exp(x26668);
          number_t x26670 = (x26566->arr[x20071]);
          array_number_t x26671 = (means->arr[x19841]);
          number_t x26672 = (x26671->arr[x20071]);
          number_t x26673 = (x26670) - (x26672);
          index_t x26701 = (x26574)->length;
          tuple_number_t_index_t x27045 = (tuple_number_t_index_t){._1=0, ._2=0};
          tuple_number_t_index_t x26702 = x27045;
          for (int x20299 = 0; x20299 < x26701; x20299++) {
            tuple_number_t_index_t x20298 = x26702;
            index_t x26674 = (x26664) * (x26666);
            index_t x26675 = (x26674) / (2);
            index_t x26676 = (x20299) - (x26675);
            index_t x26677 = (x26676) >= (0);
            index_t x26682;
            if (x26677) {
              index_t x26681 = (x26676) < (x20071);
              x26682 = x26681;
            } else {
              x26682 = 0;
            }
            tuple_number_t_index_t x26699;
            if (x26682) {
              number_t x26683 = (x20298)._1;
              number_t x26684 = (x26574->arr[x20299]);
              number_t x26688 = (x26566->arr[x26676]);
              number_t x26693 = (x26671->arr[x26676]);
              number_t x26694 = (x26688) - (x26693);
              number_t x26695 = (x26684) * (x26694);
              number_t x26696 = (x26683) + (x26695);
              index_t x26697 = (x20298)._2;
              tuple_number_t_index_t x26698 = (tuple_number_t_index_t){._1=x26696, ._2=x26697};
              x26699 = x26698;
            } else {
              x26699 = x20298;
            }
            x20298 = x26699;
            x26702 = x20298;
          }
          
          number_t x26703 = (x26702)._1;
          number_t x26704 = (x26669) * (x26673);
          number_t x26705 = (x26703) + (x26704);
          number_t x26709 = (x20070)._1;
          number_t x26710 = (x26705) * (x26705);
          number_t x26711 = (x26709) + (x26710);
          number_t x26712 = (x20070)._2;
          index_t x26713 = (x26702)._2;
          number_t x26714 = (x26713) * (x26705);
          number_t x26716 = (x26705) * (x26713);
          number_t x26717 = (x26714) + (x26716);
          number_t x26718 = (x26712) + (x26717);
          tuple_number_t_number_t x26719 = (tuple_number_t_number_t){._1=x26711, ._2=x26718};
          x20070 = x26719;
          x26722 = x20070;
        }
        
        number_t x26723 = (x26722)._1;
        number_t x26724 = (0.5) * (x26723);
        number_t x26725 = (x26663) - (x26724);
        index_t x26726 = (x26652) > (x26725);
        tuple_index_t_index_t x26728;
        if (x26726) {
          x26728 = x19840;
        } else {
          tuple_index_t_index_t x26727 = (tuple_index_t_index_t){._1=x19841, ._2=0};
          x26728 = x26727;
        }
        x19840 = x26728;
        x26731 = x19840;
      }
      
      index_t x26732 = (x26731)._1;
      array_number_t x26734 = (ls->arr[x26732]);
      array_number_t x26736 = (qs->arr[x26732]);
      index_t x26743 = (x26736)->length;
      tuple_number_t_index_t x27048 = (tuple_number_t_index_t){._1=0, ._2=0};
      tuple_number_t_index_t x26744 = x27048;
      for (int x19969 = 0; x19969 < x26743; x19969++) {
        tuple_number_t_index_t x19968 = x26744;
        number_t x26737 = (x19968)._1;
        number_t x26738 = (x26736->arr[x19969]);
        number_t x26739 = (x26737) + (x26738);
        index_t x26740 = (x19968)._2;
        tuple_number_t_index_t x26741 = (tuple_number_t_index_t){._1=x26739, ._2=x26740};
        x19968 = x26741;
        x26744 = x19968;
      }
      
      index_t x26805 = (x26566)->length;
      tuple_number_t_number_t x27050 = (tuple_number_t_number_t){._1=0, ._2=0};
      tuple_number_t_number_t x26806 = x27050;
      for (int x19965 = 0; x19965 < x26805; x19965++) {
        tuple_number_t_number_t x19964 = x26806;
        index_t x26745 = (x19965) - (1);
        index_t x26746 = (x26745) + (1);
        number_t x26749 = (x26736->arr[x19965]);
        number_t x26750 = exp(x26749);
        number_t x26751 = (x26566->arr[x19965]);
        array_number_t x26753 = (means->arr[x26732]);
        number_t x26754 = (x26753->arr[x19965]);
        number_t x26755 = (x26751) - (x26754);
        index_t x26785 = (x26734)->length;
        tuple_number_t_index_t x27049 = (tuple_number_t_index_t){._1=0, ._2=0};
        tuple_number_t_index_t x26786 = x27049;
        for (int x20151 = 0; x20151 < x26785; x20151++) {
          tuple_number_t_index_t x20150 = x26786;
          index_t x26757 = (x26745) * (x26746);
          index_t x26758 = (x26757) / (2);
          index_t x26759 = (x20151) - (x26758);
          index_t x26760 = (x26759) >= (0);
          index_t x26765;
          if (x26760) {
            index_t x26764 = (x26759) < (x19965);
            x26765 = x26764;
          } else {
            x26765 = 0;
          }
          tuple_number_t_index_t x26783;
          if (x26765) {
            number_t x26766 = (x20150)._1;
            number_t x26767 = (x26734->arr[x20151]);
            number_t x26771 = (x26566->arr[x26759]);
            number_t x26777 = (x26753->arr[x26759]);
            number_t x26778 = (x26771) - (x26777);
            number_t x26779 = (x26767) * (x26778);
            number_t x26780 = (x26766) + (x26779);
            index_t x26781 = (x20150)._2;
            tuple_number_t_index_t x26782 = (tuple_number_t_index_t){._1=x26780, ._2=x26781};
            x26783 = x26782;
          } else {
            x26783 = x20150;
          }
          x20150 = x26783;
          x26786 = x20150;
        }
        
        number_t x26787 = (x26786)._1;
        number_t x26788 = (x26750) * (x26755);
        number_t x26789 = (x26787) + (x26788);
        number_t x26793 = (x19964)._1;
        number_t x26794 = (x26789) * (x26789);
        number_t x26795 = (x26793) + (x26794);
        number_t x26796 = (x19964)._2;
        index_t x26797 = (x26786)._2;
        number_t x26798 = (x26797) * (x26789);
        number_t x26800 = (x26789) * (x26797);
        number_t x26801 = (x26798) + (x26800);
        number_t x26802 = (x26796) + (x26801);
        tuple_number_t_number_t x26803 = (tuple_number_t_number_t){._1=x26795, ._2=x26802};
        x19964 = x26803;
        x26806 = x19964;
      }
      
      tuple_number_t_number_t x27054 = (tuple_number_t_number_t){._1=0, ._2=0};
      tuple_number_t_number_t x26953 = x27054;
      for (int x19999 = 0; x19999 < x26526; x19999++) {
        tuple_number_t_number_t x19998 = x26953;
        array_number_t x26807 = (qs->arr[x19999]);
        index_t x26814 = (x26807)->length;
        tuple_number_t_index_t x27051 = (tuple_number_t_index_t){._1=0, ._2=0};
        tuple_number_t_index_t x26815 = x27051;
        for (int x20459 = 0; x20459 < x26814; x20459++) {
          tuple_number_t_index_t x20458 = x26815;
          number_t x26808 = (x20458)._1;
          number_t x26809 = (x26807->arr[x20459]);
          number_t x26810 = (x26808) + (x26809);
          index_t x26811 = (x20458)._2;
          tuple_number_t_index_t x26812 = (tuple_number_t_index_t){._1=x26810, ._2=x26811};
          x20458 = x26812;
          x26815 = x20458;
        }
        
        array_number_t x26816 = (ls->arr[x19999]);
        tuple_number_t_number_t x27053 = (tuple_number_t_number_t){._1=0, ._2=0};
        tuple_number_t_number_t x26875 = x27053;
        for (int x20455 = 0; x20455 < x26805; x20455++) {
          tuple_number_t_number_t x20454 = x26875;
          index_t x26817 = (x20455) - (1);
          index_t x26819 = (x26817) + (1);
          number_t x26821 = (x26807->arr[x20455]);
          number_t x26822 = exp(x26821);
          number_t x26823 = (x26566->arr[x20455]);
          array_number_t x26824 = (means->arr[x19999]);
          number_t x26825 = (x26824->arr[x20455]);
          number_t x26826 = (x26823) - (x26825);
          index_t x26854 = (x26816)->length;
          tuple_number_t_index_t x27052 = (tuple_number_t_index_t){._1=0, ._2=0};
          tuple_number_t_index_t x26855 = x27052;
          for (int x20727 = 0; x20727 < x26854; x20727++) {
            tuple_number_t_index_t x20726 = x26855;
            index_t x26827 = (x26817) * (x26819);
            index_t x26828 = (x26827) / (2);
            index_t x26829 = (x20727) - (x26828);
            index_t x26830 = (x26829) >= (0);
            index_t x26835;
            if (x26830) {
              index_t x26834 = (x26829) < (x20455);
              x26835 = x26834;
            } else {
              x26835 = 0;
            }
            tuple_number_t_index_t x26852;
            if (x26835) {
              number_t x26836 = (x20726)._1;
              number_t x26837 = (x26816->arr[x20727]);
              number_t x26841 = (x26566->arr[x26829]);
              number_t x26846 = (x26824->arr[x26829]);
              number_t x26847 = (x26841) - (x26846);
              number_t x26848 = (x26837) * (x26847);
              number_t x26849 = (x26836) + (x26848);
              index_t x26850 = (x20726)._2;
              tuple_number_t_index_t x26851 = (tuple_number_t_index_t){._1=x26849, ._2=x26850};
              x26852 = x26851;
            } else {
              x26852 = x20726;
            }
            x20726 = x26852;
            x26855 = x20726;
          }
          
          number_t x26856 = (x26855)._1;
          number_t x26857 = (x26822) * (x26826);
          number_t x26858 = (x26856) + (x26857);
          number_t x26862 = (x20454)._1;
          number_t x26863 = (x26858) * (x26858);
          number_t x26864 = (x26862) + (x26863);
          number_t x26865 = (x20454)._2;
          index_t x26866 = (x26855)._2;
          number_t x26867 = (x26866) * (x26858);
          number_t x26869 = (x26858) * (x26866);
          number_t x26870 = (x26867) + (x26869);
          number_t x26871 = (x26865) + (x26870);
          tuple_number_t_number_t x26872 = (tuple_number_t_number_t){._1=x26864, ._2=x26871};
          x20454 = x26872;
          x26875 = x20454;
        }
        
        number_t x26876 = (alphas->arr[x19999]);
        number_t x26877 = (x26815)._1;
        number_t x26878 = (x26876) + (x26877);
        number_t x26879 = (x26875)._1;
        number_t x26880 = (0.5) * (x26879);
        number_t x26881 = (x26878) - (x26880);
        number_t x26882 = (alphas->arr[x26732]);
        number_t x26883 = (x26744)._1;
        number_t x26884 = (x26882) + (x26883);
        number_t x26885 = (x26806)._1;
        number_t x26886 = (0.5) * (x26885);
        number_t x26887 = (x26884) - (x26886);
        number_t x26888 = (x26881) - (x26887);
        number_t x26889 = exp(x26888);
        number_t x26890 = (x19998)._1;
        number_t x26891 = (x26890) + (x26889);
        index_t x26892 = (i) == (x19999);
        number_t x26949;
        if (x26892) {
          index_t x26893 = (i) == (x26732);
          number_t x26921;
          if (x26893) {
            number_t x26894 = (x19998)._2;
            index_t x26895 = (x26815)._2;
            index_t x26896 = (1) + (x26895);
            number_t x26897 = (x26875)._2;
            number_t x26898 = (0.5) * (x26897);
            number_t x26899 = (x26896) - (x26898);
            index_t x26900 = (x26744)._2;
            index_t x26901 = (1) + (x26900);
            number_t x26902 = (x26806)._2;
            number_t x26903 = (0.5) * (x26902);
            number_t x26904 = (x26901) - (x26903);
            number_t x26905 = (x26899) - (x26904);
            number_t x26906 = (x26905) * (x26889);
            number_t x26907 = (x26894) + (x26906);
            x26921 = x26907;
          } else {
            number_t x26908 = (x19998)._2;
            index_t x26909 = (x26815)._2;
            index_t x26910 = (1) + (x26909);
            number_t x26911 = (x26875)._2;
            number_t x26912 = (0.5) * (x26911);
            number_t x26913 = (x26910) - (x26912);
            index_t x26914 = (x26744)._2;
            number_t x26915 = (x26806)._2;
            number_t x26916 = (0.5) * (x26915);
            number_t x26917 = (x26914) - (x26916);
            number_t x26918 = (x26913) - (x26917);
            number_t x26919 = (x26918) * (x26889);
            number_t x26920 = (x26908) + (x26919);
            x26921 = x26920;
          }
          x26949 = x26921;
        } else {
          index_t x26922 = (i) == (x26732);
          number_t x26948;
          if (x26922) {
            number_t x26923 = (x19998)._2;
            index_t x26924 = (x26815)._2;
            number_t x26925 = (x26875)._2;
            number_t x26926 = (0.5) * (x26925);
            number_t x26927 = (x26924) - (x26926);
            index_t x26928 = (x26744)._2;
            index_t x26929 = (1) + (x26928);
            number_t x26930 = (x26806)._2;
            number_t x26931 = (0.5) * (x26930);
            number_t x26932 = (x26929) - (x26931);
            number_t x26933 = (x26927) - (x26932);
            number_t x26934 = (x26933) * (x26889);
            number_t x26935 = (x26923) + (x26934);
            x26948 = x26935;
          } else {
            number_t x26936 = (x19998)._2;
            index_t x26937 = (x26815)._2;
            number_t x26938 = (x26875)._2;
            number_t x26939 = (0.5) * (x26938);
            number_t x26940 = (x26937) - (x26939);
            index_t x26941 = (x26744)._2;
            number_t x26942 = (x26806)._2;
            number_t x26943 = (0.5) * (x26942);
            number_t x26944 = (x26941) - (x26943);
            number_t x26945 = (x26940) - (x26944);
            number_t x26946 = (x26945) * (x26889);
            number_t x26947 = (x26936) + (x26946);
            x26948 = x26947;
          }
          x26949 = x26948;
        }
        tuple_number_t_number_t x26950 = (tuple_number_t_number_t){._1=x26891, ._2=x26949};
        x19998 = x26950;
        x26953 = x19998;
      }
      
      number_t x26954 = (x19766)._1;
      number_t x26955 = (x26953)._1;
      number_t x26956 = log(x26955);
      number_t x26957 = (alphas->arr[x26732]);
      number_t x26958 = (x26744)._1;
      number_t x26959 = (x26957) + (x26958);
      number_t x26960 = (x26806)._1;
      number_t x26961 = (0.5) * (x26960);
      number_t x26962 = (x26959) - (x26961);
      number_t x26963 = (x26956) + (x26962);
      number_t x26964 = (x26954) + (x26963);
      index_t x26965 = (i) == (x26732);
      number_t x26987;
      if (x26965) {
        number_t x26966 = (x19766)._2;
        number_t x26967 = (x26953)._2;
        number_t x26969 = (x26967) / (x26955);
        index_t x26970 = (x26744)._2;
        index_t x26971 = (1) + (x26970);
        number_t x26972 = (x26806)._2;
        number_t x26973 = (0.5) * (x26972);
        number_t x26974 = (x26971) - (x26973);
        number_t x26975 = (x26969) + (x26974);
        number_t x26976 = (x26966) + (x26975);
        x26987 = x26976;
      } else {
        number_t x26977 = (x19766)._2;
        number_t x26978 = (x26953)._2;
        number_t x26980 = (x26978) / (x26955);
        index_t x26981 = (x26744)._2;
        number_t x26982 = (x26806)._2;
        number_t x26983 = (0.5) * (x26982);
        number_t x26984 = (x26981) - (x26983);
        number_t x26985 = (x26980) + (x26984);
        number_t x26986 = (x26977) + (x26985);
        x26987 = x26986;
      }
      tuple_number_t_number_t x26988 = (tuple_number_t_number_t){._1=x26964, ._2=x26987};
      x19766 = x26988;
      x26991 = x19766;
    }
    
    tuple_number_t_number_t x27056 = (tuple_number_t_number_t){._1=0, ._2=0};
    tuple_number_t_number_t x27014 = x27056;
    for (int x19785 = 0; x19785 < x26526; x19785++) {
      tuple_number_t_number_t x19784 = x27014;
      number_t x26992 = (alphas->arr[x19785]);
      number_t x26993 = (alphas->arr[x26528]);
      number_t x26994 = (x26992) - (x26993);
      number_t x26995 = exp(x26994);
      number_t x26996 = (x19784)._1;
      number_t x26997 = (x26996) + (x26995);
      index_t x26998 = (i) == (x19785);
      number_t x27010;
      if (x26998) {
        index_t x26999 = (i) == (x26528);
        number_t x27003;
        if (x26999) {
          number_t x27000 = (x19784)._2;
          x27003 = x27000;
        } else {
          number_t x27001 = (x19784)._2;
          number_t x27002 = (x27001) + (x26995);
          x27003 = x27002;
        }
        x27010 = x27003;
      } else {
        index_t x27004 = (i) == (x26528);
        number_t x27009;
        if (x27004) {
          number_t x27005 = (x19784)._2;
          number_t x27006 = (-1) * (x26995);
          number_t x27007 = (x27005) + (x27006);
          x27009 = x27007;
        } else {
          number_t x27008 = (x19784)._2;
          x27009 = x27008;
        }
        x27010 = x27009;
      }
      tuple_number_t_number_t x27011 = (tuple_number_t_number_t){._1=x26997, ._2=x27010};
      x19784 = x27011;
      x27014 = x19784;
    }
    
    index_t x27015 = (i) == (x26528);
    number_t x27035;
    if (x27015) {
      number_t x27016 = (x26991)._2;
      number_t x27017 = (x27014)._2;
      number_t x27018 = (x27014)._1;
      number_t x27019 = (x27017) / (x27018);
      number_t x27020 = (x27019) + (1);
      number_t x27021 = (x26518) * (x27020);
      number_t x27022 = (x27016) - (x27021);
      index_t x27023 = (x26564)._2;
      number_t x27024 = (0.5) * (x27023);
      number_t x27025 = (x27022) + (x27024);
      x27035 = x27025;
    } else {
      number_t x27026 = (x26991)._2;
      number_t x27027 = (x27014)._2;
      number_t x27028 = (x27014)._1;
      number_t x27029 = (x27027) / (x27028);
      number_t x27030 = (x26518) * (x27029);
      number_t x27031 = (x27026) - (x27030);
      index_t x27032 = (x26564)._2;
      number_t x27033 = (0.5) * (x27032);
      number_t x27034 = (x27031) + (x27033);
      x27035 = x27034;
    }
    x27036->arr[i] = x27035;
    
  }
  return x27036;
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
#elif defined TAPENADE

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
  array_number_t alphas_b = vector_fill(K, 0);
  array_number_t means_b = vector_fill(K * d, 0);
  array_number_t qs_b = vector_fill(K * d, 0);
  array_number_t ls_b = vector_fill(K * td, 0);
  array_number_t icf_b = vector_fill(K * td, 0);
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
  array_array_number_t xsd = matrix_fill(n, d, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < d; ++j)
      xs->arr[i]->arr[j] = dist(rng);
  array_number_t alphasd = vector_fill(K, 0);
  array_array_number_t meansd = matrix_fill(K, d, 0);
  array_array_number_t qsd = matrix_fill(K, d, 0);
  array_array_number_t lsd = matrix_fill(K, td, 0);
#endif

  // TOP_LEVEL_usecases_gmm_Qtimesv_test(0);

  // boost::timer::auto_cpu_timer t;
  timer_t t = tic();

  // gmm_init(d, K, n);

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
    
    #if defined REV_MODE
      // gmm_objective_b(d, K, n, alphas->arr, alphas_b->arr, means->arr, icf->arr, xs->arr, wishart_gamma, wishart_m, &tmp, &res);
      double eb = 1;
      gmm_objective_b(d, K, n, alphas->arr, alphas_b->arr, means->arr, means_b->arr, icf->arr, icf_b->arr, xs->arr, xsd->arr, wishart_gamma, wishart_m, &tmp, &eb);
      res = vector_sum(alphas_b);
    // #elif defined MULT_MODE
    //   gmm_objective_dv(d, K, n, alphas->arr, alphas->arr, means->arr, means->arr, icf->arr, icf->arr, xs->arr, xsd->arr, wishart_gamma, wishart_m, &tmp, &res);
    #else
      for(int i = 0; i<K; i++) {
        double res1;
        alphas_b->arr[i] = 1;
        gmm_objective_d(d, K, n, alphas->arr, alphas_b->arr, means->arr, means->arr, icf->arr, icf->arr, xs->arr, xsd->arr, wishart_gamma, wishart_m, &tmp, &res1);
        alphas_b->arr[i] = 0;
        res += res1;
      }
    #endif
#else
    // res = gmm_objective3(xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
    // res = gmm_objective_d(xs, alphas, means, qs, ls, wishart_gamma, wishart_m, xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
    // res = gmm_objective3_d(xs, alphas, means, qs, ls, wishart_gamma, wishart_m, alphas, means, qs, ls);
    #if defined MULT_MODE
      res = vector_sum(gmm_objective3_d_alphas_1(xs, alphas, means, qs, ls, wishart_gamma, wishart_m));
      // TODO seems to be buggy!
    #elif (defined TAP_FUSED || defined TAP_UNFUSED) && (defined REV_MODE)
      double eb = 1;
      gmm_objective_b(xs, xsd, alphas, alphasd, means, meansd, qs, qsd, ls, lsd, wishart_gamma, wishart_m, eb);
      res = vector_sum(alphasd);
    // #elif defined TAP_UNFUSED
    //   res = gmm_objective(xs, alphas, means, qs, ls, wishart_gamma, wishart_m);
    #else
      for(int i = 0; i<K; i++) {
        double res1;
        alphasd->arr[i] = 1;
        #if defined TAP_FUSED || TAP_UNFUSED // FORWARD MODE
          res1 = gmm_objective_d(xs, xsd, alphas, alphasd, means, means, qs, qs, ls, ls, wishart_gamma, wishart_m, &tmp);
        #else
          res1 = gmm_objective3_d(xs, alphas, means, qs, ls, wishart_gamma, wishart_m, alphasd, means, qs, ls);
        #endif
        alphasd->arr[i] = 0;
        res += res1;
      }
    #endif
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


