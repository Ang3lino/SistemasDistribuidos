
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
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
        //  Configuring Series and adding data to the series    
        XYChart.Series<Float, Float> series = new XYChart.Series<Float, Float>();  
        for (int i = 0; i < x.size(); ++i) {
            series.getData().add(new XYChart.Data<Float, Float>(x.get(i), y.get(i)));  
        }
        return series;
    }

    public void addPoints(XYChart.Series<Float, Float> holder, ArrayList<XYChart.Data<Float, Float>> points) {
        for (int i = 0; i < points.size(); ++i) {
            try {
                TimeUnit.MILLISECONDS.sleep(10);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
            XYChart.Data<Float, Float> data = points.get(i);
            Platform.runLater(() -> holder.getData().add(data)); 
        }
    }

    public void removePoints(XYChart.Series<Float, Float> holder, ArrayList<XYChart.Data<Float, Float>> points) {
        int counter = points.size();
        while (--counter >= 0) {
            final XYChart.Data<Float, Float> data = points.get(counter);
            Platform.runLater(() -> holder.getData().remove(data)); 
            try {
                TimeUnit.MILLISECONDS.sleep(10);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }

    public void printArgs(float[] x, float[] y) {
        for (int i = 0; i < 512; ++i)
            System.out.printf("%f %f \n", x[i], y[i]);
    }

    // controller
    public void updateChart(XYChart.Series<Float, Float> holder) {
        ArrayList<XYChart.Data<Float, Float>> points = new ArrayList<>();
        Replier replier = new Replier();
        int plotTimes = 10;
        while (--plotTimes >= 0) {
            byte[] request = replier.getRequest();
            Message messageRequest = new Message(request);
            ByteBuffer bb = ByteBuffer.wrap(messageRequest.data);
            bb.order(ByteOrder.LITTLE_ENDIAN);
            float x[] = new float[512], y[] = new float[512];
            for (int i = 0; i < 512; ++i) x[i] = bb.getFloat();
            for (int i = 0; i < 512; ++i) y[i] = bb.getFloat();
            for (int i = 0; i < 512; ++i) points.add(new XYChart.Data<Float, Float>(x[i], y[i]));
            printArgs(x, y);
            Thread t = new Thread(() -> {
                addPoints(holder, points);
                removePoints(holder, points);
            });
            t.start();
            replier.sendReply(Message.REPLY, messageRequest.requestId + 1, Message.DUMMY);
            try {
                t.join();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }
  
    @Override  
    public void start(Stage primaryStage) throws Exception {  
        // Configuring Xaxis and Yaxis  
        int xMin = -32, xMax = 96;
        int yMin = -16, yMax = 16;
        NumberAxis xaxis = new NumberAxis(xMin, xMax, 2);  
        NumberAxis yaxis = new NumberAxis(yMin, yMax, 2);  
        xaxis.setLabel("X");  
        yaxis.setLabel("Y");  
          
        // Configuring ScatterChart    
        ScatterChart s = new ScatterChart(xaxis, yaxis);  
        s.setTitle("Fourier serie");  

        XYChart.Series<Float, Float> series = new XYChart.Series<Float, Float>();  
        series.setName("Height value");  
          
        //Adding series to the ScatterChart  
        s.getData().add(series);  

        configGroupAndScene(primaryStage, s);
        Thread t = new Thread(() -> updateChart(series));
        t.start();
    }  

    public void configGroupAndScene(Stage primaryStage, ScatterChart s) {
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
    }

    public static void main(String[] args) {  
        launch(args);  
    }  
  
}  