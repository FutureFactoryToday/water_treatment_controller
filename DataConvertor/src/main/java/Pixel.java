public class Pixel {
    private int B;
    private int G;
    private int R;

    public Pixel(int b, int g, int r) {
        B = b;
        G = g;
        R = r;
    }
    public String toColor(){
        return "rgb(" +
                R + "," + G + "," + B + ")";
    }
    public boolean isWhite(){
        return (R > 150) &&  (B > 150) && (G > 150);
    }

    public String toR5G6B5 (){
        int sh = (conv8to5(R)<<11);
        sh |= (conv8to6(G)<<5);
        sh |= (conv8to5(B));
        return String.format("%4x",sh& 0xFFFF).replace(" ","0");
    }

    private int conv8to5(int b) {
        int res;
        double mod = (1 << 5) - 1;
        b = b & 0xFF;
        res = (int) (b * mod / 0xff);
        return res;
    }

    private int conv8to6(int b) {
        int res;
        double mod = (1 << 6) - 1;
        b = b & 0xFF;
        res = (int) (b * mod / 0xff);
        return res;
    }
}
