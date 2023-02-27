import lombok.Data;
import org.imgscalr.Scalr;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.InputMismatchException;

@Data
public class NewBMP {
    private final String CORE = "CORE";
    private final String _3 = "Ver 3";
    private final String _4 = "Ver 4";
    private final String _5 = "Ver 5";

    private final int TYPE_BASE = 0;
    private final int SIZE_BASE = 2;
    private final int DATA_OFS_BASE = 10;
    private final int HEADER_BASE = 0xE;
    private final int WIDTH_BASE = 0x12;
    private final int HEIGHT_BASE = 0x16;
    private final int BIT_COUNT_BASE = 0x1c;
    private final int BIT_CONV_BASE = 0x1E;
    private final int IM_SIZE_BASE = 0x22;
    private String pic;
    private int h;
    private int w;
    ArrayList<Pixel> mass;
    int[] context;

    private int type;
    private int size;
    private int dataOffset;
    private int headerSize;
    private String version;
    private int bitCount;
    private int bitConv;
    private int bImSize;
    private int offset;
    private boolean needOffset;

    public NewBMP(String pic) throws IOException {
        convert(new File(pic));
    }

    public NewBMP(FontGlyph gl) {
        mass = new ArrayList<>();
        h = gl.getH();
        w = gl.getW();
        int bit = 128;
        int col = 0, row = 0;
        int newW = w/8;
        if (w%8 != 0){
            newW++;
        }
        int bt = gl.getGlyph()[row][col++];
        Pixel p;
        for (int i = 0; i < h*w; i++){
            if ((bt & bit) != 0){
                 p = new Pixel(0,0,0, 0, false);
            } else {
                 p = new Pixel(255, 255, 255, 0, false);
            }
            mass.add(p);
            bit = bit>>1;
            if (bit == 0 || (i+1)%w == 0){
                if (col == newW){
                    col = 0;
                    row++;
                    if (row == h){
                        break;
                    }
                }
                bit = 128;
                if (row >= h){
                    break;
                }
                bt = gl.getGlyph()[row][col++];
            }
        }

    }

    public NewBMP(String pic, int h, int w, int rot, int offSet, boolean needOffset) throws IOException {
        this.pic = pic;
        this.h = h;
        this.w = w;
        this.offset = offSet;
        this.needOffset = needOffset;
        File file = new File(pic);
        BufferedImage img = ImageIO.read(file);

        img = Scalr.resize(img, Scalr.Mode.FIT_EXACT, w, h);
        if (rot != 0) {
            Scalr.Rotation rotation = Scalr.Rotation.CW_90;
            switch (rot){
                case 180 ->{
                    rotation = Scalr.Rotation.CW_180;
                }
                case 270 ->{
                    rotation = Scalr.Rotation.CW_270;
                }
            }
            img = Scalr.rotate(img, rotation);
        }
        String s = file.getAbsolutePath();

        file = new File(s.replace(".bmp", "_temp.bmp"));

        ImageIO.write(img, "bmp", file);

        convert(file);

        file.delete();
    }

    private void convert(File file) throws IOException {
        byte[] temp = Files.readAllBytes(Path.of(file.getAbsolutePath()));

        context = new int[temp.length];
        for (int i = 0; i < temp.length; i++) {
            context[i] = castToInt(temp[i]);
        }

        type = get2Bytes(TYPE_BASE);
        size = get4Bytes(SIZE_BASE);
        dataOffset = get4Bytes(DATA_OFS_BASE);
        headerSize = get4Bytes(HEADER_BASE);
        switch (headerSize) {
            case 12 -> {
                version = CORE;
            }
            case 40 -> {
                version = _3;
            }
            case 108 -> {
                version = _4;
            }
            case 124 -> {
                version = _5;
            }
            default -> {
                throw new InputMismatchException("Плохой файл. Размер header " + headerSize);
            }
        }
        h = get4Bytes(HEIGHT_BASE);
        w = get4Bytes(WIDTH_BASE);
        bitCount = get2Bytes(BIT_COUNT_BASE);
        bitConv = get4Bytes(BIT_CONV_BASE);
        bImSize = get4Bytes(IM_SIZE_BASE);
        ArrayList<Pixel> tempArr = new ArrayList<>();
        int rowSize = w * 3 + w % 4;
        int row = 1;
        for (int el = 0; el < bImSize; el = el + 3) {
            if (el >= w * 3 + (row - 1) * rowSize) {
                while (el < rowSize * row) {
                    el++;
                }
                row++;
                if (el == bImSize) {
                    break;
                }
            }
            tempArr.add(new Pixel(context[el + dataOffset], context[el + 1 + dataOffset], context[el + 2 + dataOffset], offset, needOffset));
        }
        mass = new ArrayList<>();
        int ind;
        row = h - 1;
        int col = 0;
        for (int i = 0; i < tempArr.size(); i++) {
            ind = w * row + col++;
            if (col == w) {
                col = 0;
                row--;
            }
            mass.add(tempArr.get(ind));
        }
    }



    private int castToInt(byte b) {
        int res;
        if (b < 0) {
            res = 256 + b;
            return res;
        }
        return b;
    }

    private int get2Bytes(int base) {
        return (context[base + 1] << 8) + context[base];
    }

    private int get4Bytes(int base) {
        return (context[base + 3] << 24) + (context[base + 2] << 16) + (context[base + 1] << 8) + context[base];
    }

    //private int convRGBtoInt()

}
