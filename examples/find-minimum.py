from capdpy import *

x0 = Interval(0.)
x1 = Interval(2.)
L = Interval(1.)
v = Interval(0.5)
k = 2.0*L/v

vfield = IMap("par:pi,L,v;time:t;var:x,a;fun:cos((0.5*pi/L)*(t*(v*sin(a))-L))+v*cos(a),0;", 2)
vfield.setParameter("pi", Interval.pi())
vfield.setParameter("L", L)
vfield.setParameter("v", v)
solver = IC2OdeSolver(vfield, 6)
tm = IC2TimeMap(solver)

a = Interval(2.4741354375614257)
u0 = IVector([x0, a])
T = k/sin(a)

s = C2Rect2Set(u0, 2.)
tm(T, s)
print("Second derivative x(T,x0) wrt to parameter:", 2*s[0, 1, 1])
vfield.setCurrentTime(0.0)
coeffs = vfield.computeODECoefficients(u0, 2)
for i in range(3):
    print("Taylor coeffs[", i, "] = ", coeffs[i], sep="")

e = 1e-12
s1 = C1HORect2Set(IVector([x0, a]))
T = k/sin(a)
z = tm(T, s1)
dg = vfield(T, z)[0]*(-k)*cos(a)/sqr(sin(a))+IMatrix(s1)[0][1]

A = a+Interval(-e, e)
s, c = sin(A), cos(A)
T = k/s
dT = -k*c/sqr(s)
d2T = k*(sqr(c)+1)/power(s,3)

s2 = C2Rect2Set(IVector([x0, a]))
z = tm(T, s2)
D = vfield.derivative(T, z)
vfield.setCurrentTime(T)
coeffs = vfield.computeODECoefficients(z, 2)
d2g = 2.0*dT*(coeffs[2][0]*dT+D[0][1])+coeffs[1][0]*d2T+2.*s2[0, 1, 1]
N = -dg/d2g

print("dg:", dg)
print("d2g:", d2g)
print("Bound for a:", a+N)
print("Bound for x1:", z[0])
print("Result:", abs(N)<e)