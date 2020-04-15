
import java.util.concurrent.TimeUnit;

import org.knowm.xchart.QuickChart;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYChartBuilder;
import org.knowm.xchart.XYSeries.XYSeriesRenderStyle;
import org.knowm.xchart.style.Styler.LegendPosition;



public class Plotter {
  private static final int PUERTO = 7200; 
  private static final int CANTIDAD_MUESTRAS = Const.TAM_MAX_DATA / 8;

  public static void main(String[] args) throws Exception {
    Contestador c = new Contestador(PUERTO);
    final double x[] = update(c, CANTIDAD_MUESTRAS);
    c.notificar();

    XYChart chart = new XYChartBuilder().width(700).height(600).title("Gaussian Blobs").xAxisTitle("X").yAxisTitle("Y").build();

    chart.getStyler().setDefaultSeriesRenderStyle(XYSeriesRenderStyle.Scatter);
    chart.getStyler().setChartTitleVisible(false);
    chart.getStyler().setLegendPosition(LegendPosition.InsideSW);
    chart.getStyler().setMarkerSize(4);

    chart.addSeries("f(x)", x, update(c, CANTIDAD_MUESTRAS));
    c.notificar();
 
    // Show it
    final SwingWrapper<XYChart> sw = new SwingWrapper<XYChart>(chart);
    sw.displayChart();
 
    while (true) {
      Thread actualizador = new Thread(() -> {
        chart.updateXYSeries("f(x)", x, update(c, CANTIDAD_MUESTRAS), null);
      });
      Thread borrador = new Thread(() -> {
        sw.repaintChart();
        c.notificar();
      });
      actualizador.start();
      actualizador.join();
      Thread.sleep(1000);
      borrador.start();
      borrador.join();
    }
  }

  private static double[] update(Contestador c, int n) {
    byte[] solicitud = c.getRequest();
    double z[] = new double[n];
    Contestador.messageFromBytes(solicitud, z);
    return z;
  }
}