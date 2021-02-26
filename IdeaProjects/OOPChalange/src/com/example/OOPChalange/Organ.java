package com.example.OOPChalange;

public class Organ {
    private String name;
    private String medicalCondition;

    public Organ(String name, String medicalCondition) {
        this.name = name;
        this.medicalCondition = medicalCondition;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getMedicalCondition() {
        return medicalCondition;
    }

    public void setMedicalCondition(String medicalCondition) {
        this.medicalCondition = medicalCondition;
    }

    public void select(){
        System.out.println("Name: " + this.name);
        System.out.println("Medical Condition: " + this.medicalCondition);
    }
}
