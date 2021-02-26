package com.example.OOPChalange;

import java.util.Scanner;

public class Heart extends Organ {
    private int heartRate;

    public Heart(String name, String medicalCondition) {
        super(name, medicalCondition);
    }

    public int getHeartRate() {
        return heartRate;
    }

    @Override
    public void select() {
        super.select();
        System.out.println("Heart Rate: " + heartRate);
        System.out.println("\t1. Change heart rate: ");
        Scanner scanner = new Scanner(System.in);
        setHeartRate(scanner.nextInt());
    }

    public void setHeartRate(int heartRate) {
        this.heartRate = heartRate;
        System.out.println("heart rate set to " + heartRate);
    }
}
