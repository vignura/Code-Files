package com.example.singletonpattern;

public class Singleton {
    private String name;
    private static Singleton instance;

    public static Singleton getInstance(){
        if(instance == null){
            instance = new Singleton("Singleton class");
        }
        return instance;
    }

    private Singleton(String name) {
        this.name = name;
    }

    String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
