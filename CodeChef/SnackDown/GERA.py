from math import factorial
from fractions import *

mod = int(1000 * 1000 * 1000 + 7)

def answer(w, h, s):
    total = 0 
    cycidx_cols = cycle_index(w)
    cycidx_rows = cycle_index(h)
    #print( cycidx_cols )
    #print( cycidx_rows )
    for col_coeff, col_cycle in cycidx_cols:
        for row_coeff, row_cycle in cycidx_rows:
            coeff = col_coeff * row_coeff 
            cycle = combine(col_cycle, row_cycle) 
            #print( cycle )
            value = 1
            for x, power in cycle:
                value *= (1 << power)
            total += (coeff * value) % mod 
    return total

def cycle_index(n):
    return [(coeff(term), term ) for term in gen_vars(n, n)]

def coeff(term):
    val = 1
    for x, y in term:
        val *= factorial(y) * x ** y
    return Fraction(1, val)

def gen_vars(n, lim):
    soln_set = []
    if n > 0:
        for x in range(lim, 0, -1): 
            if x == 1:
                soln_set.append([(1, n)])
            else:
                for y in xrange(int(n / x), 0, -1):
                    recurse = gen_vars(n - x * y, x - 1)
                    if len(recurse) == 0:
                        soln_set.append([(x, y)])
                    for soln in recurse:
                        soln_set.append([(x, y)] + soln)
    return soln_set

def combine(term_a, term_b):
    combined = []
    for len_a, freq_a in term_a:
        for len_b, freq_b in term_b:
            lcm = len_a * len_b / gcd(len_a, len_b)
            combined.append((lcm, int(len_a * freq_a * len_b * freq_b / lcm) ) )
    return combined

arq = open('bruxo.txt', 'w')
for x in xrange(24, 551):
    y = 1
    while y <= x and x * y <= 550:
    	ans = answer(x, y, 2) % mod
    	res = ""
    	res += str(x) + " "
    	res += str(y) + " "
    	res += str(ans)
        #res = answer(x, y, 2) % mod
        print( res )
        print >> arq, res 
        y = y + 1
arq.close()
