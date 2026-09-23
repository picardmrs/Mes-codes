import java.sql.*;
import java.util.ArrayList;

public class AppData {

    private static final String URL = "jdbc:postgresql://postgres.ecole.ensicaen.fr:5432/cinema";
    private static final String USER = "picard";
    private static final String PASSWORD = "ensicaen";

    private Connection conn;

    public AppData() {
        try {
            conn = DriverManager.getConnection(URL, USER, PASSWORD);
        } catch (SQLException e) {
            System.out.println("Erreur connexion : " + e.getMessage());
        }
    }

    public Object[][] getTousFilms() {
        try {
            Statement st = conn.createStatement();
            ResultSet rs = st.executeQuery("SELECT titre, anneesortie, resume FROM films");
            ArrayList<Object[]> liste = new ArrayList<>();
            while (rs.next()) {
                Object[] row = {rs.getString("titre"), rs.getInt("anneesortie"), rs.getString("resume")};
                liste.add(row);
            }
            return liste.toArray(new Object[0][]);
        } catch (SQLException e) {
            System.out.println("Erreur : " + e.getMessage());
            return new Object[0][3];
        }
    }

    public Object[][] rechercherFilm(String titre) {
        try {
            PreparedStatement ps = conn.prepareStatement(
                "SELECT titre, anneesortie, resume FROM films WHERE titre LIKE ?");
            ps.setString(1, "%" + titre + "%");
            ResultSet rs = ps.executeQuery();
            ArrayList<Object[]> liste = new ArrayList<>();
            while (rs.next()) {
                Object[] row = {rs.getString("titre"), rs.getInt("anneesortie"), rs.getString("resume")};
                liste.add(row);
            }
            return liste.toArray(new Object[0][]);
        } catch (SQLException e) {
            System.out.println("Erreur : " + e.getMessage());
            return new Object[0][3];
        }
    }
}
