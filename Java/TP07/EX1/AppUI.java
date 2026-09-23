import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;

public class AppUI extends JFrame {

    private JTextField fieldRecherche;
    private DefaultTableModel model;
    private AppData data;
    private String[] colonnes = {"Titre", "Année", "Resumé"};

    public AppUI() {
        data = new AppData();

        setTitle("Cinématographique");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(5, 5));

        JLabel titre = new JLabel("Base de données Cinématographique", JLabel.CENTER);
        titre.setFont(new Font("Arial", Font.BOLD, 18));
        titre.setForeground(Color.BLUE);
        add(titre, BorderLayout.NORTH);

        JPanel panelRecherche = new JPanel(new FlowLayout());
        panelRecherche.setBorder(BorderFactory.createTitledBorder("Rechercher"));
        fieldRecherche = new JTextField(15);
        JButton btnRechercher = new JButton("Rechercher");
        JButton btnInitialiser = new JButton("Initialiser");
        JButton btnQuitter = new JButton("Quitter");
        panelRecherche.add(fieldRecherche);
        panelRecherche.add(btnRechercher);
        panelRecherche.add(btnInitialiser);
        panelRecherche.add(btnQuitter);

        model = new DefaultTableModel(data.getTousFilms(), colonnes);
        JTable table = new JTable(model);
        JScrollPane scrollPane = new JScrollPane(table);

        JPanel panelCentre = new JPanel(new BorderLayout());
        panelCentre.add(panelRecherche, BorderLayout.NORTH);
        panelCentre.add(scrollPane, BorderLayout.CENTER);
        add(panelCentre, BorderLayout.CENTER);

        btnRechercher.addActionListener(e -> {
            String recherche = fieldRecherche.getText();
            Object[][] resultats = data.rechercherFilm(recherche);
            model.setDataVector(resultats, colonnes);
            if (resultats.length == 0) {
                JOptionPane.showMessageDialog(this, "Film non trouvé !",
                        "Titre " + recherche, JOptionPane.INFORMATION_MESSAGE);
            }
        });

        btnInitialiser.addActionListener(e -> {
            fieldRecherche.setText("");
            model.setDataVector(data.getTousFilms(), colonnes);
        });

        btnQuitter.addActionListener(e -> {
            int rep = JOptionPane.showConfirmDialog(this, "Voulez-vous quitter l'application",
                    "Fin", JOptionPane.YES_NO_OPTION);
            if (rep == JOptionPane.YES_OPTION) System.exit(0);
        });

        setSize(600, 500);
        setVisible(true);
    }

    public static void main(String[] args) {
        new AppUI();
    }
}
