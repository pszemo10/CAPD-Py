from capdpy import *

vfield = IMap("par:a,b;var:x,y,z;fun:-(y+z),x+b*y,b+z*(x-a);")
vfield.setParameter("a", Interval(57.)/Interval(10.))
vfield.setParameter("b", Interval(2.)/Interval(10.))
solver = IOdeSolver(vfield, 20)
section = ICoordinateSection(3, 0)
poincare_map = IPoincareMap(solver, section, CrossingDirection.MinusPlus)

u0 = IVector([0.,-8.3809417428298,0.029590060630665])
s = C0TripletonSet(u0)
print(poincare_map(s)-u0)

s1 = C1Rect2Set(u0)
flowDerivative = IMatrix(3, 3)
v = poincare_map(s1, flowDerivative)
DP = poincare_map.computeDP(v, flowDerivative)
print(DP)

s0 = C0TripletonSet(u0)
v0 = poincare_map(s0)
r = 1e-10*Interval(-1, 1)
s1 = C1Rect2Set(IVector([0.,u0[1]+r,u0[2]+r]))
flowDerivative = IMatrix(3, 3)
v = poincare_map(s1, flowDerivative)
DP = poincare_map.computeDP(v, flowDerivative)
M = IMatrix(2, 2, [DP[1][1]-1., DP[1][2], DP[2][1], DP[2][2]-1.])
N = -gauss(M, IVector([v0[1]-u0[1], v0[2]-u0[2]]))
print("Result:", subset(N[0], r) and subset(N[1], r))

m = 0.5*(DP[1][1]+DP[2][2])
d = DP[1][1]*DP[2][2]-DP[1][2]*DP[2][1]
t = sqrt(sqr(m)-d)
print("lambda1 =", m-t)
print("lambda2 =", m+t)

