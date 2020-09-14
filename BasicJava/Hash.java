import java.util.Scanner;
import java.io.*;
import java.nio.file.*;

public class Hash{

	static int HashSize = 16;
	static int Len = 0;
	static byte[] hash = new byte[HashSize];

	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);
		System.out.print("Enter File name: ");
		String FileName = in.nextLine();
		// System.out.println("File name: " + FileName);

		// try to read from file 
		try{

			byte[] Content = Files.readAllBytes(Paths.get(FileName));
			System.out.println("Read: " + Content.length + " bytes");

			// print the content of the file
			for(int i = 0; i < Content.length; i += HashSize){
				// System.out.print((char)Content[i]);

				// calculate length
				if((Content.length -i) >= HashSize){
					Len = HashSize;
				}else{
					Len = (Content.length -i);
				}

				// System.out.println("i: " +i + " Len: "+ Len);

				// compute the hash 
				for(int j = 0; j < Len; j++){
					hash[j] = (byte)(hash[j] ^ Content[i + j]);
				}
			}

		} catch(IOException ex){
			ex.printStackTrace();
		}

		// print the hash
		System.out.print("Hash: ");
		for(int i = 0; i < HashSize; i++){
			System.out.print(hash[i]);
		}
		System.out.print("\n");
	}
}