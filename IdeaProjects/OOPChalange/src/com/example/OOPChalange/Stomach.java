package com.example.OOPChalange;

import java.util.Scanner;

public class Stomach extends Organ{
    public Stomach(String name, String medicalCondition) {
        super(name, medicalCondition);
    }
    @Override
    public void select() {
        super.select();
        System.out.println("\t1. Digest");
        Scanner scanner = new Scanner(System.in);
        int choice  = scanner.nextInt();

        switch (choice)
        {
            case 1:
                System.out.println("Digesting has begun");
                break;
        }
    }
}
