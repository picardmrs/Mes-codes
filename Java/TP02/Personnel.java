class Personnel{
    private String prenom;
    private String nom;
    private int salaire;
    private MaDate date;
    private Adresse adresse;

    private Personnel(String prenom, String nom, int salaire, MaDate d, Adresse a){
        this.prenom = prenom;
        this.nom = nom;
        this.salaire = salaire;
        date = d;
        adresse = a;
    }

    private String identite(){
        return prenom + " " + nom;
    }

    private void affiche(){
        System.out.print("Identité : ");
        identite();
        System.out.println();

        System.out.print("Date de naissance : ");
        date.votreDate();
        System.out.println();

        System.out.print("Adresse : ");
        adresse.Coordonnee();
        System.out.println();
    }

    private void changerAdresse(Adresse NouvelleAdresse){
        this.adresse = NouvelleAdresse;
    }

    public int getSalaire(){
        return salaire;
    }
}