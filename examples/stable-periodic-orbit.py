from capdpy import *

vector_field = IMap("par:c;var:x,y;fun:y,c*y*(1-x^2)-x;")
vector_field.setParameter("c", Interval(2.0)/Interval(10.0))
solver = IOdeSolver(vector_field, 20)
section = ICoordinateSection(2, 1)
poincare_map = IPoincareMap(solver, section, CrossingDirection.PlusMinus)
u = IVector([Interval(2.0004136789920905), Interval(0.0)])

s0 = C0Rect2Set(u)
print(poincare_map(s0))
s1 = C1Rect2Set(u)
flowDerivative = IMatrix(2, 2)
v = poincare_map(s1, flowDerivative, 1)
poincare_map_derivative = poincare_map.computeDP(v, flowDerivative)
dPdx = poincare_map_derivative[0, 0]

s = 1e-5*Interval(-1.0, 1.0)
print(s)
C1Rect2Set(IVector([u[0]+s, Interval(0.0)])) 
flowDerivative = IMatrix(2, 2)
v = poincare_map(s1, flowDerivative, 1)
poincare_map_derivative = poincare_map.computeDP(v, flowDerivative)
subset = subset(v[0]-u[0], s)
sub = (v[0]-u[0]).subset(s)
abs_res = abs(poincare_map_derivative[0, 0])
print(sub and abs_res<1.0)
