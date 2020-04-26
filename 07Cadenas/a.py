
import random 


alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
low, high = 0, len(alpha) - 1
buff = ''
# n = int(100)
n = int(100000)
for i in range(n):
    curr = ''
    for j in range(3):
        curr += (alpha[random.randint(0, high)])
    buff += curr + ' '

if 'IPN' in buff:
    print('Si esta')
else:
    print('No esta')
