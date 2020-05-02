
import os 


fname = 'backup.txt'
for t in map(int, [70e3, 70e4, 70e5]):
    command = f'time ./a.out {t} {fname}'
    print(command)
    os.system(command)
    print('\n')

    