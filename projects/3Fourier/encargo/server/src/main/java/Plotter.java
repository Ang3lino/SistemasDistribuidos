
import java.io.IOException;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

import com.github.sh0nk.matplotlib4j.NumpyUtils;
import com.github.sh0nk.matplotlib4j.Plot;
import com.github.sh0nk.matplotlib4j.PythonExecutionException;

public class Plotter {
    static public void sleepMilliseconds(int ms) {
        try {
            TimeUnit.MILLISECONDS.sleep(ms);
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }


    public static void main(String args[]) throws IOException, PythonExecutionException  {
        List<Double> x = NumpyUtils.linspace(-3, 3, 100);
        // List<Double> y = x.stream().map(xi -> Math.sin(xi) + Math.random()).collect(Collectors.toList());
        List<Double> y = x.stream().map(xi -> 2*xi ).collect(Collectors.toList());
        Plot plt = Plot.create();

        Thread closer = new Thread(() -> {
            sleepMilliseconds(4000);
            System.out.println("Hello");
            plt.close();
        });

        plt.plot().add(x, y).label("sin");
        plt.title("scatter");
        plt.legend().loc("upper right");
        // plt.show();
        plt.executeSilently();
        System.out.println("holo");

    }
}