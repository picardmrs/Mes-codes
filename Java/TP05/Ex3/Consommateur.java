public class Consommateur extends Thread{
    TamponLineaire tampon;
    int temp;
    String nom;

    public Consommateur(TamponLineaire tampon, int temp, String nom){
        this.tampon = tampon;
        this.temp = temp;
        this.nom = nom;
    }

    public void run(){
        while(true){
            try{
                String article = tampon.prelever();
                System.out.println(nom + " a prélevé : " + article);
                Thread.sleep(temp);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
