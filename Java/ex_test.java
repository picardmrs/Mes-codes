public class AgeInvaide extends Exception{
    public String getMessage(){
        System.out.println("age incorrecte")
    }
}

public class Personne{
    int age; 

    public void Personne(_age){
        if( age < 0 ou age > 150 ){
            throw new getMessage();
        }
        age = _age; 
    }
}

public class Main{
    public static void Main(String args[]){
        try{
            Personne p1 = new Personne(-12);
            Personne p2 = new Personne(13); 
        } catch(AgeInvaide e){
            System.out.println(e.getMessage())
        }
         
    }
    return; 
}









public class TepperatureINvalide extends Exception{
    public void getMessage(){
        System.out.println("Température invalide : doit être entre -50 et 60");
    }
}

public class Thermometre{
    int temp;
    public void Thermometre(_temp){
        if( -50 > _temp or _temp > 60 ){
            throw new getMessage();
        }
        temp = _temp;
    }

    public int getTemperature(){
        return temp; 
    }
}

pblic class Main{
    public static void Main(String args[]){
        try{
            Thermometre t1 = new Thermometre(11);
            Thermometre t2 = new Thermometre(-80);
        } catch( TepperatureINvalide e){
            System.out.println(e.getMessage())
        }
    } 

}








public void SoldeInsuffisant{
    public void SImessage(){
        System.out.println("Solde insuffisant pour ce retrait");
    }
} 

public void MontantInvalide{
    public void MImessage(){
        System.out.println("Le montant doit être positif");
    }
} 

public void CompteBacaire{
    private double solde;

    public CompteBacaire(double solde){
        if(solde < 0){
            throw new MontantInvalide();
        }
        solde = this.solde;
    }

    public retirer(double montant){
        if(0 > solde -montant){
            throw new SImessage();
        } 
            
        elif( 0 > montant){
            throw new MImessage();
        }
        else{
            solde = solde -montant;
        }
    }

    public double getSolde(){
        return Solde;
    }
}

public Main{
    public static void main{String args[]}{
        try{
            CompteBacaire c1 = new CompteBacaire(100);
            CompteBacaire c2 = new CompteBacaire(100);

            c1.retirer(50);
            c2.retirer(150);
            c1.retirer(-10);
        } catch( SoldeInsuffisant e){
            System.out.println(e.SImessage())
        } catch( MontantInvalide e){
            System.out.println(e.MImessage())
        }
    }
}






public class Buffer{
    private int valeur;
    private boolean plein;

    public synchronized void produire() throws InterruptedException {
        while( plein){
            this.wait();
        }
        this.valeur++;
        plein = true;
        this.notify();
    }

    public synchronized void consommer() throws InterruptedException {
        while(! plein){
            this.wait();
        }            
        this.valeur--;
        plein = false;
        this.notify();
    }
}

public class Producteur implements Runnable{
    Buffer b;

    public Producteur(Buffer b){
        this.b = b;
    }
    
    public void run(){
        for( int i = 0 ; i < 5; i ++){
            b.produire()
        }
    }
}

public class Consommateur implements Runnable{
    Buffer b;

    public Consommateur(Buffer b){
        this.b = b;
    }

    public void run(){
        for( int i = 0 ; i < 5; i ++){
            b.consommer()
        }
    }
}

public class Main{
    Buffer buffer = new Buffer();
    public static void main(String args[]) throws InteruptedException{
        Thread produire = new Thread(new Producteur(this.buffer));
        Thread consommer = new Thread(new Consommateur(this.buffer));
        produire.start();
        consommer.start();
    }
}



// exemple 


// 1. Classe partagée — contient toute la logique de synchronisation
public class ObjetPartage {
    private boolean etat = false;

    public synchronized void tache1() throws InterruptedException {
        while (etat) {
            this.wait();
        }
        // faire le travail
        etat = true;
        this.notify();
    }

    public synchronized void tache2() throws InterruptedException {
        while (!etat) {
            this.wait();
        }
        // faire le travail
        etat = false;
        this.notify();
    }
}

// 2. Thread 1
public class Thread1 extends Thread {
    ObjetPartage obj;

    public Thread1(ObjetPartage obj) {
        this.obj = obj;
    }

    public void run() {
        for (int i = 0; i < 5; i++) {
            try {
                obj.tache1();
            } catch (InterruptedException e) {}
        }
    }
}

// 3. Thread 2
public class Thread2 extends Thread {
    ObjetPartage obj;

    public Thread2(ObjetPartage obj) {
        this.obj = obj;
    }

    public void run() {
        for (int i = 0; i < 5; i++) {
            try {
                obj.tache2();
            } catch (InterruptedException e) {}
        }
    }
}

// 4. Main
public class Main {
    public static void main(String[] args) {
        ObjetPartage obj = new ObjetPartage();  // objet partagé créé ici
        Thread1 t1 = new Thread1(obj);          // même objet passé aux deux
        Thread2 t2 = new Thread2(obj);
        t1.start();
        t2.start();
    }
}