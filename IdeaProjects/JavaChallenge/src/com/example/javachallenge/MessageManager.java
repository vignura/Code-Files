package com.example.javachallenge;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MessageManager {
    private Map<String, List<String>> messages;

    public MessageManager() {
        messages = new HashMap<>();
    }

    public MessageManager(Map<String, List<String>> messages) {
        this.messages = messages;
    }

    public Map<String, List<String>> getMessages() {
        return messages;
    }

    public void setMessages(Map<String, List<String>> messages) {
        this.messages = messages;
    }

    public void sendMessage(String name, String message){
       List<String> messageList = messages.get(name);
       if(messageList != null){
           messageList.add(message);
           messages.put(name, messageList);
       }
       else{
           messageList = new ArrayList<>();
           messageList.add(message);
           messages.put(name, messageList);
       }
    }
}
