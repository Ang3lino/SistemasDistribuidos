

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

import os

from LagrangePolynomial import LagrangePolynomial
#from random import * # randint function definition


def plot(fname, x, y):
    print(x)
    print(y)
    lpol = LagrangePolynomial() 
    lpol.set_points(x, y)
    x_vals = np.linspace(1000, 80_000, 100)
    y_vals = [lpol.evaluate(xi) for xi in x_vals]
    plt.plot(x_vals, y_vals, label='lol')
    plt.title(fname)
    plt.xlabel(r'$n$')
    plt.ylabel(r'$t$ secs')
    plt.grid(True)
    plt.savefig(fname.replace('csv', '') + 'png')
    # plt.show()
    plt.close()

if __name__ == "__main__":
    for fname in os.listdir('./csv/'):
        print(fname)
        df = pd.read_csv('./csv/' + fname, delimiter=' ')
        x = (df.iloc[:, 0])  # n
        
        # data preprocessing
        y = df.iloc[:, 1]
        y = map(str, y)
        y = [y_i.replace('s', '') for y_i in y]
        y = [y_i.split('m') for y_i in y]
        y = list(map(lambda yi: int(yi[0])*60 + float(yi[1]), y))
        plot(fname, x, y)
        
# x_values = range(3, 16)
# print(x_values)

# for j in range(len(data_matrix[0])):
#     lpol = LagrangePolynomial() 
#     lpol.set_points(list(x_values), column(data_matrix, j))
#     y = [ lpol.evaluate(xi) for xi in x_values ]
#     plt.plot(x_values, y, label='fdafda')

# tags = ['LM7905', 'LM7912']
# plt.title("Regulador de voltaje fijo negativo")
# plt.xlabel("Voltaje de la fuente")
# plt.ylabel(r'Voltaje en $R_o$')
# plt.legend(tags)
# plt.grid(True) # cuadriculado
# plt.show()
