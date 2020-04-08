import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;

public class Generator {
    public float[] x, y;
    private int n = 1;

    private double sampling(double x) {
        if (x == 0) 
            return 1.0;
        return Math.sin(x) / x;
    }

    // T = 64, A = 16, d = 32
    private double fourierCoefficient(double t, int n) {
        double p = (32 / (Math.PI * n)) * sampling(Math.PI * n / 2) - 1;
        double q = Math.sin((Math.PI * n / 32) * t);
        return p*q;
    }

    public Generator(float min, float max, int n) {
        x = linspace(min, max, n);
        y = new float[n];
        Arrays.fill(y, 0);
    }

    public static float[] linspace(float min, float max, int points) {  
        float[] d = new float[points];  
        for (int i = 0; i < points; i++){  
            d[i] = min + i * (max - min) / (points - 1);  
        }  
        return d;  
    }  

    public void increment () {
        for (int i = 0; i < x.length; ++i) {
            y[i] += fourierCoefficient(x[i], n);
        }
        ++n;
    }
}
