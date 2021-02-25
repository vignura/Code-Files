package com.company.guessinggame;

import java.util.Scanner;

public class Main {

    private static final int maxFails = 3;
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("Welcome to the Guessing Game..!");
        System.out.print("enter your name: ");

        String userName = in.next();
        System.out.println("Hello " + userName);
        System.out.print("Shall we begin ? ");

        String choice = in.next();
//        System.out.println("choice: " + choice);
        if(choice.equals("yes") == true){
            int failCount = 0;

            while(failCount < maxFails){
                int randNum = (int) (Math.random() * 10);
                System.out.println("can you guess what's the number ?");
                int usersGuess = in.nextInt();
                if(usersGuess == randNum){
                    System.out.println("your guess is right!. You've won");
                    break;
                }
                else{
                    failCount++;
                    System.out.print("your guess is wrong... ");
                    System.out.println(" [" + randNum + "] ");

                    if(failCount == maxFails){
                        System.out.println("Game Over!!");
                    }
                    else {
                        if (usersGuess > randNum) {
                            System.out.println("guess higher.");
                        } else {
                            System.out.println("guess higher.");
                        }
                    }
                }
            }

        }
        else{
            System.out.println("bye " + userName);
        }

    }
}
