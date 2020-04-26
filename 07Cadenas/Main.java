/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg7;

import java.util.Random;

//public class Main {   
    //public static String[] main(String[] args) {
     // public static String[] generateRandomWords(int numberOfWords)
public class Main {
    public static String generador (int numberOfWords) {
        String resultado = new String();
        Random random = new Random();
        for(int i = 0; i < numberOfWords; i++)
        {
            char[] word = new char[3]; // words of length 3 through 10. (1 and 2 letter words are boring.)
            for(int j = 0; j < word.length; j++)
            {
                word[j] = (char)('A' + random.nextInt(26));
            }
            resultado += new String(word) + " ";
        }
        return resultado;
    }
    
    public static void main(String[] args) {
       String cadenota = generador(100000);
       boolean tiene = cadenota.contains("IPN");
        System.out.println(tiene);
    }
}

                
                
                
               // System.out.println("Tamaño de la cadena: " +   random_word.length() + " caracteres");
                





