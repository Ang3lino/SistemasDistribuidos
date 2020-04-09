
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
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

    private final double xMin = -32, xMax = 96;
    private final int yMin = -16, yMax = 16;
    private Set<Integer> requestReceived = new HashSet<>();


    public XYChart.Series<Number, Number> getSeries(ArrayList<Number> x, ArrayList<Number> y) {
        //  Configuring Series and adding data to the series    
        XYChart.Series<Number, Number> series = new XYChart.Series<>();  
        for (int i = 0; i < x.size(); ++i) {
            series.getData().add(new XYChart.Data<Number, Number>(x.get(i), y.get(i)));  
        }
        return series;
    }

    // Platform.runLater(() -> holder.getData().addAll(points));
    public void addPoints(XYChart.Series<Number, Number> holder, ArrayList<XYChart.Data<Number, Number>> points) {
        // for (int i = 0; i < points.size(); ++i) {
        //     XYChart.Data<Float, Float> data = points.get(i);
        //     Platform.runLater(() -> holder.getData().add(data)); 
        // }
        Platform.runLater(() -> {
            holder.getData().addAll(points);
        });
    }

    public void removePoints(XYChart.Series<Number, Number> holder, ArrayList<XYChart.Data<Number, Number>> points) {
        int counter = holder.getData().size();

        // while (--counter >= 0) {
        //     try {
        //         TimeUnit.MILLISECONDS.sleep(10);
        //     } catch (InterruptedException e) {
        //         System.out.println(e);
        //     }
        //     final int index = counter;
        //     Platform.runLater(() -> {
        //         holder.getData().remove(index);
        //     });
        // }

        Platform.runLater(() -> {
            holder.getData().removeAll(points);
        });
    }

    public void printArgs(float[] x, float[] y) {
        for (int i = 0; i < x.length; ++i)
            System.out.printf("%f, %f \n", x[i], y[i]);
    }

    private int updatePoints(Replier replier, float[] x, float[] y) {
        byte[] request = replier.getRequest();
        Message messageRequest = new Message(request);
        if (requestReceived.contains(messageRequest.requestId)) 
            return messageRequest.requestId;
        ByteBuffer bb = ByteBuffer.wrap(messageRequest.data);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        if (messageRequest.operationId == Message.SET_X_AXIS)
            for (int i = 0; i < x.length; ++i) x[i] = bb.getFloat();
        else
            for (int i = 0; i < y.length; ++i) y[i] = bb.getFloat();
        System.out.println("Message received: \n" + messageRequest + "\n");
        return messageRequest.requestId;
    }

    // controller
    public void updateChart(XYChart.Series<Number, Number> holder) {
        Replier replier = new Replier();
        int n = 1024;
        float x[] = new float[n];
        // Generator g = new Generator((float) xMin, (float) xMax, n);
        while (true) {
            ArrayList<XYChart.Data<Number, Number>> points = new ArrayList<>();
            float y[] = new float[n];

            int requestId = updatePoints(replier, x, y);
            if (requestReceived.contains(requestId)) {
                replier.sendReply(Message.REPLY, requestId + 1, Message.PLOT);
                continue;
            }
            requestReceived.add(requestId);

            // g.increment();
            // x =   g.x; y = g.y;
            // System.out.println(plotTimes);

            for (int i = 0; i < n; ++i) points.add(new XYChart.Data<Number, Number>(x[i], y[i]));
            
            System.out.println("With arguments: \n");
            printArgs(x, y);

            addPoints(holder, points);
            try {
                TimeUnit.MILLISECONDS.sleep(1000);
                // TimeUnit.MILLISECONDS.sleep(30000);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
            removePoints(holder, points);
            replier.sendReply(Message.REPLY, requestId + 1, Message.PLOT);
        }
        // Platform.exit();
    }
  
    @Override  
    public void start(Stage primaryStage) throws Exception {  
        // Configuring Xaxis and Yaxis  
        NumberAxis xaxis = new NumberAxis(xMin, xMax, 5);  
        NumberAxis yaxis = new NumberAxis(yMin, yMax, 2);  
        xaxis.setLabel("X");  
        yaxis.setLabel("Y");  
          
        // Configuring ScatterChart    
        ScatterChart<Number, Number> s = new ScatterChart<>(xaxis, yaxis);  
        s.setTitle("Fourier serie");  

        XYChart.Series<Number, Number> series = new XYChart.Series<>();  
        series.setName("Height value");  
          
        //Adding series to the ScatterChart  
        s.getData().add(series);  

        configGroupAndScene(primaryStage, s);
        new Thread(() -> updateChart(series)).start();
    }  

    public void configGroupAndScene(Stage primaryStage, ScatterChart<Number, Number> s) {
        //Configuring group and Scene   
        double horizontalSize = 800, verticalSize = 600;
        Group root = new Group();  
        s.setPrefSize(horizontalSize, verticalSize);
        root.getChildren().add(s);  
        Scene scene = new Scene(root, horizontalSize, verticalSize);  
        scene.getStylesheets().add("style.css");
        primaryStage.setScene(scene);  
        primaryStage.setTitle("Angel Lopez Manriquez 4CM1");  
        primaryStage.show();      
    }

    public static void main(String[] args) {  
        launch(args);  
    }  
  
}  