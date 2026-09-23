import java.io.*;

public class Etudiant implements Serializable {
    private static final long serialVersionUID = 1L;
    private int code;
    private String nom;
    private String prenom;
    private float moyenne;

    public int getCode() {
        return code;
    }

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public float getMoyenne() {
        return moyenne;
    }

    public void setMoyenne(float moyenne) {
        this.moyenne = moyenne;
    }

    public boolean isReussi() {
        return moyenne >= 10;
    }

    public boolean isZoneRachat() {
        return moyenne >= 9.00f && moyenne <= 9.99f;
    }

    public Etudiant(String nom, String prenom, float moyenne){
        this.code = nom.charAt(0) + prenom.charAt(0) + nom.length() + prenom.length(); 
        this.nom = nom; 
        this.prenom = prenom; 
        this.moyenne = moyenne; 
    }
}