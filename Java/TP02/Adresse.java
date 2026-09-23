class Adresse{
    private int numero;
    private String rue;
    private String cp;
    private String ville;

    private Adresse(int numero, String rue, String cp , String ville ){
        this.numero = numero;
        this.rue = rue ;
        this.cp = cp;
        this.ville = ville;
    }

    public String Coordonnee() {
        private int etoile_rue;
        private int etoile_cp;
        private int etoile_ville;
        private String a_total;

        a_total = numero + " rue " + rue;
        etoile_rue = length(rue);
        while(etoile_rue <= 30){
            a_total = a_total + "*";
        }
        a_total = a_total + cp
        etoile_cp = length(cp);
        while(etoile_cp <= 6){
            a_total = a_total + "*";
        }
        a_total = a_total + ville;
        etoile_ville = length(ville);
        while(etoile_ville <= 20){
            a_total = a_total + "*";
        }

        return a_total;
    }
}