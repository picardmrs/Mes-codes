class MaDate{
    private int j;
    private int m;
    private int a;

    private MaDate(int j, int m, int a){
        this.j = j;
        this.m = m;
        this.a = a;
    }

    public String votreDate() {
        return j + "/" + m + "/" + a;
    }

    public int getj(){
        return j;
    }

    public int getm(){
        return m;
    }

    public int geta(){
        return a;
    }
}