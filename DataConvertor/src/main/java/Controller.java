import javafx.embed.swing.*;
import javafx.fxml.Initializable;
import javafx.scene.SnapshotParameters;
import javafx.scene.canvas.Canvas;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.WritableImage;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Paint;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.ResourceBundle;

public class Controller implements Initializable {
    public TextField fontSaveName;
    public Tab fontTab;
    public Tab bmpTab;
    boolean isInited;
    File lastSaveDir, lastLoadDir;
    public CheckBox prop;
    public Button txt;
    public ComboBox<String> fonts;
    public Label txtLbl;
    private final Stage stage = App.getStage();

    public Pane modPic;
    public Canvas drawField;
    public TextField selectedFile;
    public TextField arrayName;
    public TextField height;
    public TextField width;
    public Canvas initPic;
    public ChoiceBox<Integer> rotCh;
    public Label modChar;
    public TextField fontHeight;
    public Button previewGlyphsBtn;
    public Button saveGlyphsBtn;
    public Button previewPicBtn;
    public Button savePicBtn;
    int h;
    int w;
    double proportion;
    public Label log;
    Image initImg;
    private final char engStart = ' ';
    private final char engEnd = '~';
    private final char rusStart = 'А';
    private final char rusEnd = 'я';
    private ArrayList<FontGlyph> glyphs;
    NewBMP bmpPic;

    private void log(String str) {
        log.setText(str);
    }

    private void addGlyph(char ch) throws IOException {
        SnapshotParameters sp = new SnapshotParameters();
        sp.setFill(Paint.valueOf("WHITE"));
        modChar.setText(String.valueOf(ch));
        WritableImage img = modChar.snapshot(sp, null);
        String tempFile = System.getProperty("java.io.tmpdir") + "\\temp.bmp";
        File file = new File(tempFile);
        if (file.isFile()) {
            file.delete();
        }
        BufferedImage rImg = SwingFXUtils.fromFXImage(img, null);
        BufferedImage temp = new BufferedImage(rImg.getWidth(), rImg.getHeight(), BufferedImage.TYPE_INT_RGB);
        Graphics2D g = temp.createGraphics();
        g.drawImage(rImg, 0, 0, rImg.getWidth(), rImg.getHeight(), null);
        g.dispose();
        ImageIO.write(temp, "bmp", file);
        NewBMP glBMP = new NewBMP(tempFile);

        //FontGlyph.test();
        FontGlyph gl = new FontGlyph(glBMP);
        glyphs.add(gl);
    }

    public void previewGlyphs() throws IOException {

        try {
            initPic.getGraphicsContext2D().clearRect(0,0, initPic.getWidth(),initPic.getHeight());
            int initH = h = Integer.parseInt(fontHeight.getText());
            int initW = w = h;
            initPic.getGraphicsContext2D().setFont(Font.font(AutoComplete.getComboBoxValue(fonts), FontWeight.NORMAL, h));

            for (char i = engStart; i <= engEnd; i++){
                initPic.getGraphicsContext2D().fillText(String.valueOf(i),w,h);
                w += initW;
                if (w > initPic.getWidth() - initW){
                    h+=initH;
                    w = 0;
                }
            }
            for (char i = rusStart; i <= rusEnd; i++){
                initPic.getGraphicsContext2D().fillText(String.valueOf(i),w,h);
                w += initW;
                if (w > initPic.getWidth() - initW){
                    h+=initH;
                    w = 0;
                }
            }
            addAllGlyphs();
            drawGlyphs(glyphs);

        } catch (NumberFormatException pe) {
            Alert alert = new Alert(Alert.AlertType.ERROR);

            alert.setTitle("Неправильный размер шрифта");
            alert.setHeaderText(null);
            alert.setContentText("Неверно введен размер шрифта!\nВведеный текст: " + fontHeight.getText() + "\nДолжно быть число!");

            alert.showAndWait();
        } catch (Exception ex) {
            ex.printStackTrace();
            System.out.println(glyphs.size());
        }
    }

    private void addAllGlyphs() throws IOException {
        glyphs = new ArrayList<>();

        double h = Double.parseDouble(fontHeight.getText());
        modChar.setFont(Font.font(AutoComplete.getComboBoxValue(fonts), FontWeight.NORMAL, h));

        for (char i = engStart; i <= engEnd; i++) {
            addGlyph(i);
        }
        for (char i = rusStart; i <= rusEnd; i++) {
            addGlyph(i);
        }
    }

