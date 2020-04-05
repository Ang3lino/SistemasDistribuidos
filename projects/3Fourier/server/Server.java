
import java.util.ArrayList;
import java.util.concurrent.TimeUnit;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.ScatterChart;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;


public class Server extends Application { 
    public XYChart.Series<Float, Float> getSeries(ArrayList<Float> x, ArrayList<Float> y) {
        //Configuring Series and adding data to the series    
        XYChart.Series<Float, Float> series = new XYChart.Series<Float, Float>();  
        for (int i = 0; i < x.size(); ++i) {
            series.getData().add(new XYChart.Data<Float, Float>(x.get(i), y.get(i)));  
        }
        return series;
    }

    public void addPoints(XYChart.Series<Float, Float> holder, ArrayList<Float> x, ArrayList<Float> y) {

    }

    public void updateChart(XYChart.Series<Float, Float> holder) {
        ArrayList<XYChart.Data<Float, Float>> toRemove = new ArrayList<>();
        for (int i = 0; i < 100; ++i) {
            final float p = (float) i;
            final float q = (float) i;
            System.out.printf("Passing %f %f\n", p,q);
            try {
                TimeUnit.MILLISECONDS.sleep(100);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
            XYChart.Data<Float, Float> data = new XYChart.Data<Float, Float>(p, q);
            Platform.runLater(() -> holder.getData().add(data)); 
            toRemove.add(data);
        }
        while (!toRemove.isEmpty()) {
            XYChart.Data<Float, Float> data = toRemove.get(0);
            Platform.runLater(() -> holder.getData().remove(data)); 
            try {
                TimeUnit.MILLISECONDS.sleep(100);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
            toRemove.remove(0);
        }
    }
  
    @Override  
    public void start(Stage primaryStage) throws Exception {  
        // TODO Auto-generated method stub  
        //Configuring Xaxis and Yaxis  
        int xMin = 0, xMax = 100;
        NumberAxis xaxis = new NumberAxis(xMin, xMax, 10);  
        NumberAxis yaxis = new NumberAxis(xMin, xMax, 10);  
        xaxis.setLabel("Weight");  
        yaxis.setLabel("Height");  
          
        //Configuring ScatterChart    
        ScatterChart s = new ScatterChart(xaxis, yaxis);  
        s.setTitle("Perfect height according to your weight");  

        ArrayList<Float> x = new ArrayList<>(), y = new ArrayList<>();
        for (int i = xMin; i < xMax; ++i) {
            x.add((float) i);
            y.add((float) 2*i);
        }
        XYChart.Series series = getSeries(x, y);
        series.setName("Height value");  
          
        //Adding series to the ScatterChart  
        s.getData().add(series);  

        Thread t = new Thread(() -> updateChart(series));
          
        //Configuring group and Scene   
        double horizontalSize = 800, verticalSize = 600;
        Group root = new Group();  
        s.setPrefSize(horizontalSize, verticalSize);
        root.getChildren().add(s);  
        Scene scene = new Scene(root, horizontalSize, verticalSize);  
        scene.getStylesheets().add("style.css");
        primaryStage.setScene(scene);  
        primaryStage.setTitle("ScatterChart Example");  
        primaryStage.show();      
          
          
        t.start();
    }  

    public static void main(String[] args) {  
        launch(args);  
    }  
  
}  