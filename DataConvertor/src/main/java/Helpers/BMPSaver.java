package Helpers;

import DataClasses.NewBMP;
import DataClasses.Pixel;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.nio.file.attribute.FileAttribute;

public class BMPSaver {
    public static void saveToFile(String file, String name, NewBMP bmp) {
        Path path = Path.of(file);
        try {
            Files.deleteIfExists(path);
            Files.writeString(path, "/*Pic Array v.2*/\n",StandardOpenOption.APPEND, StandardOpenOption.CREATE);
            Files.writeString(path, "#include <stdint.h>\n", StandardOpenOption.APPEND);
            Files.writeString(path, "#include \"TFT/bmp.h\" \n", StandardOpenOption.APPEND);
            Files.writeString(path, "#define   WIDTH   " + bmp.getW() + "\n", StandardOpenOption.APPEND);
            Files.writeString(path, "#define   HEIGHT  " + bmp.getH() + "\n", StandardOpenOption.APPEND);
            Files.writeString(path, "#define   SIZE  " + bmp.getMass().size() + "\n", StandardOpenOption.APPEND);
            Files.writeString(path, "const BITMAPSTRUCT " + name + " __attribute__((aligned)) =\n", StandardOpenOption.APPEND);
            Files.writeString(path, """
                    {
                      {
                        WIDTH,
                        HEIGHT,
                        SIZE
                      },
                      {
                      #ifdef _565_FORMAT
                      """, StandardOpenOption.APPEND);
            int num = 0;
            Files.writeString(path,"\t",StandardOpenOption.APPEND);
            for (Pixel p : bmp.getMass()
            ) {
                Files.writeString(path, "0x"+ p.toR5G6B5(), StandardOpenOption.APPEND);
                Files.writeString(path, ",\t", StandardOpenOption.APPEND);
                num++;
                if (num == bmp.getW()) {
                    Files.writeString(path, "\n\t", StandardOpenOption.APPEND);
                    num = 0;
                }
            }
            Files.writeString(path, """
                      
                        #endif
                      
                        #ifdef _24bit_FORMAT
                      """, StandardOpenOption.APPEND);
            num = 0;
            Files.writeString(path,"\t",StandardOpenOption.APPEND);
            for (Pixel p : bmp.getMass()
            ) {
                Files.writeString(path,  p.to24BitColor(), StandardOpenOption.APPEND);
                Files.writeString(path, ",\t", StandardOpenOption.APPEND);
                num++;
                if (num == bmp.getW()) {
                    Files.writeString(path, "\n\t", StandardOpenOption.APPEND);
                    num = 0;
                }
            }
            Files.writeString(path,"#endif\n\t}\n};\n", StandardOpenOption.APPEND);

        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }
    public static void updateSavedFile (String url) throws IOException {
        Path file = Path.of(url);
        Files.readString(file);
        String secLine = Files.readString(file);
        System.out.println(secLine);
//        if (!secLine.isBlank() && secLine.contains("#include \"TFT/bmp.h\" \n")){
//            Path tempFile = Files.createTempFile("temp_",".c");
//
//        }

    }
}
