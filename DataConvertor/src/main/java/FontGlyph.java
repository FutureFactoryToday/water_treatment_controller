import lombok.Data;

import java.io.IOException;

@Data
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
}
