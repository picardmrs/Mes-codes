import java.io.*;

public class Producteur extends Thread{
    int n ; 
    TamponLineaire tampon;
    int temp;

    public Producteur(int nb_article, TamponLineaire tampon, int temp){
        this.n = nb_article;
        this.tampon = tampon;
        this.temp = temp;
    }

    public void run(){
        for(int current = 0; current < n; current++){
            try{
                tampon.deposer("article "+current);
                Thread.sleep(temp);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }    
}