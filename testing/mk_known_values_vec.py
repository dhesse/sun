import numpy as np
a = np.matrix((np.random.random(9) + np.random.random(9)*(0 + 1J)).reshape(3,3))
for i in range(3):
   for j in range(3):
     print "  A({0},{1}) = cplx({2:.16f},{3:.16f});".format(i,j, a[i,j].real, a[i,j].imag)
b = np.matrix((np.random.random(3) + np.random.random(3)*(0 + 1J)).reshape(3))
for i in range(3):
   print "  B({0}) = cplx({1:.16f},{2:.16f});".format(i, b[0,i].real, b[0,i].imag)
c = np.dot(b,a)
for i in range(3):
   print "  C({0}) = cplx({1:.16f},{2:.16f});".format(i, c[0,i].real, c[0,i].imag)
d = np.dot(a, b.transpose())
for i in range(3):
   print "  D({0}) = cplx({1:.16f},{2:.16f});".format(i, d[i,0].real, d[i,0].imag)
