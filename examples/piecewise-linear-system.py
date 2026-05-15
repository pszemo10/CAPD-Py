from capdpy import *

vf1 = IMap("par:c;var:x,y,z;fun:y,z,1-y-0.5*x;")
vf2 = IMap("par:c;var:x,y,z;fun:y,z,1-y+0.5*x;")
solver1 = IOdeSolver(vf1, 20)
solver2 = IOdeSolver(vf2, 20)
section = ICoordinateSection(3, 0)
pm1 = IPoincareMap(solver1, section)
pm2 = IPoincareMap(solver2, section)

u = IVector([0.0, 1.3744, 0.0])
s1 = C0Rect2Set(u)
u1 = pm1(s1)
s2 = C0Rect2Set(u1)
u2 = pm2(s2)

print(u2)

e = 1e-4
s1 = C0Rect2Set(IVector([0.0, u[1]-e, 0.0]))
u1 = pm1(s1)
s2 = C0Rect2Set(u1)
u2 = pm2(s2)
zL = u2[2]

s1 = C0Rect2Set(IVector([0.0, u[1]+e, 0.0]))
u1 = pm1(s1)
s2 = C0Rect2Set(u1)
u2 = pm2(s2)
zR = u2[2]

s1 = C0Rect2Set(IVector([0.0, u[1]+Interval(-e,e), 0.0]))
u1 = pm1(s1)
s2 = C0Rect2Set(u1)
u2 = pm2(s2)
print(u2)
print("Result:", zL*zR<0)