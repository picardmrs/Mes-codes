import java.time.LocalDate;

class CompteEpargne extends Compte {
    private static final double TAUX_INTERET = 0.03;

    private double depotMinimal;

    public CompteEpargne(Client client, double solde, double depotMinimal) {
        super(client, solde, "Epargne");
        this.depotMinimal = depotMinimal;
    }
                                                                                                                    
    @Override
    public void retrait(String dateop, double montant, String libelle) throws EMontantMinException {
        if (montant > getSolde()) {
            throw new EMontantMinException("Montant superieur au solde du compte.");
        }
        if (montant > 0 && (getSolde() - montant) >= depotMinimal) {
            setSolde(getSolde() - montant);
            ajouterOperation(new Operation("RETRAIT", dateop, montant, libelle));
        } else {
            System.out.println("Retrait impossible: depot minimal non respecte.");
        }
    }

    public double CalculInterets() {
        double interets = getSolde() * TAUX_INTERET;
        deposer(LocalDate.now().toString(), interets, "Versement interets");
        return interets;
    }

    public double getDepotMinimal() {
        return depotMinimal;
    }

    public double getTauxInteret() {
        return TAUX_INTERET;
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
