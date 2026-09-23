import java.io.*;

public class TamponLineaire{
    String[] tab;
    int size;
    int current = 0;

    public TamponLineaire(int taille){
        this.tab = new String[taille];
        this.size = taille;
    }

    void deposer(String object){
        tab[current] = object;
        current++;
        return;
    }

    String prelever(){
        String prelever = tab[current];
        current--;
        return prelever;
    }
}