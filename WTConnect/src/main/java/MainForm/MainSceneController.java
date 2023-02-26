package main.java.MainForm;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import jssc.*;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;


import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;

public class MainSceneController {
    public TextArea log;
    public MenuItem menuSettings;
    public TextField ta1;
    public Label msg;
    private SerialPort serialPort;
    private static final Logger LOGGER = LogManager.getLogger(MainSceneController.class);
    private final DateTimeFormatter logTimeFormat = DateTimeFormatter.ofPattern("yyyy.MM.dd HH:mm:ss");
    public Button connectButton;
    public Button sendButton;
    public Circle connectionStatus;
    @FXML
    public ChoiceBox<String> comPortList;
    private boolean isComFound;
    private String message;

    private final String reconnect = "Повторить сканирование";
    private final String connect = "Подключиться";
    private final String disconnect = "Отключиться";

    public void menuSettingsClick() throws IOException {
//        Parent root = FXMLLoader.load(getClass().getResource("SettingsForm/SettingsForm.fxml"));
//        primaryStage.setTitle("Hello World");
//        primaryStage.setScene(new Scene(root));
//        primaryStage.show();
    }

    public void sendButton () throws SerialPortException {
        if (!ta1.getText().isBlank()) {
            byte num = Byte.parseByte(ta1.getText());
            serialPort.writeByte(num);
        }
    }
    public void connectButtonClick() throws SerialPortException {
        if (!isComFound){
            fillComPorts();
        } else {
            if (serialPort == null || !serialPort.isOpened()) {
                connectToPort(comPortList.getValue());
                connectionStatus.setFill(Paint.valueOf("lightgreen"));
                connectButton.setText(disconnect);
                toggleButtons();
            } else {
                disconnectFromPort();
                connectionStatus.setFill(Paint.valueOf("red"));
                connectButton.setText(connect);
                toggleButtons();
            }
        }
    }

    private void connectToPort(String name) throws SerialPortException {
        serialPort = new SerialPort(name);
        if (serialPort.openPort())
        {
            serialPort.setParams(SerialPort.BAUDRATE_9600,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);

            serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);

            log("Удачно подключено к порту: " + serialPort.getPortName());
        }
    }
    private void disconnectFromPort() throws SerialPortException {
        serialPort.closePort();
        log("Удачно отключено от порта: " + serialPort.getPortName());
    }
    private void toggleButtons(){
        comPortList.setDisable(!comPortList.isDisable());
    }

    private void fillComPorts(){
        final String noComs = "Нет доступных Com";

        String[] comListRaw = SerialPortList.getPortNames();

        ObservableList<String> comList = comPortList.getItems();
        //LOGGER.info("Временный список " + comList);
        if (comList != null){
            comList.clear();
        }


        //LOGGER.info("Длина comListRaw: "+ comListRaw.length);
        //LOGGER.info("ComList до иниацилизации: "+ comList);
        if (comListRaw.length != 0) {
            comList = FXCollections.observableArrayList();
            comList.addAll(Arrays.asList(comListRaw));
            comPortList.setDisable(false);
        } else {

            comList = FXCollections.observableArrayList(noComs);
            comPortList.setDisable(true);
        }
        //LOGGER.info("ComList после иниацилизации: "+ comList);
        comPortList.setItems(comList);

        comPortList.getSelectionModel().selectFirst();
        String firstLine = comPortList.getSelectionModel().getSelectedItem();
        //LOGGER.info("Первая строчка: "+ firstLine);
        comPortList.getSelectionModel().selectFirst();
        comPortList.setValue(firstLine);
        if (firstLine.equals(noComs)){
            isComFound = false;
            log(noComs);
            connectButton.setText(reconnect);
        } else {
            isComFound = true;
            log("Найдено COM портов: " + comListRaw.length);
            connectButton.setText(connect);
        }
    }

    @FXML
    void initialize(){
        fillComPorts();
    }

    private void log (String msg){

        log.appendText(LocalDateTime.now().format(logTimeFormat) + ": " + msg + "\n");
    }

    public class PortReader implements SerialPortEventListener {
          public void serialEvent(SerialPortEvent event) {
            if(event.isRXCHAR() && event.getEventValue() > 0){
                try {
                    //Получаем ответ от устройства, обрабатываем данные и т.д.
                    message =serialPort.readString(event.getEventValue());
                }
                catch (SerialPortException ex) {
                    ex.printStackTrace();
                }
            }
        }
    }
}
