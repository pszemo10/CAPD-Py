from capdpy import *

x0 = Interval(0.)
x1 = Interval(2.)
L = Interval(1.)
v = Interval(0.5)
vfield = IMap("par:pi,L,v;time:t;var:x,a;fun:cos((0.5*pi/L)*(t*(v*sin(a))-L))+v*cos(a),0;")
vfield.setParameter("pi", Interval.pi())
vfield.setParameter("L", L)
vfield.setParameter("v", v)
solver = IOdeSolver(vfield, 20)
tm = ITimeMap(solver)

a = Interval(1.9058939019661396)
u0 = IVector([x0, a])
s = C0HORect2Set(u0)
T = 2.0*L/(v*sin(a))
print("approximation:", tm(T, s))

print("vector field:", vfield(T, u0))

e = 1e-11
s0 = C0HORect2Set(IVector([x0, a]))
xT = tm(2.0*L/(v*sin(a)), s0)[0]-x1

A = a+Interval(-e, e)
s1 = C1HORect2Set(IVector([x0, A]))
T = 2.0*L/(v*sin(a))
z = tm(T, s1)
dT = vfield(T,z)[0]*(-2.*L/v)*cos(A)/sqr(sin(A)) + IMatrix(s1)[0][1]

N = -xT/dT
print("Bound for a:", a+N)
print("Result:", abs(N)<e)
