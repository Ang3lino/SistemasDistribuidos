
import java.util.concurrent.TimeUnit;

import org.knowm.xchart.QuickChart;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYSeries.XYSeriesRenderStyle;
import org.knowm.xchart.style.Styler.LegendPosition;



public class Plotter {
    private static final int PUERTO = 7200; 
    private static final int CANTIDAD_MUESTRAS = Const.TAM_MAX_DATA / 8;

    static public void sleepMilliseconds(int ms) {
        try {
            TimeUnit.MILLISECONDS.sleep(ms);
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }

  public static void main(String[] args) throws Exception {
    Contestador c = new Contestador(PUERTO);
    double x[] = new double[CANTIDAD_MUESTRAS], y[] = new double[CANTIDAD_MUESTRAS];

    // puntos iniciales
    x = update(c, CANTIDAD_MUESTRAS); c.notificar();
    y = update(c, CANTIDAD_MUESTRAS); c.notificar();

    // Create Chart
    final XYChart chart = QuickChart.getChart("Titulo", "X", "Y", "f(x)", x, y);

    // chart.getStyler().setDefaultSeriesRenderStyle(XYSeriesRenderStyle.Scatter);
    // chart.getStyler().setChartTitleVisible(false);
    // chart.getStyler().setLegendPosition(LegendPosition.InsideSW);
    // chart.getStyler().setMarkerSize(16);
 
    // Show it
    final SwingWrapper<XYChart> sw = new SwingWrapper<XYChart>(chart);
    sw.displayChart();
 
    while (true) {
      Thread.sleep(2500);
      y = update(c, CANTIDAD_MUESTRAS);
      chart.updateXYSeries("f(x)", x, y, null);
      sw.repaintChart();
      c.notificar();
    }
  }

  private static double[] update(Contestador c, int n) {
    byte[] solicitud = c.getRequest();
    double z[] = new double[n];
    Contestador.messageFromBytes(solicitud, z);
    return z;
  }
}