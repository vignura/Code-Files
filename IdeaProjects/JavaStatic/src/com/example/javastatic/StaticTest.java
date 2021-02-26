package com.example.javastatic;

public class StaticTest {
    private static String name;
    private String color;
    private int age;

    public StaticTest(String color, int age) {
        this.color = color;
        this.age = age;
    }

    public static String getName() {
        return name;
    }

    public static void setName(String name) {
        StaticTest.name = name;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
