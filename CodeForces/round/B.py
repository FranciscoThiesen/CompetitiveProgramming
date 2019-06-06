from math import *

res = [1, 1]

x = int( raw_input() )

vals = map( int, raw_input().split() )

vals.sort()

for idx in range( len( vals ) ):
    if idx > 0:
        if vals[idx] == vals[idx - 1]:
            res[1] = res[1] * vals[idx]
        else:
            res[0] = res[0] * vals[idx]

print( str(res[0]) + " "),
print( res[1] )
