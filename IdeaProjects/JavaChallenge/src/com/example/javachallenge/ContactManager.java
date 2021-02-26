package com.example.javachallenge;

import java.util.List;

public class ContactManager {
    private List<Contact> contacts;

    public ContactManager(List<Contact> contacts) {
        this.contacts = contacts;
    }

    public List<Contact> getContacts() {
        return contacts;
    }

    public void setContacts(List<Contact> contacts) {
        this.contacts = contacts;
    }

    public void addContact(Contact contact){
        contacts.add(contact);
    }

    public void removeContact(Contact contact){
        contacts.remove(contact);
    }

    public void removeContactByName(String contactName){
        for(Contact contact : contacts){
            if(contact.getName().equals(contactName)){
                contacts.remove(contact);
                return;
            }
        }
    }

    public void removeContactByNumber(String contactNumber){
        for(Contact contact : contacts){
            if(contact.getPhoneNumber().equals(contactNumber)){
                contacts.remove(contact);
                return;
            }
        }
    }

    public Contact searchContactByName(String contactName){
        for(Contact contact : contacts){
            if(contact.getName().equals(contactName)){
                return contact;
            }
        }
        return null;
    }

    public Contact searchContactByNumber(String contactNumber){
        for(Contact contact : contacts){
            if(contact.getPhoneNumber().equals(contactNumber)){
                return contact;
            }
        }
        return null;
    }
}
