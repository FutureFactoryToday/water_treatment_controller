import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class BMPSaver {
    public static void saveToFile(String file, String name, NewBMP bmp) {
        Path path = Path.of(file);
        try {
            Files.deleteIfExists(path);
            Files.writeString(path, "#include <stdint.h>\n", StandardOpenOption.APPEND, StandardOpenOption.CREATE);
            Files.writeString(path, "#include \"bmp.h\" \n", StandardOpenOption.APPEND);
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
                      {""", StandardOpenOption.APPEND);
            int num = 0;
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

                      }
                    };""", StandardOpenOption.APPEND);
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }
}
