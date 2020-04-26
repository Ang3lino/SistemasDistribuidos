
import math 


seno = 0
coseno = 0 
tangente = 0;
raizCuad = 0;
logaritmo = 0
max_ = 10e7;
max_ = int(max_)
for i in range(1, max_):
    seno += math.sin(i);
    coseno += math.cos(i);
    tangente += math.tan(i);
    logaritmo += math.log(i);
    raizCuad += math.sqrt(i);