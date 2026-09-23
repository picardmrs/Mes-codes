import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

abstract class Compte {
    private static int prochainNumeroCompte = 1;

    private Client client;
    private int numeroCompte;
    private double solde;
    private String typeCompte;
    private List<Operation> operations;

    public Compte(Client client, double solde, String typeCompte) {
        this.client = client;
        this.numeroCompte = prochainNumeroCompte++;
        this.solde = solde;
        this.typeCompte = typeCompte;
        this.operations = new ArrayList<>();
        if (this.client != null) {
            this.client.ajouterCompte(this);
        }
    }

    public void deposer(String dateop, double montant, String libelle) {
        if (montant > 0) {
            solde += montant;
            operations.add(new Operation("DEPOT", dateop, montant, libelle));
        }
    }

    public abstract void retrait(String dateop, double montant, String libelle) throws EMontantMinException;

    public List<Operation> getOperations() {
        return Collections.unmodifiableList(operations);
    }

    protected void ajouterOperation(Operation operation) {
        operations.add(operation);
    }

    protected double getSolde() {
        return solde;
    }

    protected void setSolde(double solde) {
        this.solde = solde;
    }

    public int getNumeroCompte() {
        return numeroCompte;
    }

    public Client getClient() {
        return client;
    }

    public String getType() {
        return typeCompte;
    }

    public double consulterSolde() {
        return solde;
    }

    public void Historique(int nombreOperations) {
        System.out.println("Solde du compte: " + solde);
        int debut = Math.max(operations.size() - nombreOperations, 0);
        for (int i = debut; i < operations.size(); i++) {
            System.out.println(operations.get(i));
        }
    }

    @Override
    public String toString() {
        return "client=" + client +
                ", numeroCompte=" + numeroCompte +
                ", type=" + typeCompte +
                ", solde=" + solde;
    }
}