public class Nombre implements Runnable {
    private Gestion gestion;

    public Nombre(Gestion gestion) {
        this.gestion = gestion;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            try {
                gestion.afficherNombre(i);
                Thread.sleep(700);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
