import numpy as np
a = np.matrix((np.random.random(9) + np.random.random(9)*(0 + 1J)).reshape(3,3))
for i in range(3):
   for j in range(3):
     print "  A({0},{1}) = cplx({2},{3});".format(i,j, a[i,j].real, a[i,j].imag)
b = np.matrix((np.random.random(9) + np.random.random(9)*(0 + 1J)).reshape(3,3))
for i in range(3):
   for j in range(3):
     print "  B({0},{1}) = cplx({2},{3});".format(i,j, b[i,j].real, b[i,j].imag)
c = np.dot(a,b)
for i in range(3):
   for j in range(3):
     print "  A({0},{1}) = cplx({2},{3});".format(i,j, c[i,j].real, c[i,j].imag)
