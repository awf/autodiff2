#!/usr/bin/python
import numpy as np
from numpy import linalg as LA
import theano
import theano.tensor as T
import datetime
import math
import cProfile
import pstats
from theano import pp
from scipy.spatial import distance

def topLevel(m1, m2, m3):
  # res = np.empty([m1.shape[0], m1[0].shape[0]])
  # for ii in range(0, m1.shape[0]):
  #   for jj in range(0, m1[0].shape[0]):
  #     x11402 = 0.0
  #     for x11264 in range(0, (m3).shape[0]):
  #       x11630 = (m2[x11264])
  #       x11379 = 0.0
  #       for x11332 in range(0, (x11630).shape[0]):
  #         x11379 = (x11379) + (((x11630[x11332])) * (((m1[x11332])[jj])))
  #       x11632 = x11379
        
  #       x11402 = (x11402) + ((((m3[x11264])[jj])) * (((0.0) - ((x11630[ii]))) * ((1.0) * ((1.0) / ((x11632) * (x11632))))))
  #       x11402
  #     x11633 = x11402
      
  #     res[ii][jj] = x11633
  return np.dot(np.transpose(m2), ((m3 / (np.dot(m2, m1) * np.dot(m2, m1)))))
  
    
def nmf(distribution, m, n, k, sanity_check, runs):
    W = T.dmatrix('W')
    H = T.dmatrix('H')
    A = T.dmatrix('A')

    
    if distribution == "gaussian":
        lagoRuleH = theano.function([A, W, H], (H * theano.dot(T.transpose(W), A)) / theano.dot(theano.dot(T.transpose(W), W), H))
        lagoRuleW = theano.function([A, W, H], (W * theano.dot(A, T.transpose(H))) / theano.dot(W, theano.dot(H, T.transpose(H))))
    elif distribution == "exponential":
        # lagoRuleH = theano.function([A, W, H], (H * theano.dot(T.transpose(W), (A / T.pow(theano.dot(W, H), 2)))) / theano.dot(T.transpose(W), (1 / theano.dot(W, H))))
        lagoRuleH = theano.function([A, W, H], theano.dot(T.transpose(W), ((A / T.pow(theano.dot(W, H), 2)) - (1 / theano.dot(W, H)))))
        # lagoRuleH = theano.function([A, W, H], theano.dot(W, H))
        # lagoRuleW = theano.function([A, W, H], (W * theano.dot((A / T.pow(theano.dot(W, H), 2)), T.transpose(H))) / theano.dot((1 / theano.dot(W, H)), T.transpose(H)))
    elif distribution == "poisson":
        lagoRuleH = theano.function([A, W, H], (H * theano.dot(T.transpose(W), (A / theano.dot(W, H)))) / theano.dot(T.transpose(W), T.ones((m, n))))
        lagoRuleW = theano.function([A, W, H], (W * theano.dot((A / theano.dot(W, H)), T.transpose(H))) / theano.dot(T.ones((m, n)), T.transpose(H)))
    else:
        raise Exception("Distribution %s not recognized" % distribution)

    
    print "Generating matrices"
    if distribution == "gaussian":
        a = np.maximum(0, np.random.randn(m, n)) # Non-negative!
    elif distribution == "exponential":
        a = np.random.exponential(size=(m, n))
    elif distribution == "poisson":
        a = np.random.poisson(size=(m, n))        
    w = np.random.rand(m, k)
    h = np.random.rand(k, n)

    
    print "Timing Lago update of H and W"
    Hlago = h
    Wlago = w
    timesLago = []
    for i in range(runs):
        print "\tIteration %d" % (i + 1)
        pr = cProfile.Profile()
        pr.enable()
        # Hlago, Wlago = lagoRuleH(a, Wlago, Hlago), lagoRuleW(a, Wlago, Hlago)
        Hlago = lagoRuleH(a, Wlago, Hlago)
        # Hlago = topLevel(Hlago, Wlago, a)
        pr.create_stats()
        stats = pstats.Stats(pr)
        print "\t\tExecution time spent is %s." % stats.total_tt
        timesLago.append(stats.total_tt)

        
    print "Deriving Theano rules"
    Abar = theano.dot(W, H)
    if distribution == "gaussian":
        exprs = (1.0 / math.sqrt(2 * math.pi)) * T.exp(-(A - Abar)**2 / 2)
        muH = (-1*H) / (theano.dot(theano.dot(T.transpose(W), W), H))
        muW = (-1*W) / (theano.dot(W, theano.dot(H, T.transpose(H))))
    elif distribution == "exponential":
        exprs = (1/Abar) * T.exp((-1*A) / Abar)
        # muH = (-1*H) / (theano.dot(T.transpose(W) , (1/theano.dot(W, H))))
        # muW = (-1*W) / (theano.dot(1/theano.dot(W, H), T.transpose(H)))
    elif distribution == "poisson":
        exprs = T.exp(-1*Abar)*T.pow(Abar, A)
        muH = (-1*H) / theano.dot(T.transpose(W), T.ones_like(A))
        muW = (-1*W) / theano.dot(T.ones_like(A), T.transpose(H))
        
    # neglogexp = -1*T.log( T.prod(  exprs  ))
    neglogexp = T.sum(T.log(Abar) + A / Abar)
    diffH = T.grad(neglogexp, H)
    # diffW = T.grad(neglogexp, W)
    # theanoRuleH = theano.function([A, W, H], H + muH*diffH)
    theanoRuleH = theano.function([A, W, H], diffH)
    # theanoRuleW = theano.function([A, W, H], W + muW*diffW)

    
    Htheano = h
    Wtheano = w
    print "Timing Theano update of H and W"
    timesTheano = []
    total = 0.0
    for i in range(runs):
        print "\tIteration %d" % (i + 1)
        pr = cProfile.Profile()
        pr.enable()
        # Htheano, Wtheano = theanoRuleH(a, Wtheano, Htheano), theanoRuleW(a, Wtheano, Htheano)
        Htheano = theanoRuleH(a, Wtheano, Htheano)
        total += T.sum(Htheano)
        pr.create_stats()
        stats = pstats.Stats(pr)
        print "\t\tExecution time spent is %s." % stats.total_tt
        timesTheano.append(stats.total_tt)


    if sanity_check:
        print "Sanity checking:"
        d = distance.euclidean
        flatten = lambda x: np.asarray(x).reshape(-1)
        print "\tDistance between Hs: ", d(flatten(Htheano), flatten(Hlago))
        print "\tDistance between Ws: ", d(flatten(Wtheano), flatten(Wlago))
        print "\tDistance from Theano W to a random matrix: ", d(flatten(Wtheano), np.random.rand(m * k))
        print "\tDistance from Lago W to a random matrix: ", d(flatten(Wlago), np.random.rand(m * k))

    return (timesLago, timesTheano)
        

#Gaussian Distribution Prog
# Testing timing of Updating H only
# Format of m,n,k is multiplication of W_(m,k)*H_(k,n)
# -m
# -k
# -n
# -TPE is type 
# tpe:
#     
#     0: Theano
#    1: Lago-Code
def main(args):
    distribution = args[0]
    m = int(args[1])
    n = int(args[2])
    k = int(args[3])
    runs = int(args[4]) if len(args) > 4 else 1
    sanity_check = (args[5] == "check") if len(args) > 5 else False

    timesLago, timesTheano = nmf(distribution, m, n, k, sanity_check, runs)
    now = datetime.datetime.now()
    experiment_id = now.strftime("%m%d%H%M%S")

    filename = "results/%s/%s.csv" % (distribution, experiment_id)
    print "Saving results to %s" % filename
    f=open(filename, 'w+')
  
    for (l, t) in zip(timesLago, timesTheano):
        f.write("%s, %d, %d, %d, %f, %f\n" % (experiment_id, m, n, k, l, t))
    f.close()

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 3:
        print "Usage: %s <gaussian|exponential|poisson> <rows> <columns> <k> [runs] [check]" % sys.argv[0]
    else:
        main(sys.argv[1:])