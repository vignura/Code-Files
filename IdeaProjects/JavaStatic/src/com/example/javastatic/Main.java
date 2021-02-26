package com.example.javastatic;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<StaticTest> staticTests = new ArrayList<>();
        // set the static member name
        StaticTest.setName("Vignesh");
        // add 3 test instances
        for(int i = 0; i < 3; i++){
            staticTests.add(new StaticTest("white", 10 + i));
        }

        // print the lists
        for(StaticTest st: staticTests){
            System.out.println("Name: " + StaticTest.getName() + " color: " + st.getColor() + " age: " + st.getAge());
        }
    }
}