    private void drawGlyphs(ArrayList<FontGlyph> glyphs) {
        int curX = 0, curY = 0, maxY = 0;
        drawField.getGraphicsContext2D().clearRect(0, 0, drawField.getWidth(), drawField.getHeight());
        for (FontGlyph gl : glyphs) {
            NewBMP glBMP = new NewBMP(gl);
            if (curX >= modPic.getWidth() - glBMP.getW()) {
                curY += maxY;
                curX = 0;
                if (curY >= modPic.getHeight() - glBMP.getH()) {
                    break;
                }
            }
            drawBMP(glBMP, curX, curY);
            curX += glBMP.getW();
            maxY = Math.max(maxY, glBMP.getH());

        }
    }

    public void saveGlyphs() throws IOException {

        FileChooser fCh = new FileChooser();
        fCh.setTitle("Сохранение файла шрифта");
        if (lastSaveDir != null) {
            fCh.setInitialDirectory(
                    lastSaveDir
            );
        }
        fCh.getExtensionFilters().add(new FileChooser.ExtensionFilter("C File", "*.c"));

        File saveFile = fCh.showSaveDialog(stage);
        if (saveFile != null) {
            lastSaveDir = saveFile.getParentFile();
            if (glyphs == null) {
                addAllGlyphs();
            }
            GlyphsSaver.saveToFile(saveFile.getAbsolutePath(), fontSaveName.getText(), glyphs);
            glyphs = null;
            log("Сохранен файл " + saveFile.getName());
        }

    }


    public void changeWidth() {
        if (prop.isSelected()) {
            if (!height.getText().isEmpty()) {
                width.setText(String.valueOf((int) proportion * (int) Double.parseDouble(height.getText())));
            }
        }
    }

    public void changeHeight() {
        if (prop.isSelected()) {
            if (!width.getText().isEmpty()) {
                height.setText(String.valueOf((int) (Double.parseDouble(width.getText()) / proportion)));
            }
        }
    }

    public void chooseFileClick() throws IOException {
        FileChooser fCh = new FileChooser();
        fCh.setTitle("Выберите изображение");
        fCh.getExtensionFilters().add(new FileChooser.ExtensionFilter("BMP File", "*.bmp"));
        if (lastLoadDir != null) {
            fCh.setInitialDirectory(
                    lastLoadDir
            );
        }
        File selectedPic = fCh.showOpenDialog(stage);
        //File selectedPic = new File("C:\\Users\\bogdanov.ai\\Pictures\\test\\test2.bmp");
        //File selectedPic = new File("C:\\Users\\bogdanov.ai\\Pictures\\C-70logo.bmp");
        if (selectedPic == null) {
            log("Файл не найден");
            return;
        }
        lastLoadDir = selectedPic.getParentFile();

        log("Выбран файл: " + selectedPic);
        selectedFile.setText(selectedPic.getPath());
        System.out.println("Img try");
        arrayName.setText(selectedPic.getName().split("\\.")[0]);
        InputStream s = new FileInputStream(selectedPic);
        initImg = new Image(s);

        System.out.println("Img loaded");

        setInitPic();

        drawField.getGraphicsContext2D().clearRect(0, 0, drawField.getWidth(), drawField.getHeight());
    }

    public void setInitPic() {
        initPic.getGraphicsContext2D().clearRect(0, 0, initPic.getWidth(), initPic.getHeight());
        double h = (initImg.getHeight() < 320) ? initImg.getHeight() : 320.0;
        double w = (initImg.getWidth() < 480) ? initImg.getWidth() : 480.0;
        int startX = (int) (initPic.getWidth() / 2 - w / 2);
        int startY = (int) (initPic.getHeight() / 2 - h / 2);

        initPic.getGraphicsContext2D().drawImage(initImg, startX, startY);
        width.setText(String.valueOf((int) initImg.getWidth()));


        height.setText(String.valueOf((int) initImg.getHeight()));
        proportion = w / h;
    }

