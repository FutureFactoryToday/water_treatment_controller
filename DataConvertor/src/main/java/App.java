import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class App extends Application {
    private static Stage stage;
    @Override
    public void start(Stage primaryStage) throws Exception{

        stage = primaryStage;
        Parent root = FXMLLoader.load(getClass().getResource("MainForm.fxml"));
        primaryStage.setTitle("BMP to C array");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

        //System.out.println("Ok");
}
    public static Stage getStage(){
        return stage;
    }
}
