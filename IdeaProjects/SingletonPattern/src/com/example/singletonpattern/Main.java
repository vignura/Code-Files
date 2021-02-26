package com.example.singletonpattern;

public class Main {
    public static void main(String[] args) {
        Singleton singleton = Singleton.getInstance();
        System.out.println(singleton.getName());
        /*
         you can't do
         Singleton singleton = new Singleton("name");
         as the constructor is private and it is only
         called inside the getInstance method.
        */
    }
}
