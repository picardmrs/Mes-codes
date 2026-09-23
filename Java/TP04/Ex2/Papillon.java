import java.io.*;

public class Papillon{
    private int n = 11;

    public static void main(String[] args){
        Papillon papillon = new Papillon();
        papillon.ecrirePapillon(); 
    }

    public String ecrireLigne(int n, int numLigne, String ligne){
        ligne = "";
        for( int i = 0 ; i <= numLigne ; i++){
            ligne = ligne + "▓";
        }
        for( int i = 0 ; i < n-2*numLigne-2 ; i++){
            ligne = ligne + " ";
        }
        for( int i = 0 ; i <= numLigne ; i++){
            ligne = ligne + "▓";
        }
        return ligne;
    }

    public void ecrirePapillon(){
        String ligne = ""; 

        try{
            BufferedWriter buw = new BufferedWriter(new FileWriter("papillon.txt"));
            int nbLignes = (n + 1) / 2;
            // Moitié supérieure
            for (int numLigne = 0 ; numLigne < nbLignes ; numLigne++){
                ligne = ecrireLigne(n, numLigne, ligne);
                buw.write(ligne);
                buw.newLine();
            }
            // Moitié inférieure
            for (int numLigne = nbLignes - 2 ; numLigne >= 0 ; numLigne--){
                ligne = ecrireLigne(n, numLigne, ligne);
                buw.write(ligne);
                buw.newLine();
            }
            buw.close();
        } catch (IOException e) {
            System.err.println("Erreur de lecture : " + e.getMessage());
        }
    }
}