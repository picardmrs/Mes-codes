import java.io.*;

public class Lecture{
    private int numeroLigne = 1; 
    private String textLigne;
    private String cheminFichier = "./document.txt";

    public void afficheNumLigne(int numeroLigne){
        for(int i = 0; i <= 3 - numeroLigne/10; i++){
            System.out.print("0");
        }
        System.out.print(numeroLigne); 
    }

    public void afficheTextLigne(String textLigne){
        try {
            BufferedReader bur = new BufferedReader(new FileReader(cheminFichier));
            
            while ((textLigne = bur.readLine()) != null){
                int debut = 0;

                while (debut < textLigne.length()) {
                    afficheNumLigne(this.numeroLigne);
                    System.out.print(" ");
                    int fin = Math.min(debut + 60, textLigne.length());
                    System.out.println(textLigne.substring(debut, fin));
                    this.numeroLigne++;
                    debut = fin;
                }
            }
            bur.close();
        } catch (IOException e) {
            System.err.println("Erreur de lecture : " + e.getMessage());
        }
    }

    public static void main(String[] args){
        Lecture lecture = new Lecture();
        lecture.afficheTextLigne("");
    }
}