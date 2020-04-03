
import java.util.ArrayList;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.ScatterChart;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;


public class Scatter extends Application { 
    public XYChart.Series<Float, Float> getSeries(ArrayList<Float> x, ArrayList<Float> y) {
        //Configuring Series and adding data to the series    
        XYChart.Series<Float, Float> series = new XYChart.Series<Float, Float>();  
        for (int i = 0; i < x.size(); ++i) {
            series.getData().add(new XYChart.Data<Float, Float>(x.get(i), y.get(i)));  
        }
        return series;
    }
  
    @Override  
    public void start(Stage primaryStage) throws Exception {  
        // TODO Auto-generated method stub  
        //Configuring Xaxis and Yaxis  
        NumberAxis xaxis = new NumberAxis(35, 105, 5);  
        NumberAxis yaxis = new NumberAxis(35, 105, 5);  
        xaxis.setLabel("Weight");  
        yaxis.setLabel("Height");  
          
        //Configuring ScatterChart    
        ScatterChart s = new ScatterChart(xaxis,yaxis);  
        s.setTitle("Perfect height according to your weight");  

        ArrayList<Float> x = new ArrayList<>(), y = new ArrayList<>();
        for (int i = 35; i < 100; ++i) {
            x.add((float) i);
            y.add((float) i);
        }
        for (int i = 35; i < 100; ++i) {
            x.add((float) i);
            y.add((float) 2*i);
        }
        XYChart.Series series = getSeries(x, y);
        series.setName("Height value");  
          
        //Adding series to the ScatterChart  
        s.getData().add(series);  
          
        //Configuring group and Scene   
        Group root = new Group();  
        root.getChildren().add(s);  
        Scene scene = new Scene(root,600,400);  
        scene.getStylesheets().add("style.css");
        primaryStage.setScene(scene);  
        primaryStage.setTitle("ScatterChart Example");  
        primaryStage.show();      
          
          
    }  
    public static void main(String[] args) {  
        launch(args);  
    }  
  
}  