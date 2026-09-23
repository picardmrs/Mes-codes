class Commercial extends Personnel{
    private MaDate date_arrivee;
    private int montant_vente;

    private void setMontantVente(int montant){
        this.montant_vente = montant;
    }

    public double salaireTotal(){
        int salaire = getSalaire();
        return salaire + montant_vente * 0.05;
    }

    public dureeTravail(){

    }

    public affiche(){
        affiche();
        System.out.println("Montant des ventes : "+ montant_vente);
        System.out.println("Salaire total : "+ salaireTotal());
    }
}