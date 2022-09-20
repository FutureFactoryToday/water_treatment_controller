import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.nio.file.attribute.FileStoreAttributeView;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        args = new String[1];
        args[0] = "E:\\MyData\\Projects\\water_treatment_controller\\GUI\\Макет\\Buttons\\c";

        if (args.length == 0){
            System.out.println("Выберете файл");
            return;
        }
        File srcDir = new File(args[0]);
        File[] files = srcDir.listFiles();
        for(File str: files){
            if (str.getAbsolutePath().contains(".c")) {
                modFile(str.getAbsolutePath(), args[0]);
            }
        }
    }

    public static void modFile(String file, String base) {
        try {
            Path filePath = Path.of(file);
            String fileName = file.replace(base,"").replace(".c","");

            String[] content = Files.lines(filePath).toArray(String[]::new);
            ArrayList<String> modContent = new ArrayList<>();
            for (String s : content
            ) {
                for (String sS : s.split("[,\s]")
                ) {
                    sS = sS.replace(",", "");
                    if (sS.contains("0X")) {
                        modContent.add(sS);
                    }
                }
            }
            modContent.subList(0, 8).clear();


            Path newFile = Path.of(filePath.getParent() +"\\mod\\" +fileName +"_modFile.c");
            if (Files.exists(newFile)) {
                Files.delete(newFile);
            }
            Files.createFile(newFile);
            ArrayList<String> newModCont = new ArrayList<>();
            for (int i = 0; i < modContent.size(); i = i + 2) {
                String s = "RC(".concat(modContent.get(i + 1)).concat(modContent.get(i).replace("0X", "").concat("), "));
//                if ((i + 2) % 300 == 0) {
                    s = s.concat("\n");

//                }
                newModCont.add(s);
            }

            newModCont.forEach(s -> {
                try {
                    Files.writeString(newFile, s, StandardOpenOption.APPEND);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

