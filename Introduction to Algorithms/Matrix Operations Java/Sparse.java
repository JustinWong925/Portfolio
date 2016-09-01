//Program 3: Matrix
//Justin Wong, jujwong
//CS101 Tantalo F14

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

public class Sparse{
    static Scanner open(String filename){
	Scanner scan = null;
	try{
	    scan = new Scanner(new File(filename));
	} catch (IOException except){
	    System.err.println("Error: Invalid filename");
	    exit(1);
	}
	return scan;
    }
    
    // function to safe check the file.nextInt() function
    static int getInt(Scanner file){
	int length = 0;
	if(file.hasNextInt()){
	    length = file.nextInt();
	} else {
	    System.out.println("Invalid file input: needs to have correct integer order");
	    exit(1);
	}
	return length;
    }
	
    // Executes all operations and prints the necessary statements. 
    static void printprog (Scanner file, PrintWriter writer, String args){
	int length = getInt(file);
	Matrix A = new Matrix(length);
	Matrix B = new Matrix(length);
	int Arow = getInt(file);
	int Brow = getInt(file);
	file.nextLine(); // jump the space line
	// fill Matrix A
	for(;Arow > 0; Arow--){
	    A.changeEntry(getInt(file), getInt(file), file.nextDouble());
	}
	writer.println("A has " + A.getNNZ() + " non-zero entries:");
	writer.println(A);
	// fill Matrix B
	file.nextLine();
	for(;Brow > 0; Brow--){
	    B.changeEntry(getInt(file), getInt(file), file.nextDouble());
	}
	writer.println("B has " + B.getNNZ() + " non-zero entries:");
	writer.println(B);

	// implements the necessary operations and outputs
	Matrix ScalarA = A.scalarMult(1.5);
	writer.println("(1.5)*A =");
	writer.println(ScalarA);

	Matrix AplusB = A.add(B);
	writer.println("A+B =");
	writer.println(AplusB);
	
	Matrix AplusA = A.add(A);
	writer.println("A+A =");
	writer.println(AplusA);
	
	Matrix BminusA = B.sub(A);
	writer.println("B-A =");
	writer.println(BminusA);
	
	Matrix AminusA = A.sub(A);
	writer.println("A-A =");
	writer.println(AminusA);
	
	Matrix Atranspose = A.transpose();
	writer.println("Transpose(A) =");
	writer.println(Atranspose);

	Matrix AmultB = A.mult(B);
	writer.println("A*B =");
	writer.println(AmultB);

	Matrix BmultB = B.mult(B);
	writer.println("B*B =");
	writer.println(BmultB);

    }

	// checks for proper number of arguments
	// then calls the main program function
	// and will close the file and save
    public static void main(String[] args){
	if(args.length != 2) {
	    System.err.println("Invalid inputs");
	    exit(1);
	}
	Scanner input = open(args[0]);
	PrintWriter writer = null;
	try {
	    writer = new PrintWriter(new FileWriter(args[1]));
	} catch (FileNotFoundException excep){
	    System.err.println("Could not create the file");
	    exit(1);
	} catch (IOException excep){
	    System.err.println("Could not create the file");
	    exit(1);
	}
	printprog(input, writer, args[0]);
	writer.close();
    }
}