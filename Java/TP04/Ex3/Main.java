import java.io.*;
import java.util.*;

public class Main {

    public static void sauvegarderClasse(ArrayList<Etudiant> liste) {
        try {
            ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("classe.dat"));
            oos.writeObject(liste);
            oos.close();
        } catch (IOException e) {
            System.out.println("Erreur sauvegarde : " + e.getMessage());
        }
    }

    public static ArrayList<Etudiant> chargerClasse() {
        File f = new File("classe.dat");
        if (!f.exists()) return new ArrayList<>();
        try {
            ObjectInputStream ois = new ObjectInputStream(new FileInputStream("classe.dat"));
            ArrayList<Etudiant> liste = (ArrayList<Etudiant>) ois.readObject();
            ois.close();
            return liste;
        } catch (Exception e) {
            return new ArrayList<>();
        }
    }

    public static Etudiant trouverEtudiant(ArrayList<Etudiant> liste, int code) {
        for (int i = 0; i < liste.size(); i++) {
            if (liste.get(i).getCode() == code) return liste.get(i);
        }
        return null;
    }

    public static void ajtEtudiant(ArrayList<Etudiant> liste, Scanner sc) {
        System.out.print("Nom : ");
        String nom = sc.next();
        System.out.print("Prénom : ");
        String prenom = sc.next();
        System.out.print("Moyenne : ");
        float moyenne = sc.nextFloat();

        Etudiant e = new Etudiant(nom, prenom, moyenne);

        for (int i = 0; i < liste.size(); i++) {
            if (liste.get(i).getCode() == e.getCode()) {
                System.out.println("Erreur : code déjà présent dans la liste.");
                return;
            }
        }
        liste.add(e);
        sauvegarderClasse(liste);
        System.out.println("Etudiant ajouté. Code : " + e.getCode());
    }

    public static void mdfEtudiant(ArrayList<Etudiant> liste, int code, Scanner sc) {
        Etudiant e = trouverEtudiant(liste, code);
        if (e == null) { System.out.println("Etudiant introuvable."); return; }

        System.out.println("Que voulez-vous modifier ? 1.Nom  2.Prénom  3.Moyenne");
        int choix = sc.nextInt();
        switch (choix) {
            case 1: System.out.print("Nouveau nom : ");    e.setNom(sc.next());           break;
            case 2: System.out.print("Nouveau prénom : "); e.setPrenom(sc.next());        break;
            case 3: System.out.print("Nouvelle moyenne : "); e.setMoyenne(sc.nextFloat()); break;
        }
        sauvegarderClasse(liste);
        System.out.println("Etudiant modifié.");
    }

    public static void infoEtudiant(ArrayList<Etudiant> liste, Scanner sc) {
        System.out.println("Rechercher par : 1.Code  2.Nom");
        int choix = sc.nextInt();
        Etudiant e = null;

        if (choix == 1) {
            System.out.print("Code : ");
            e = trouverEtudiant(liste, sc.nextInt());
        } else if (choix == 2) {
            System.out.print("Nom : ");
            String nom = sc.next();
            for (int i = 0; i < liste.size(); i++) {
                if (liste.get(i).getNom().equalsIgnoreCase(nom)) { e = liste.get(i); break; }
            }
        }

        if (e == null) { System.out.println("Etudiant introuvable."); return; }
        System.out.println("Code    : " + e.getCode());
        System.out.println("Nom     : " + e.getNom());
        System.out.println("Prénom  : " + e.getPrenom());
        System.out.println("Moyenne : " + e.getMoyenne());
        System.out.println("Réussi  : " + e.isReussi());
        System.out.println("Rachat  : " + e.isZoneRachat());
    }

    public static void supprEtudiant(ArrayList<Etudiant> liste, int code) {
        Etudiant e = trouverEtudiant(liste, code);
        if (e == null) { System.out.println("Etudiant introuvable."); return; }
        liste.remove(e);
        sauvegarderClasse(liste);
        System.out.println("Etudiant supprimé.");
    }

    public static void genererRapport(ArrayList<Etudiant> liste) {
        if (liste.isEmpty()) { System.out.println("Liste vide."); return; }

        // Fichier succesStudent.dat (seulement si plus de 7 étudiants)
        if (liste.size() > 7) {
            try {
                ArrayList<Etudiant> succes = new ArrayList<>();
                for (int i = 0; i < liste.size(); i++) {
                    if (liste.get(i).isReussi()) succes.add(liste.get(i));
                }
                ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("succesStudent.dat"));
                oos.writeObject(succes);
                oos.close();
            } catch (IOException e) {
                System.out.println("Erreur succesStudent.dat : " + e.getMessage());
            }
        }

        // Fichier rachatStudent.dat
        try {
            ArrayList<Etudiant> rachat = new ArrayList<>();
            for (int i = 0; i < liste.size(); i++) {
                if (liste.get(i).isZoneRachat()) rachat.add(liste.get(i));
            }
            ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("rachatStudent.dat"));
            oos.writeObject(rachat);
            oos.close();
        } catch (IOException e) {
            System.out.println("Erreur rachatStudent.dat : " + e.getMessage());
        }

        // Calcul max, min, moyenne classe
        Etudiant max = liste.get(0);
        Etudiant min = liste.get(0);
        float somme = 0;
        for (int i = 0; i < liste.size(); i++) {
            Etudiant e = liste.get(i);
            if (e.getMoyenne() > max.getMoyenne()) max = e;
            if (e.getMoyenne() < min.getMoyenne()) min = e;
            somme += e.getMoyenne();
        }
        float moyenneClasse = somme / liste.size();

        // Fichier etatClasse.txt
        try {
            PrintWriter pw = new PrintWriter(new FileWriter("etatClasse.txt"));
            pw.println(max.getNom() + " " + max.getPrenom() + " " + max.getMoyenne());
            pw.println(min.getNom() + " " + min.getPrenom() + " " + min.getMoyenne());
            pw.println(moyenneClasse);
            pw.println("Picard Marius Groupe4");
            pw.close();

            // Affichage du rapport
            System.out.println("=== Etat de la classe ===");
            System.out.println("Max : " + max.getNom() + " " + max.getPrenom() + " -> " + max.getMoyenne());
            System.out.println("Min : " + min.getNom() + " " + min.getPrenom() + " -> " + min.getMoyenne());
            System.out.println("Moyenne classe : " + moyenneClasse);
            System.out.println("Rapport sauvegardé dans etatClasse.txt");
        } catch (IOException e) {
            System.out.println("Erreur etatClasse.txt : " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        ArrayList<Etudiant> liste = chargerClasse();
        Scanner sc = new Scanner(System.in);
        int choix = 0;

        do {
            System.out.println("\n1. Ajouter un étudiant");
            System.out.println("2. Modifier un étudiant");
            System.out.println("3. Chercher un étudiant");
            System.out.println("4. Supprimer un étudiant");
            System.out.println("5. Générer rapport");
            System.out.println("0. Quitter");
            System.out.print("Votre choix : ");
            choix = sc.nextInt();

            switch (choix) {
                case 1: ajtEtudiant(liste, sc); break;
                case 2:
                    System.out.print("Code de l'étudiant à modifier : ");
                    mdfEtudiant(liste, sc.nextInt(), sc);
                    break;
                case 3: infoEtudiant(liste, sc); break;
                case 4:
                    System.out.print("Code de l'étudiant à supprimer : ");
                    supprEtudiant(liste, sc.nextInt());
                    break;
                case 5: genererRapport(liste); break;
            }
        } while (choix != 0);

        sc.close();
    }
}
