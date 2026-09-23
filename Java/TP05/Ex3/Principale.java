public class Principale {
    public static void main(String[] args) {
        TamponLineaire tampon = new TamponLineaire(10);

        Producteur p = new Producteur(10, tampon, 500);
        Consommateur c1 = new Consommateur(tampon, 700, "Consommateur1");
        Consommateur c2 = new Consommateur(tampon, 1000, "Consommateur2");

        p.start();
        c1.start();
        c2.start();
    }
}
