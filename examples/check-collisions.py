from capdpy import *

vfield = IMap("par:c;var:x,y,z;fun:y,z,c^2-y-0.5*x^2;")
vfield.setParameter("c", 0.125)
solver = IOdeSolver(vfield, 20)
tm = ITimeMap(solver)
T = Interval(100.)

solution = ISolutionCurve(0.0)
s = C0HOTripletonSet(IVector([0., -0.125, 0.]))
tm(T, s, solution)
print("solution(7) in", solution(7.))

solution = ISolutionCurve(0.0)
e = Interval(-1, 1)/10000.
s = C0HOTripletonSet(IVector([0., -0.125+e, e]))
tm(T, s, solution)

N = 200
for i in range(N):
    t = Interval(i, i+1)*T/N
    norm = solution(t).euclNorm()
    if not norm >= 0.1:
        print("Constraint not satisfied t = ", t,", norm = ", norm, sep="")
        break