import sys
import math

M = 1
mods = [ 3, 5, 7, 8, 11, 13, 17 ]
phis = [ 2, 4, 6, 4, 10, 12, 16 ]

for mod in mods:
    M = M * mod

def N(mod):
    return int(M / mod);

def S(mod, phi):
    return (N(mod) ** (phi-1)) % mod;

def result(A : [list]):
    x = 0;

    for i in range(0, len(mods)):
        mod = mods[i]
        phi = phis[i]
        x = x + A[i]*N(mod)*S(mod, phi)

    return x % M


T, n, m =  list(map(int, input().split()))

for t in range(1, T+1):
    alist = list()

    for i in range(0, len(mods)):
        outstr = ""
        mod = mods[i]

        for j in range(0, 18):
            outstr = outstr + " " + str(mod)
        print(outstr)
        sys.stdout.flush()

        a = 0
        rests = list(map(int, input().split()))
        for rest in rests:
            a = (a + rest) % mod
        alist.append(a)

    print(result(alist))
    sys.stdout.flush()
    verdict = list(map(int, input().split()))

sys.exit()
