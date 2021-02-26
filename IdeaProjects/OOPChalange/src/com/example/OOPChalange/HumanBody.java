package com.example.OOPChalange;

public class HumanBody {
    private String name;
    private int age;
    private Heart heart;
    private Eye leftEye;
    private Eye rightEye;
    private Stomach stomach;
    private Skin skin;

    public HumanBody(String name, int age, Heart heart, Eye leftEye, Eye rightEye, Stomach stomach, Skin skin) {
        this.name = name;
        this.age = age;
        this.heart = heart;
        this.leftEye = leftEye;
        this.rightEye = rightEye;
        this.stomach = stomach;
        this.skin = skin;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public Heart getHeart() {
        return heart;
    }

    public void setHeart(Heart heart) {
        this.heart = heart;
    }

    public Eye getLeftEye() {
        return leftEye;
    }

    public void setLeftEye(Eye leftEye) {
        this.leftEye = leftEye;
    }

    public Eye getRightEye() {
        return rightEye;
    }

    public void setRightEye(Eye rightEye) {
        this.rightEye = rightEye;
    }

    public Stomach getStomach() {
        return stomach;
    }

    public void setStomach(Stomach stomach) {
        this.stomach = stomach;
    }

    public Skin getSkin() {
        return skin;
    }

    public void setSkin(Skin skin) {
        this.skin = skin;
    }

    public Organ getSelectedOrgan(int organNumber){

        switch (organNumber){
            case 1: return this.heart;
            case 2: return this.leftEye;
            case 3: return this.rightEye;
            case 4: return this.stomach;
            case 5: return this.skin;
            default: return new Organ("unknown", "unknown");
        }
    }
}
