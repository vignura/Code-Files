package com.example.OOPChalange;

import java.util.Scanner;

public class Eye extends Organ{
    private String color;
    private boolean isEyeOpened;

    public Eye(String name, String medicalCondition, String color) {
        super(name, medicalCondition);
        this.color = color;
    }

    public Eye(String name, String medicalCondition, String color, boolean isEyeOpened) {
        super(name, medicalCondition);
        this.color = color;
        this.isEyeOpened = isEyeOpened;
    }

    public boolean isEyeOpened() {
        return isEyeOpened;
    }

    public void setEyeOpened(boolean eyeOpened) {
        isEyeOpened = eyeOpened;
        if(eyeOpened) {
            System.out.println("Eye is opened");
        }else{
            System.out.println("Eye is closed");
        }
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public void toggleEye()
    {
        setEyeOpened(!this.isEyeOpened);
    }

    @Override
    public void select() {
        super.select();
        System.out.println("Color: " + this.color);
        System.out.println("\t1. Close the Eye");
        Scanner scanner = new Scanner(System.in);
        int choice  = scanner.nextInt();

        switch (choice)
        {
            case 1:
                setEyeOpened(false);
                break;
        }
    }
}
