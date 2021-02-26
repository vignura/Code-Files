package com.example.OOPChalange;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        boolean shouldQuit = false;
        HumanBody humanBody = new HumanBody("Tom", 25,
                new Heart("Heart", "stroke"),
                new Eye("Left Eye", "Short sighted", "brown", false),
                new Eye("Right Eye", "Short sighted", "brown", false),
                new Stomach("Stomach", "ulcer"),
                new Skin("Skin", "rashes"));

        System.out.println("Name: " + humanBody.getName());
        System.out.println("Age: " + humanBody.getAge());

        while(!shouldQuit) {
            System.out.println("Choose an Organ: ");
            System.out.println("1. " + humanBody.getHeart().getName());
            System.out.println("2. " + humanBody.getLeftEye().getName());
            System.out.println("3. " + humanBody.getRightEye().getName());
            System.out.println("4. " + humanBody.getStomach().getName());
            System.out.println("5. " + humanBody.getSkin().getName());
            System.out.println("6. Quit");

            Scanner scanner = new Scanner(System.in);
            int choice = scanner.nextInt();
            if (choice != 6) {
                Organ selectedOrgan = humanBody.getSelectedOrgan(choice);
                selectedOrgan.select();
            } else shouldQuit = true;
        }

    }
}
