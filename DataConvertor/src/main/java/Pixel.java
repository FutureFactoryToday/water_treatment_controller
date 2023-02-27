public class Pixel {
    private final int B;
    private final int G;
    private final int R;
    private final int offset;
    private final boolean needOffset;
    private int _16bitColor;
    public Pixel(int b, int g, int r, int offset, boolean needOffset) {
        B = b;
        G = g;
        R = r;

        this.offset = offset;
        this.needOffset = needOffset;
        to16BitColor();
    }
    public String toColor(){
        int newR = conv5to8((_16bitColor & 0xF800) >> 11);
        int newG = conv6to8((_16bitColor & 0x07E0) >> 5);
        int newB = conv5to8((_16bitColor & 0x001F));

        return "rgb(" +
                newR + "," + newG + "," + newB + ")";
    }
    public boolean isWhite(){
        return (R > 150) &&  (B > 150) && (G > 150);
    }

    public String toR5G6B5 (){

        return String.format("%4x",_16bitColor& 0xFFFF).replace(" ","0");
    }

    private void to16BitColor(){
        if (needOffset) {
            int rOffset = (offset & 0xF800) >> 11;
            int gOffset = (offset & 0x07E0) >> 5;
            int bOffset = (offset & 0x001F);
            _16bitColor = ((0x1F & (conv8to5(R) + rOffset))<<11);
            _16bitColor |= ((0x3F & (conv8to6(G) + gOffset))<<5);
            _16bitColor |= (0x1F & (conv8to5(B) + bOffset));
        } else {
            _16bitColor = (conv8to5(R)<<11);
            _16bitColor |= (conv8to6(G)<<5);
            _16bitColor |= (conv8to5(B));
        }
    }


    public static int conv8to5(int b) {
        int res;
        double mod = (1 << 5) - 1;
        b = b & 0xFF;
        res = (int) Math.round (b * mod / 0xff);
        return res & 0x1F;
    }

    public static int conv8to6(int b) {
        int res;
        double mod = (1 << 6) - 1;
        b = b & 0xFF;
        res =(int) Math.round (b * mod / 0xff);
        return res & 0x3F;
    }

    public static int conv5to8(int b) {
        int res;
        double mod = (1 << 5) - 1;
        b = b & 0xFF;
        res = (int) Math.round (b * 0xFF / mod);
        return res ;
    }

    public static int conv6to8(int b) {
        int res;
        double mod = (1 << 6) - 1;
        b = b & 0xFF;
        res = (int) Math.round (b * 0xff / mod);
        return res ;
    }
}
