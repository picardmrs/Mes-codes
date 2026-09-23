import java.io.*;

public class Principale{
    public static void main(String args[]){

        Gestion gestion = new Gestion();
        Lettre lettre = new Lettre(gestion);
        Nombre nombre = new Nombre(gestion);

        Thread t1 = new Thread(lettre);
        Thread t2 = new Thread(nombre);

        t1.start();
        t2.start();

        return; 
    }
}