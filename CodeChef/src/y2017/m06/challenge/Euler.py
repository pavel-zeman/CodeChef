# Inspired by http://mathforum.org/library/drmath/view/73120.html 
def fact(x):
 res = 1
 for i in range(2, x + 1):
  res *= i
 return res


def nom(x):
 t, res = 1, 1
 while x > 0:
  t *= x;
  res += t
  x -= 1
 return res

def gcd(x, y):
 while y:
  x, y = y, x % y
 return x


def calc(n, p, q):
 t = gcd(p, q)
 p, q, s, z = p/t, q/t, 0, 1
 while q > 0 and n > 0:
  t = p / q
  s += z * t * n * (n + 1) / 2
  p -= q * t
  t = n / q
  s += z * p * t * (n + 1) - z * t * (p * q * t + p + q - 1) / 2
  n -= q * t
  t = n * p / q
  s += z * t * n
  n = t
  p, q = q, p
  z = -z
 return s
 

n = input()
print(calc(n, nom(3000), fact(3000)))