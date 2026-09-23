public class Gestion {
    private boolean turn = false;

    public Gestion() {
        turn = false;
    }

    public synchronized void afficherNombre(int n) throws InterruptedException {
        if (turn == true) {
            this.wait();
        }
        System.out.println(n);
        turn = true;
        this.notify();
    }

    public synchronized void afficherLettre(int n) throws InterruptedException {
        if (turn == false) {
            this.wait();
        }
        char lettre = (char)('A' + n - 1);
        if (n % 2 == 0) {
            System.out.println(Character.toLowerCase(lettre));
        } else {
            System.out.println(Character.toUpperCase(lettre));
        }
        turn = false;
        this.notify();
    }
}
