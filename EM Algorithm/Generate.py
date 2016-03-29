import random

th = []
N = 3
for i in range(N):
	th.append(random.uniform(0,100))

total = sum(th)
theta = [float(i)/total for i in th]
ft = open('theta.txt','w+')
ft.write(' '.join([str(round(i,N)) for i in theta]))
ft.close()

for i in range(1,N):
	theta[i] += theta[i - 1]

result_z = []
result_x = []

for i in range(1000):
	r = random.uniform(0,1)
	z = 0
	for i in range(N):
		if theta[i] > r:
			z = i
			break
	result_z.append(z)
	if z == 0:
		x = random.gauss(3,1.5)
	elif z == 1:
		x = random.gauss(11,2)
	elif z == 2:
		x = random.gauss(15,4)
	result_x.append(x)
	
fz = open("result_z.txt","w+")
fx = open("result_x.txt","w+")

fz.write(' '.join([str(i) for i in result_z]))
fx.write(' '.join([str(i) for i in result_x]))

fz.close()
fx.close()