import math
import random

N = 3
def norm(x,mu,delta):
	return (1/(math.sqrt(2*math.pi*delta)))*math.exp(-(x - mu)**2/(2*delta))

def Px_z(x,z): #calculate the P(X|Z)
	return norm(x,u[z],delta[z])

def Pz_x(z,x): #calculate the P(Z|X)
	up = Px_z(x,z) * theta[z]
	sum = 0
	for i in range(N):
		sum += (Px_z(x,i) * theta[i])
	return up/sum

def Px(x): #calculate the P(x)
	sum = 0
	for i in range(N):
		sum += (theta[i] * Px_z(x,i))
	return sum
	
fx = open('result_x.txt','r+')
result_x = []
for line in fx:
	result_x = line.split()

result_x = list(map(float,result_x))

iter = 6000
theta = []
u = []
delta = []

#para_dic = {}
#para_ls = []

#initiate
for i in range(N):
	theta.append(random.uniform(0,100))
	u.append(random.uniform(0,50))
	delta.append(random.uniform(1,50))
total = sum(theta)
theta = [float(i)/total for i in theta]

#tht EM algorithm
flag = True
t = 0
threshold = 0.000000001
fw = open('PE.txt','w')

while flag and t < iter:
	if t % 200 == 0:
		fw.write('iter '+str(t)+':\n')
		fw.write(' '.join([str(round(i,5)) for i in theta])+'\n')
		fw.write(' '.join([str(round(i,5)) for i in u])+'\n')
		fw.write(' '.join([str(round(i,5)) for i in delta])+'\n')
		sumP = 0
		for x in result_x:
			sumP += math.log(Px(x))
		fw.write('likelihood = '+str(sumP)+'\n')
		fw.write('\n')
	print(t)
	flag = False
	#print([round(i,5) for i in theta])
	#print([round(i,5) for i in u])
	#print([round(i,5) for i in delta])
	#the E-step
	W = []
	for z in range(N):
		ls = []
		for x in result_x:
			if type(Pz_x(z,x)) != float:
				print(type(Pz_x(z,x)))
				print(z,x,Pz_x(z,x))
			ls.append(Pz_x(z,x))
		W.append(ls)
	
	#the M-step
	for j in range(N):
		#print(type(W[j][10]))
		#print(W[j])
		total = 0
		for v in W[j]:
			total += v
		old = theta[j]
		theta[j] = (1.0/len(W[j])) * total
		#print(abs(theta[j] - old))
		if abs(theta[j] - old) > threshold:
			#print(abs(theta[j] - old))
			flag = True
		sum = 0
		for i in range(len(result_x)):
			sum += W[j][i] * result_x[i]
		old = u[j]
		u[j] = sum / total
		if abs(u[j] - old) > threshold:
			#print(abs(u[j] - old))
			flag = True
		sum = 0
		for i in range(len(result_x)):
			sum += W[j][i]*((result_x[i] - u[j])**2)
		old = delta[j]
		delta[j] = sum / total
		if abs(delta[j] - old) > threshold:
			#print(abs(delta[j] - old))
			flag = True
	t += 1

fw.write('iter '+str(t)+':\n')
fw.write(' '.join([str(round(i,5)) for i in theta])+'\n')
fw.write(' '.join([str(round(i,5)) for i in u])+'\n')
fw.write(' '.join([str(round(i,5)) for i in delta])+'\n')
sumP = 0
for x in result_x:
	sumP += math.log(Px(x))
fw.write('likelihood = '+str(sumP)+'\n')
fw.write('\n')
"""
for item in para_ls:	
	print([round(i,5) for i in item['theta']])
	print([round(i,5) for i in item['u']])
	print([round(i,5) for i in item['delta']])
"""
fw.close()
