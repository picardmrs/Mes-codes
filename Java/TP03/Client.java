import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Client {
	private String nomPrenom;
	private String dateNaissance;
	private String adressePostale;
	private String adresseEmail;
	private String telephone1;
	private String telephone2;
	private List<Compte> comptes;
	
	public Client(String nomPrenom, String dateNaissance, String adressePostale, String adresseEmail, String telephone1, String telephone2) {
		this.nomPrenom = nomPrenom;
		this.dateNaissance = dateNaissance;
		this.adressePostale = adressePostale;
		this.adresseEmail = adresseEmail;
		this.telephone1 = telephone1;
		this.telephone2 = telephone2;
		this.comptes = new ArrayList<>();
	}

	public Client(String nomPrenom, String dateNaissance, String adressePostale, String adresseEmail, String telephone1) {
		this(nomPrenom, dateNaissance, adressePostale, adresseEmail, telephone1, null);
	}

	public String getNomPrenom() {
		return nomPrenom;
	}

	public String getDateNaissance() {
		return dateNaissance;
	}

	public String getAdressePostale() {
		return adressePostale;
	}

	public String getAdresseEmail() {
		return adresseEmail;
	}

	public String getTelephone1() {
		return telephone1;
	}

	public String getTelephone2() {
		return telephone2;
	}

	public void ajouterCompte(Compte compte) {
		if (compte != null) {
			comptes.add(compte);
		}
	}

	public List<Compte> getComptes() {
		return Collections.unmodifiableList(comptes);
	}

	@Override
	public String toString() {
		String infoTelephone2 = (telephone2 == null || telephone2.isEmpty()) ? "non renseigne" : telephone2;
		return "Client{" +
				"nomPrenom='" + nomPrenom + '\'' +
				", adresseEmail='" + adresseEmail + '\'' +
				", telephone1='" + telephone1 + '\'' +
				", telephone2='" + infoTelephone2 + '\'' +
				'}';
	}
}