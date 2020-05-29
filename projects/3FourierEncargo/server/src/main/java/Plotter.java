
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
    String funcionId = "f(x)";

    XYChart chart = new XYChartBuilder().width(700).height(600).title("Fourier").xAxisTitle("X").yAxisTitle("Y").build();

    // Configuracion de la instancia de XYChart
    chart.getStyler().setDefaultSeriesRenderStyle(XYSeriesRenderStyle.Scatter);
    chart.getStyler().setChartTitleVisible(false);
    chart.getStyler().setLegendPosition(LegendPosition.InsideSW);
    chart.getStyler().setMarkerSize(4);

    chart.addSeries(funcionId, x, update(c, CANTIDAD_MUESTRAS)); c.notificar();
    final SwingWrapper<XYChart> sw = new SwingWrapper<XYChart>(chart);  // redimensionamiento automatico
    sw.displayChart();  // muestra la grafica
 
    while (true) {
      Thread actualizador = new Thread(() -> {
        chart.updateXYSeries(funcionId, x, update(c, CANTIDAD_MUESTRAS), null);
      });
      Thread borrador = new Thread(() -> {
        sw.repaintChart();
        c.notificar();
      });
      actualizador.start();
      actualizador.join();
      Thread.sleep(1000);  // para verificar la aproximacion puede incrementar el retraso de actualizacion
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