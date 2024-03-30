package Helpers;

import DataClasses.NewBMP;

import java.io.IOException;

public class FontGlyph {
    int w;
    int h;
    short[][] glyph;

    public FontGlyph(NewBMP src) {
        w = src.getW();
        h = src.getH();
        int newW = w / 8;
        if (w % 8 != 0) {
            newW++;
        }
        glyph = new short[h][newW];
        int pixCnt = 0;
        short pixBuf = 0;
        int bufW = 0;

        for (int cntH = 0; cntH < h; cntH++) {
            for (int cntW = 0; cntW < w; cntW++) {
                short pixD = (short) ((src.getMass().get(cntH * w + cntW).isWhite()) ? 0 : 1);
                pixBuf = (short) (pixBuf << 1);
                pixBuf = (short) (pixBuf + pixD);

                pixCnt++;
                if (pixCnt == 8) {
                    glyph[cntH][bufW] = pixBuf;
                    pixBuf = 0;
                    pixCnt = 0;
                    bufW++;
                }
            }
            if (w % 8 != 0) {
                glyph[cntH][bufW] = pixBuf;
            }
            while (pixCnt % 8 != 0) {
                pixCnt++;
                glyph[cntH][bufW] = (short) (glyph[cntH][bufW] << 1);
            }
            bufW = 0;
            pixBuf = 0;
            pixCnt = 0;
        }
    }

    ;


    public String getServiceData() {
        return null;
    }

    public static void test() throws IOException {
        NewBMP bmp = new NewBMP("c:\\test.bmp");
        FontGlyph gl = new FontGlyph(bmp);
    }

    public int getW() {
        return this.w;
    }

    public int getH() {
        return this.h;
    }

    public short[][] getGlyph() {
        return this.glyph;
    }

    public void setW(int w) {
        this.w = w;
    }

    public void setH(int h) {
        this.h = h;
    }

    public void setGlyph(short[][] glyph) {
        this.glyph = glyph;
    }

    public boolean equals(final Object o) {
        if (o == this) return true;
        if (!(o instanceof FontGlyph)) return false;
        final FontGlyph other = (FontGlyph) o;
        if (!other.canEqual((Object) this)) return false;
        if (this.getW() != other.getW()) return false;
        if (this.getH() != other.getH()) return false;
        if (!java.util.Arrays.deepEquals(this.getGlyph(), other.getGlyph())) return false;
        return true;
    }

    protected boolean canEqual(final Object other) {
        return other instanceof FontGlyph;
    }

    public int hashCode() {
        final int PRIME = 59;
        int result = 1;
        result = result * PRIME + this.getW();
        result = result * PRIME + this.getH();
        result = result * PRIME + java.util.Arrays.deepHashCode(this.getGlyph());
        return result;
    }

    public String toString() {
        return "FontGlyph(w=" + this.getW() + ", h=" + this.getH() + ", glyph=" + java.util.Arrays.deepToString(this.getGlyph()) + ")";
    }
}
