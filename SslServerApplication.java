package com.snhu.sslserver;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import java.security.MessageDigest;

@SpringBootApplication
public class SslServerApplication {

	public static void main(String[] args) {
		SpringApplication.run(SslServerApplication.class, args);
	}

}

@RestController
class ServerController {
	
	 @RequestMapping("/hash")
	    public String myHash(){
		    	// Changed the name to fit requirement
		    	String data = "My name Joseph Goins, and this is a cool hash function!";
		    	try {
			    	// Created a MessageDigest instance called hash which uses the SHA-256 hash algorithm
			    	MessageDigest hash = MessageDigest.getInstance("SHA-256");
			    	
			    	// Hash the data using the string as a byte data type
			    	byte[] hashedMessage = hash.digest(data.getBytes());
			    	
			    	// Convert bytes to hexadecimal message format
			    	String hex = bytesToHex(hashedMessage);
		
			    	// Return the hashed message
		        return "<html><body>"
		        		+ "<p>Data: " + data + "</p>"
		        		+ "<p>SHA-256 : CheckSum Value " + hex + "</p>"
		        				+ "</body></html>";
		    	} catch (Exception e) {
		    		return "<html><p>Error hashing data</p></html>";
		    	}
	    }
	 
	 public static String bytesToHex(byte[] bytesMessage) {
 		// Use the string builder to build a hexMessage
 		StringBuilder hexMessage = new StringBuilder();
 		
 		// Iterates through each byte in the bytesMessage
 		for (byte x : bytesMessage) {
 			hexMessage.append(String.format("%02x", x)); // Converts each byte to hex format
 		}
 		
 		// Return the hexMessage as a string which is the encrypted message
 		return hexMessage.toString();
 }
}