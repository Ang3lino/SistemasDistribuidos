
import os


plane_txt_name = 'Angel_Lopez_Manriquez_DSD_4CM1_3.txt'

buff = ''
for fname in os.listdir('.'):
    if fname in (plane_txt_name, __name__):
        continue
    buff += f'// {fname} ' + '-' * 90 + '\n'
    with open(fname, 'r') as f:
        buff += f.read()
    buff += '\n'
with open(plane_txt_name, 'w') as f:
    f.write(buff)
