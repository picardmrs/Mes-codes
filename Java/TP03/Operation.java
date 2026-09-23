class Operation {
    private String type;
    private String dateOperation;
    private double montant;
    private String libelle;

    public Operation(String type, String dateOperation, double montant, String libelle) {
        this.type = type;
        this.dateOperation = dateOperation;
        this.montant = montant;
        this.libelle = libelle;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getDateOperation() {
        return dateOperation;
    }

    public void setDateOperation(String dateOperation) {
        this.dateOperation = dateOperation;
    }

    public double getMontant() {
        return montant;
    }

    public void setMontant(double montant) {
        this.montant = montant;
    }

    public String getLibelle() {
        return libelle;
    }

    public void setLibelle(String libelle) {
        this.libelle = libelle;
    }

    @Override
    public String toString() {
        return "Operation{" +
                "type='" + type + '\'' +
                ", dateOperation='" + dateOperation + '\'' +
                ", montant=" + montant +
                ", libelle='" + libelle + '\'' +
                '}';
    }
}