    public void previewPic() throws IOException {
        try {
            if (initImg == null) {
                return;
            }
            bmpPic = new NewBMP(selectedFile.getText(), Integer.parseInt(height.getText()), Integer.parseInt(width.getText()), rotCh.getValue());
            drawBMP(bmpPic);
        }catch (Exception e){
            e.printStackTrace();
            log("Ошибка открытия файла.");
        }
    }

    public void fontChange (){
        if(isInited) {
            String font = fonts.getValue();
            if (font != null && !font.isEmpty()) {
                fontSaveName.setText(fonts.getValue().replace(" ", "_") + "_" + fontHeight.getText());
            }
        }
    }
    public void savePic() throws IOException {
        FileChooser fCh = new FileChooser();
        fCh.setTitle("Сохранение изображения");
        if (lastSaveDir != null) {
            fCh.setInitialDirectory(
                    lastSaveDir
            );
        }
        fCh.getExtensionFilters().add(new FileChooser.ExtensionFilter("C File", "*.c"));

        File saveFile = fCh.showSaveDialog(stage);
        if (saveFile != null) {
            lastSaveDir = saveFile.getParentFile();
            if (bmpPic == null) {
                bmpPic = new NewBMP(selectedFile.getText(), Integer.parseInt(height.getText()), Integer.parseInt(width.getText()), rotCh.getValue());
            }
            BMPSaver.saveToFile(saveFile.getAbsolutePath(), arrayName.getText(), bmpPic);
            bmpPic = null;
            log("Картинка сохранена " + saveFile.getAbsolutePath());
        }

    }

    private void drawBMP(NewBMP bmp, int x, int y) {

        for (h = 0; h < bmp.getH(); h++) {
            for (w = 0; w < bmp.getW(); w++) {
                drawPixel(x + w, y + h, bmp.getMass().get(h * bmp.getW() + w));
            }
        }
    }

    private void drawBMP(NewBMP bmp) {
        int startX = (int) (drawField.getWidth() / 2 - bmp.getW() / 2);
        int startY = (int) (drawField.getHeight() / 2 - bmp.getH() / 2);
        drawField.getGraphicsContext2D().clearRect(0, 0, drawField.getWidth(), drawField.getHeight());
        for (h = 0; h < bmp.getH(); h++) {
            for (w = 0; w < bmp.getW(); w++) {
                drawPixel(startX + w, startY + h, bmp.getMass().get(h * bmp.getW() + w));
            }
        }
    }

    private void drawPixel(double x, double y, Pixel p) {
        if (x < drawField.getWidth() && y < drawField.getHeight() && x >= 0 && y >= 0) {
            drawField.getGraphicsContext2D().setFill(Paint.valueOf(p.toColor()));
            drawField.getGraphicsContext2D().fillRect(x, y, 1, 1);
        } else {
            throw new InputMismatchException("Неверные координаты: \n x: " + x + "\ny: " + y);
        }
    }

    public void changeScreen() {
        if (isInited) {
            drawField.getGraphicsContext2D().clearRect(0, 0, drawField.getWidth(), drawField.getHeight());
            initPic.getGraphicsContext2D().clearRect(0, 0, initPic.getWidth(), initPic.getHeight());
            log("");
            if (bmpTab.isSelected()) {
                if (!selectedFile.getText().isEmpty()) {
                    setInitPic();
                }
            }
            if (fontTab.isSelected()) {
                if (fontSaveName.getText().isEmpty())
                {
                    String font = AutoComplete.getComboBoxValue(fonts);
                    if (font != null && !font.isEmpty()) {
                        fontSaveName.setText(font.replace(" ", "_") + "_" + fontHeight.getText());
                    }
                }
            }
        }

    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        List<String> avFonts = Font.getFontNames();
        if (avFonts != null) {
            fonts.getItems().addAll(avFonts);
            System.out.println("Fonts loaded: " + fonts.getItems().size());

        }
        AutoComplete.autoCompleteComboBoxPlus(fonts, (typedText, itemToCompare) -> itemToCompare.contains(typedText));
        fonts.setValue("Oxygen Mono");
        rotCh.getItems().addAll(0, 90, 180, 270);
        rotCh.setValue(rotCh.getItems().get(0));
        fontHeight.setText("8");
        isInited = true;
        log("Готов к работе");
    }
}
