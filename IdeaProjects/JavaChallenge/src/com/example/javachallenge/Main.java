package com.example.javachallenge;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        boolean shouldQuit = false;
        
        System.out.println("Welcome to phone simulator !");

        // create some contacts
        List<Contact> contacts = new ArrayList<>();
        contacts.add(new Contact("vignesh", "9940398991"));
        contacts.add(new Contact("amma", "9940244384"));
        contacts.add(new Contact("airtel", "*121#"));
        
        ContactManager contactManager = new ContactManager(contacts);
        MessageManager messageManager = new MessageManager();

        while(!shouldQuit){
            System.out.println("""
                    Main Menu:
                    1. Manage Contacts
                    2. Messages
                    3. Quit""");

            Scanner scanner =  new Scanner(System.in);
            int choice = scanner.nextInt();
            boolean shouldBreak = false;

            switch (choice){
                case 1:
                    while(!shouldBreak){
                        System.out.println("""
                                Manage Contacts Menu:
                                1. Show all contacts
                                2. Add new contact
                                3. Search for a contact
                                4. Delete a contact
                                5. Go back to previous menu""");
                        choice = scanner.nextInt();
                        switch (choice)
                        {
                            case 1:
                                contacts = contactManager.getContacts();
                                for (Contact contact:
                                     contacts) {
                                    System.out.println("Name: " + contact.getName() + " Phone number: " + contact.getPhoneNumber());
                                }
                                break;
                            case 2:
                                String name;
                                String phoneNumber;
                                System.out.print("enter contact name: ");
                                name = scanner.next();
                                System.out.print("enter contact number: ");
                                phoneNumber = scanner.next();
                                contactManager.addContact(new Contact(name, phoneNumber));
                                break;
                            case 3:
                                String contactName;
                                System.out.print("enter contact name to search: ");
                                contactName = scanner.next();
                                Contact contact = contactManager.searchContactByName(contactName);
                                if(contact != null){
                                    System.out.println("contact found!, Phone number: " + contact.getPhoneNumber());
                                }else                                   {
                                    System.out.println("contact not found!");
                                }
                                break;
                            case 4:
                                System.out.print("enter contact name to delete: ");
                                contactName = scanner.next();
                                contactManager.removeContactByName(contactName);
                                break;
                            default: shouldBreak = true;
                        }
                    }
                    break;
                case 2:
                    while(!shouldBreak) {
                        System.out.println("""
                                Messages Menu:
                                1. See all messages
                                2. Send a new message
                                3. go back to previous menu""");
                        choice = scanner.nextInt();
                        switch (choice) {
                            case 1:
                                Map<String, List<String>> messages = messageManager.getMessages();
                                for(String name: messages.keySet()){
                                    List<String> msgList = messages.get(name);
                                    System.out.println("Messages from  " + name + ": ");
                                    for(String msg: msgList){
                                        System.out.println("\t" + msg);
                                    }
                                }
                                break;
                            case 2:
                                String name;
                                String message;
                                System.out.print("enter contact name: ");
                                name = scanner.next();
                                System.out.print("enter message: ");
                                scanner.nextLine();
                                message = scanner.nextLine();
                                messageManager.sendMessage(name, message);
                                break;
                            default: shouldBreak = true;
                        }
                    }
                    break;
                default: shouldQuit = true;
            }
        }
    }
}
