Question 1 : 

Counter extends Thread donc Counter herite de Thread (tout sauf le private)

Question 2 : 

Ce programme affiche un message a fois si il n ya pas d'interruptions entre les essais.

Question 3 : 

run() est la méthode qui permet l'affichage tout les sleep time si il n y a pas d'interrupt lors de ces temps là

Question 4 : 

Counter ct1 = new Counter(5, "Hello");
Counter ct2 = new Counter(6, "Bonjour");
ct1.start();
ct2.start();

Question 5 : 
```java 
class Counter implements Runnable {
    private int a;
    private String msg;

    public Counter(int a, String msg) {
        this.a = a;
        this.msg = msg;
    }

    public void run() {
        for (int i = 0; i < a; i++) {
            try {
                Thread.sleep(500);
                System.out.println(msg);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class DoSomeThing {
    public static void main(String[] args) {
        Counter ct1 = new Counter(5, "Hello");
        Counter ct2 = new Counter(6, "Bonjour");
        Thread t1 = new Thread(ct1);
        Thread t2 = new Thread(ct2);
        t1.start();
        t2.start();
        System.out.println("The thread has been started");
    }
}

```
