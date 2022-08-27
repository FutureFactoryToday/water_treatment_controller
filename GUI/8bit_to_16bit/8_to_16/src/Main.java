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
        args[0] = "E:\\MyData\\Projects\\water_treatment_controller\\GUI\\Logo\\smallLogo_16b_raw.c";
        if (args.length == 0){
            System.out.println("Выберете файл");
            return;
        }
        try {
            String[] content = Files.lines(Path.of(args[0])).toArray(String[]::new);
            ArrayList<String> modContent = new ArrayList<>();
            for (String s: content
                 ) {
                for (String sS:s.split("[,\s]")
                     ) {
                    sS = sS.replace(",","");
                    if (sS.contains("0X")) {
                        modContent.add(sS);
                    }
                    }
                }
            for(int i = 0; i < 8; i ++) {
                modContent.remove(0);
            }


            Path newFile = Path.of(Path.of(args[0]).getParent() + "\\modFile.c");
            if (Files.exists(newFile)){
                Files.delete(newFile);
            }
            Files.createFile(newFile);
            ArrayList<String> newModCont = new ArrayList<>();
            for (int i = 0; i < modContent.size(); i=i+2){
                String s = "RC(".concat(modContent.get(i+1)).concat(modContent.get(i).replace("0X","").concat("), "));
                if ((i+2) % 300 == 0){
                    s=s.concat("\n");

                }
                newModCont.add(s);
            }

            newModCont.forEach(s -> {
                try {
                    Files.writeString(newFile,s, StandardOpenOption.APPEND);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });
            } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
