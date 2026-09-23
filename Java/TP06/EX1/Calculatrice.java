import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Calculatrice extends JFrame {

    private JTextField champA, champB, fieldOp, fieldRes;

    public Calculatrice() {
        setTitle("Mini calculatrice");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(10, 10));

        JPanel panelHaut = new JPanel(new FlowLayout());
        panelHaut.add(new JLabel("a :"));
        champA = new JTextField(5);
        panelHaut.add(champA);
        panelHaut.add(new JLabel("b :"));
        champB = new JTextField(5);
        panelHaut.add(champB);
        add(panelHaut, BorderLayout.NORTH);

        JPanel panelBoutons = new JPanel(new FlowLayout());
        JButton btnAdd = new JButton("a + b");
        JButton btnSub = new JButton("a - b");
        JButton btnMul = new JButton("a * b");
        JButton btnDiv = new JButton("a / b");
        panelBoutons.add(btnAdd);
        panelBoutons.add(btnSub);
        panelBoutons.add(btnMul);
        panelBoutons.add(btnDiv);
        add(panelBoutons, BorderLayout.CENTER);

        JPanel panelBas = new JPanel(new FlowLayout());
        panelBas.add(new JLabel("Opération :"));
        fieldOp = new JTextField(10);
        fieldOp.setEditable(false);
        panelBas.add(fieldOp);
        panelBas.add(new JLabel("Résultat :"));
        fieldRes = new JTextField(10);
        fieldRes.setEditable(false);
        panelBas.add(fieldRes);
        add(panelBas, BorderLayout.SOUTH);

        btnAdd.addActionListener(e -> additionner());
        btnSub.addActionListener(e -> soustraire());
        btnMul.addActionListener(e -> multiplier());

        btnDiv.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                diviser();
            }
        });

        JMenuBar menuBar = new JMenuBar();

        JMenu menuApp = new JMenu("Application");
        JMenuItem itemInit = new JMenuItem("Initialiser");
        itemInit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_I, InputEvent.CTRL_DOWN_MASK));
        itemInit.addActionListener(e -> initialiser());
        JMenuItem itemQuitter = new JMenuItem("Quitter");
        itemQuitter.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, InputEvent.CTRL_DOWN_MASK));
        itemQuitter.addActionListener(e -> System.exit(0));
        menuApp.add(itemInit);
        menuApp.add(itemQuitter);

        JMenu menuOp = new JMenu("Opérations");
        menuOp.setMnemonic(KeyEvent.VK_O);
        JMenuItem itemAdd = new JMenuItem("Addition");
        itemAdd.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Z, InputEvent.CTRL_DOWN_MASK));
        itemAdd.addActionListener(e -> additionner());
        JMenuItem itemSub = new JMenuItem("Soustraction");
        itemSub.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, InputEvent.CTRL_DOWN_MASK));
        itemSub.addActionListener(e -> soustraire());
        JMenuItem itemMul = new JMenuItem("Multiplication");
        itemMul.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_M, InputEvent.CTRL_DOWN_MASK));
        itemMul.addActionListener(e -> multiplier());
        JMenuItem itemDiv = new JMenuItem("Division");
        itemDiv.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_D, InputEvent.CTRL_DOWN_MASK));
        itemDiv.addActionListener(e -> diviser());
        menuOp.add(itemAdd);
        menuOp.add(itemSub);
        menuOp.add(itemMul);
        menuOp.add(itemDiv);

        JMenu menuAPropos = new JMenu("A propos");
        JMenuItem itemInfo = new JMenuItem("Info");
        itemInfo.addActionListener(e -> JOptionPane.showMessageDialog(this,
                "Application créée par Marius Picard", "Information", JOptionPane.INFORMATION_MESSAGE));
        menuAPropos.add(itemInfo);

        menuBar.add(menuApp);
        menuBar.add(menuOp);
        menuBar.add(menuAPropos);
        setJMenuBar(menuBar);

        setSize(400, 200);
        setVisible(true);
    }

    private void additionner() {
        try {
            double a = Double.parseDouble(champA.getText());
            double b = Double.parseDouble(champB.getText());
            fieldOp.setText("Addition");
            fieldRes.setText(String.valueOf(a + b));
        } catch (NumberFormatException e) {
            fieldRes.setText("saisie invalide");
        }
    }

    private void soustraire() {
        try {
            double a = Double.parseDouble(champA.getText());
            double b = Double.parseDouble(champB.getText());
            fieldOp.setText("Soustraction");
            fieldRes.setText(String.valueOf(a - b));
        } catch (NumberFormatException e) {
            fieldRes.setText("saisie invalide");
        }
    }

    private void multiplier() {
        try {
            double a = Double.parseDouble(champA.getText());
            double b = Double.parseDouble(champB.getText());
            fieldOp.setText("Multiplication");
            fieldRes.setText(String.valueOf(a * b));
        } catch (NumberFormatException e) {
            fieldRes.setText("saisie invalide");
        }
    }

    private void diviser() {
        try {
            double a = Double.parseDouble(champA.getText());
            double b = Double.parseDouble(champB.getText());
            fieldOp.setText("Division");
            if (b == 0) {
                fieldRes.setText("division par zéro");
            } else {
                fieldRes.setText(String.valueOf(a / b));
            }
        } catch (NumberFormatException e) {
            fieldRes.setText("saisie invalide");
        }
    }

    private void initialiser() {
        champA.setText("");
        champB.setText("");
        fieldOp.setText("");
        fieldRes.setText("");
    }

    public static void main(String[] args) {
        new Calculatrice();
    }
}
