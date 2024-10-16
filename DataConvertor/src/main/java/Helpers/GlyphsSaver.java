package Helpers;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;

public class GlyphsSaver {
    private static final char engStart = ' ';
    private static final char engEnd = '~';
    private static final char rusStart = 'А';
    private static final char rusEnd = 'я';

    public static void saveToFile(String file, String name, ArrayList<FontGlyph> glyphArrayList) {
        Path path = Path.of(file);
        try {
            Files.deleteIfExists(path);
            Files.writeString(path, "#include <stdint.h>\n", StandardOpenOption.APPEND, StandardOpenOption.CREATE);
            Files.writeString(path, "#include \"TFT/Fonts/wtc_fonts.h\"\n", StandardOpenOption.APPEND, StandardOpenOption.CREATE);
            int ch = engStart;
            for (FontGlyph gl : glyphArrayList
            ) {
                Files.writeString(path, "const glyph_t _" + ch + "_glyph_" + glyphArrayList.get(0).getH() + "= \n", StandardOpenOption.APPEND);
                Files.writeString(path, "\t{\n", StandardOpenOption.APPEND);
                Files.writeString(path, "\t\t" + gl.getW() + ",\n", StandardOpenOption.APPEND);
                Files.writeString(path, "\t\t{\n", StandardOpenOption.APPEND);
                for (int h = 0; h < gl.getH(); h++) {
                    Files.writeString(path, "\t\t\t", StandardOpenOption.APPEND);
                    for (int w = 0; w < gl.getGlyph()[h].length; w++) {
                        Files.writeString(path, "0x" + String.format("%2x", gl.getGlyph()[h][w] & 0xFF).replace(" ", "0") + ", ", StandardOpenOption.APPEND);
                    }
                    Files.writeString(path, "\t//", StandardOpenOption.APPEND);
                    int bitCnt = 0;
                    for (int w = 0; w < gl.getGlyph()[h].length; w++) {
                        int bit = 128;
                        int bt = gl.getGlyph()[h][w];
                        while (bit != 0 && bitCnt != gl.getW()) {
                            if ((bt & bit) != 0) {
                                Files.writeString(path, "*", StandardOpenOption.APPEND);
                            } else {
                                Files.writeString(path, "-", StandardOpenOption.APPEND);
                            }
                            bit = bit >> 1;
                            bitCnt++;
                        }
                    }
                    Files.writeString(path, "\n", StandardOpenOption.APPEND);
                }
                Files.writeString(path, "\t\t},\n", StandardOpenOption.APPEND);
                Files.writeString(path, "\t};\n", StandardOpenOption.APPEND);
                ch++;
                if (ch == engEnd + 1){
                    ch = rusStart;
                }
            }
            Files.writeString(path, "const WTC_FONT " + name + " __attribute__((aligned)) =\n", StandardOpenOption.APPEND);
            Files.writeString(path, "\t{\n", StandardOpenOption.APPEND);
            Files.writeString(path, "\t\t" + glyphArrayList.get(0).getH() + ",\n\t{\n", StandardOpenOption.APPEND);
            for (int i = engStart; i <= engEnd; i++) {
                Files.writeString(path, "\t\t&_" + i + "_glyph_" + glyphArrayList.get(0).getH() + ",\n", StandardOpenOption.APPEND);
            }
            for (int i = rusStart; i <= rusEnd; i++) {
                Files.writeString(path, "\t\t&_" + i + "_glyph_" + glyphArrayList.get(0).getH() + ",\n", StandardOpenOption.APPEND);
            }
            Files.writeString(path, "\t}\n};\n", StandardOpenOption.APPEND);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
