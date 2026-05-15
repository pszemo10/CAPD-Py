from capdpy import *

vfield = IMap("var:x,y,px,py;fun:px,py,-x*(1+2*y),y*(y-1)-x^2;")
solver = IOdeSolver(vfield, 15)
tm = ITimeMap(solver)

T = Interval(1.0)
x0 = Interval(1.0)
y0 = Interval(0.0)
x1 = Interval(0.0)
y1 = Interval(1.0)

px = Interval(-0.36331582018346342)
py = Interval(1.4091573668228699)

s0 = C0Rect2Set(IVector([x0, y0, px, py]))
print(tm(T, s0))

s1 = C1Rect2Set(IVector([x0, y0, px, py]))
y = tm(T, s1)
D = IMatrix(s1)
print(D)
print(gauss(D, y))

s0 = C0Rect2Set(IVector([x0, y0, px, py]))
u = tm(T, s0)
s = 1e-5*Interval(-1,1)
px += s
py += s
s1 = C1Rect2Set(IVector([x0, y0, px, py]))
tm(T, s1)
D = IMatrix(s1)
M = IMatrix(2, 2, [D[0][2], D[0][3], D[1][2], D[1][3]])
z = -gauss(M, IVector([u[0]-x1, u[1]-y1]))
print(z)
print(subset(z[0], s) and subset(z[1], s))

