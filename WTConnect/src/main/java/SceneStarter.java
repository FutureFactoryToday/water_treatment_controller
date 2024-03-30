package main.java;

import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ChoiceBox;
import javafx.stage.Stage;

public class SceneStarter extends Application {
    @FXML
    private ChoiceBox<String> comPortList;

    @Override
    public void start(Stage primaryStage) throws Exception{
        Parent root = FXMLLoader.load(getClass().getResource("MainForm/MainForm.fxml"));
        primaryStage.setTitle("WTConnect");
        primaryStage.setScene(new Scene(root));

        primaryStage.show();
    }

}
