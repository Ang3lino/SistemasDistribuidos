

public class A {
    public static void main(String args[]) {
        double seno = 0, coseno = 0, tangente = 0;
        double logaritmo = 0, raizCuad = 0;
        double max = 10e7;
        for (double i = 1; i < max; ++i) {
            seno += Math.sin(i);
            coseno += Math.cos(i);
            tangente += Math.tan(i);
            logaritmo += Math.log(i);
            raizCuad += Math.sqrt(i);
        }
    }
}