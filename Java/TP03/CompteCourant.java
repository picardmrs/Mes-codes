class CompteCourant extends Compte {

	public CompteCourant(Client client) {
		super(client, 0, "Courant");
	}

	public CompteCourant(Client client, double solde) {
		super(client, solde, "Courant");
	}

	@Override
	public void retrait(String dateop, double montant, String libelle) throws EMontantMinException {
		if (montant > getSolde()) {
			throw new EMontantMinException("Montant superieur au solde du compte.");
		}
		if (montant > 0) {
			setSolde(getSolde() - montant);
			ajouterOperation(new Operation("RETRAIT", dateop, montant, libelle));
		} else {
			System.out.println("Retrait impossible");
		}
	}

	@Override
	public String toString() {
		return super.toString();
	}

    
}