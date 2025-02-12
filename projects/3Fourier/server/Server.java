/**
 * Author: Angel Manriquez
 */

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
    private final int yMin = -8, yMax = 8;
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


    public void removePoints(XYChart.Series<Number, Number> holder) {
        final int n = holder.getData().size();
        for (int i = 0; i < n; ++i) {
            Platform.runLater(() -> {
                holder.getData().remove(0);
            });
        }
    }

    public void sleepMilliseconds(int ms) {
        try {
            TimeUnit.MILLISECONDS.sleep(ms);
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }

    public void removePoints(XYChart.Series<Number, Number> holder, ArrayList<XYChart.Data<Number, Number>> points) {
        Platform.runLater(() -> {
            holder.getData().removeAll(points);
        });
    }

    public void printArgs(float[] x, float[] y) {
        for (int i = 0; i < x.length; ++i)
            System.out.printf("%f, %f \n", x[i], y[i]);
    }


    private ArrayList<XYChart.Data<Number, Number>> getPointsAsArrayList(Message messageRequest, float[] x, float[] y) {
        ByteBuffer bb = ByteBuffer.wrap(messageRequest.data);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        if (messageRequest.operationId == Message.SET_X_AXIS)
            for (int i = 0; i < x.length; ++i) 
                x[i] = bb.getFloat();
        else
            for (int i = 0; i < y.length; ++i) 
                y[i] = bb.getFloat();
        System.out.println("Message received: \n" + messageRequest + "\n");
        ArrayList<XYChart.Data<Number, Number>> points = new ArrayList<>(x.length);
        for (int i = 0; i < x.length; ++i) points.add(new XYChart.Data<Number, Number>(x[i], y[i]));
        return points;
    }

    private Message getMessage(Replier replier, boolean repeated) {
        byte[] request = replier.getRequest();
        Message messageRequest = new Message(request);
        int requestId = messageRequest.requestId;
        if (requestReceived.contains(requestId)) {
            replier.sendReply(Message.REPLY, requestId + 1, Message.PLOT);
            repeated = true;
        }
        requestReceived.add(requestId);
        repeated = false;
        return messageRequest; 
    }

    // controller
    public void updateChart(XYChart.Series<Number, Number> holder) throws InterruptedException {
        Replier replier = new Replier();
        int n = Message.DATA_LENGTH >> 2;
        float x[] = new float[n], y[] = new float[n];
        boolean repeated = false;

        // add points first, then in the loop we'll remove them with threading
        Message message = getMessage(replier, repeated);
        ArrayList<XYChart.Data<Number, Number>> points = getPointsAsArrayList(message, x, y);
        addPoints(holder, points);    
        replier.sendReply(Message.REPLY, message.requestId + 1, Message.PLOT);

        while (true) {
            final ArrayList<XYChart.Data<Number, Number>> finalPoints = points;
            Thread remove = new Thread(() -> {
                sleepMilliseconds(4000);
                removePoints(holder, finalPoints);
            });
            remove.start();
            message = getMessage(replier, repeated);
            if (repeated) continue;
            points = getPointsAsArrayList(message, x, y);
            try { 
                remove.join();
            } catch (InterruptedException e) { System.out.println(e);}
            addPoints(holder, points);    
            replier.sendReply(Message.REPLY, message.requestId + 1, Message.PLOT);
        }
        // Platform.exit();
    }
  
    @Override  
    public void start(Stage primaryStage) throws Exception {  
        // Configuring Xaxis and Yaxis  
        NumberAxis xaxis = new NumberAxis(xMin, xMax, 5);  
        NumberAxis yaxis = new NumberAxis(yMin, yMax, 5);  
        xaxis.setLabel("X");  
        yaxis.setLabel("Y");  
          
        // Configuring ScatterChart    
        ScatterChart<Number, Number> s = new ScatterChart<>(xaxis, yaxis);  
        s.setTitle("Proyecto 3");  

        XYChart.Series<Number, Number> series = new XYChart.Series<>();  
        series.setName("Graficador y receptor (Java) de las sumas parciales crecientes de Fourier enviadas por C++");  
          
        //Adding series to the ScatterChart  
        s.getData().add(series);  

        configGroupAndScene(primaryStage, s);
        new Thread(() -> {
            try {
                updateChart(series);
            } catch (InterruptedException e) { 
                System.out.println(e); 
            }
        }).start();
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