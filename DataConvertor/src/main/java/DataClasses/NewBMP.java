package DataClasses;

import Helpers.FontGlyph;
import org.imgscalr.Scalr;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.InputMismatchException;

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
            case 12 -> version = CORE;
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

    public String getCORE() {
        return this.CORE;
    }

    public String get_3() {
        return this._3;
    }

    public String get_4() {
        return this._4;
    }

    public String get_5() {
        return this._5;
    }

    public int getTYPE_BASE() {
        return this.TYPE_BASE;
    }

    public int getSIZE_BASE() {
        return this.SIZE_BASE;
    }

    public int getDATA_OFS_BASE() {
        return this.DATA_OFS_BASE;
    }

    public int getHEADER_BASE() {
        return this.HEADER_BASE;
    }

    public int getWIDTH_BASE() {
        return this.WIDTH_BASE;
    }

    public int getHEIGHT_BASE() {
        return this.HEIGHT_BASE;
    }

    public int getBIT_COUNT_BASE() {
        return this.BIT_COUNT_BASE;
    }

    public int getBIT_CONV_BASE() {
        return this.BIT_CONV_BASE;
    }

    public int getIM_SIZE_BASE() {
        return this.IM_SIZE_BASE;
    }

    public String getPic() {
        return this.pic;
    }

    public int getH() {
        return this.h;
    }

    public int getW() {
        return this.w;
    }

    public ArrayList<Pixel> getMass() {
        return this.mass;
    }

    public int[] getContext() {
        return this.context;
    }

    public int getType() {
        return this.type;
    }

    public int getSize() {
        return this.size;
    }

    public int getDataOffset() {
        return this.dataOffset;
    }

    public int getHeaderSize() {
        return this.headerSize;
    }

    public String getVersion() {
        return this.version;
    }

    public int getBitCount() {
        return this.bitCount;
    }

    public int getBitConv() {
        return this.bitConv;
    }

    public int getBImSize() {
        return this.bImSize;
    }

    public int getOffset() {
        return this.offset;
    }

    public boolean isNeedOffset() {
        return this.needOffset;
    }

    public void setPic(String pic) {
        this.pic = pic;
    }

    public void setH(int h) {
        this.h = h;
    }

    public void setW(int w) {
        this.w = w;
    }

    public void setMass(ArrayList<Pixel> mass) {
        this.mass = mass;
    }

    public void setContext(int[] context) {
        this.context = context;
    }

    public void setType(int type) {
        this.type = type;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void setDataOffset(int dataOffset) {
        this.dataOffset = dataOffset;
    }

    public void setHeaderSize(int headerSize) {
        this.headerSize = headerSize;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public void setBitCount(int bitCount) {
        this.bitCount = bitCount;
    }

    public void setBitConv(int bitConv) {
        this.bitConv = bitConv;
    }

    public void setBImSize(int bImSize) {
        this.bImSize = bImSize;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }

    public void setNeedOffset(boolean needOffset) {
        this.needOffset = needOffset;
    }

    public boolean equals(final Object o) {
        if (o == this) return true;
        if (!(o instanceof NewBMP)) return false;
        final NewBMP other = (NewBMP) o;
        if (!other.canEqual((Object) this)) return false;
        final Object this$CORE = this.getCORE();
        final Object other$CORE = other.getCORE();
        if (this$CORE == null ? other$CORE != null : !this$CORE.equals(other$CORE)) return false;
        final Object this$_3 = this.get_3();
        final Object other$_3 = other.get_3();
        if (this$_3 == null ? other$_3 != null : !this$_3.equals(other$_3)) return false;
        final Object this$_4 = this.get_4();
        final Object other$_4 = other.get_4();
        if (this$_4 == null ? other$_4 != null : !this$_4.equals(other$_4)) return false;
        final Object this$_5 = this.get_5();
        final Object other$_5 = other.get_5();
        if (this$_5 == null ? other$_5 != null : !this$_5.equals(other$_5)) return false;
        if (this.getTYPE_BASE() != other.getTYPE_BASE()) return false;
        if (this.getSIZE_BASE() != other.getSIZE_BASE()) return false;
        if (this.getDATA_OFS_BASE() != other.getDATA_OFS_BASE()) return false;
        if (this.getHEADER_BASE() != other.getHEADER_BASE()) return false;
        if (this.getWIDTH_BASE() != other.getWIDTH_BASE()) return false;
        if (this.getHEIGHT_BASE() != other.getHEIGHT_BASE()) return false;
        if (this.getBIT_COUNT_BASE() != other.getBIT_COUNT_BASE()) return false;
        if (this.getBIT_CONV_BASE() != other.getBIT_CONV_BASE()) return false;
        if (this.getIM_SIZE_BASE() != other.getIM_SIZE_BASE()) return false;
        final Object this$pic = this.getPic();
        final Object other$pic = other.getPic();
        if (this$pic == null ? other$pic != null : !this$pic.equals(other$pic)) return false;
        if (this.getH() != other.getH()) return false;
        if (this.getW() != other.getW()) return false;
        final Object this$mass = this.getMass();
        final Object other$mass = other.getMass();
        if (this$mass == null ? other$mass != null : !this$mass.equals(other$mass)) return false;
        if (!java.util.Arrays.equals(this.getContext(), other.getContext())) return false;
        if (this.getType() != other.getType()) return false;
        if (this.getSize() != other.getSize()) return false;
        if (this.getDataOffset() != other.getDataOffset()) return false;
        if (this.getHeaderSize() != other.getHeaderSize()) return false;
        final Object this$version = this.getVersion();
        final Object other$version = other.getVersion();
        if (this$version == null ? other$version != null : !this$version.equals(other$version)) return false;
        if (this.getBitCount() != other.getBitCount()) return false;
        if (this.getBitConv() != other.getBitConv()) return false;
        if (this.getBImSize() != other.getBImSize()) return false;
        if (this.getOffset() != other.getOffset()) return false;
        if (this.isNeedOffset() != other.isNeedOffset()) return false;
        return true;
    }

    protected boolean canEqual(final Object other) {
        return other instanceof NewBMP;
    }

    public int hashCode() {
        final int PRIME = 59;
        int result = 1;
        final Object $CORE = this.getCORE();
        result = result * PRIME + ($CORE == null ? 43 : $CORE.hashCode());
        final Object $_3 = this.get_3();
        result = result * PRIME + ($_3 == null ? 43 : $_3.hashCode());
        final Object $_4 = this.get_4();
        result = result * PRIME + ($_4 == null ? 43 : $_4.hashCode());
        final Object $_5 = this.get_5();
        result = result * PRIME + ($_5 == null ? 43 : $_5.hashCode());
        result = result * PRIME + this.getTYPE_BASE();
        result = result * PRIME + this.getSIZE_BASE();
        result = result * PRIME + this.getDATA_OFS_BASE();
        result = result * PRIME + this.getHEADER_BASE();
        result = result * PRIME + this.getWIDTH_BASE();
        result = result * PRIME + this.getHEIGHT_BASE();
        result = result * PRIME + this.getBIT_COUNT_BASE();
        result = result * PRIME + this.getBIT_CONV_BASE();
        result = result * PRIME + this.getIM_SIZE_BASE();
        final Object $pic = this.getPic();
        result = result * PRIME + ($pic == null ? 43 : $pic.hashCode());
        result = result * PRIME + this.getH();
        result = result * PRIME + this.getW();
        final Object $mass = this.getMass();
        result = result * PRIME + ($mass == null ? 43 : $mass.hashCode());
        result = result * PRIME + java.util.Arrays.hashCode(this.getContext());
        result = result * PRIME + this.getType();
        result = result * PRIME + this.getSize();
        result = result * PRIME + this.getDataOffset();
        result = result * PRIME + this.getHeaderSize();
        final Object $version = this.getVersion();
        result = result * PRIME + ($version == null ? 43 : $version.hashCode());
        result = result * PRIME + this.getBitCount();
        result = result * PRIME + this.getBitConv();
        result = result * PRIME + this.getBImSize();
        result = result * PRIME + this.getOffset();
        result = result * PRIME + (this.isNeedOffset() ? 79 : 97);
        return result;
    }

    public String toString() {
        return "NewBMP(CORE=" + this.getCORE() + ", _3=" + this.get_3() + ", _4=" + this.get_4() + ", _5=" + this.get_5() + ", TYPE_BASE=" + this.getTYPE_BASE() + ", SIZE_BASE=" + this.getSIZE_BASE() + ", DATA_OFS_BASE=" + this.getDATA_OFS_BASE() + ", HEADER_BASE=" + this.getHEADER_BASE() + ", WIDTH_BASE=" + this.getWIDTH_BASE() + ", HEIGHT_BASE=" + this.getHEIGHT_BASE() + ", BIT_COUNT_BASE=" + this.getBIT_COUNT_BASE() + ", BIT_CONV_BASE=" + this.getBIT_CONV_BASE() + ", IM_SIZE_BASE=" + this.getIM_SIZE_BASE() + ", pic=" + this.getPic() + ", h=" + this.getH() + ", w=" + this.getW() + ", mass=" + this.getMass() + ", context=" + java.util.Arrays.toString(this.getContext()) + ", type=" + this.getType() + ", size=" + this.getSize() + ", dataOffset=" + this.getDataOffset() + ", headerSize=" + this.getHeaderSize() + ", version=" + this.getVersion() + ", bitCount=" + this.getBitCount() + ", bitConv=" + this.getBitConv() + ", bImSize=" + this.getBImSize() + ", offset=" + this.getOffset() + ", needOffset=" + this.isNeedOffset() + ")";
    }

    //private int convRGBtoInt()

}
