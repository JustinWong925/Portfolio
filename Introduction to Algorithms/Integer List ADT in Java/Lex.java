// Program 1: Lexicographic Sorting
//Justin Wong jujwong

import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
	  int lineNumber = 0;
      int i = 0;
	  int n = 0;
      if (args.length != 2){ //needs two command line arguments
         System.err.println("Usage: Lex infile outfile");
	     System.exit(1);
      }
   
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
   
      while(in.hasNextLine()){ //takes in string
	     ++lineNumber;
	     line = in.nextLine()+" "; 
	     token = line.split("\\s+"); //the string array splitting at the spaces
	     n = token.length;
		 out.println("Line "+lineNumber+" contains "+n+" token"+(n==1?"":"s")+":");
	     for(i = 0; i<n; ++i){
		    out.println(i);
	        out.println(token[i]);
	     }
         out.println();
      
	  	  
      in.close();
      out.close();
   /*
   //This is just the regular insertion sort
   //
   void inSort(){
      for (j = 1; j <= n-1; ++j){ //n = array length
	     String temp = token[i]; //temp is first item in array
		 i = j-1; //starts at beginning
		 while(i > 0 && temp.compareTo(token[i]) < 0){ //i > 0 and temp smaller than token at i
		    token[i+1] = token[i];  //token[i+1] becomes token[i]
			--i;  //i is decremented
		 }
		 token[i+1] = temp;  //token[i+1] swaps with temp
	  }   
   }
   */
   /*
   //This insertion sort has been modified for the list and arrays
   //
   //
    static void inSortRedux(){
      List L = new List();
	  for(int j = 1; j <= n; ++j){
	     if(L.length() == 0){ L.append(j);} //if empty list, start it
	     String temp = token[j];
		 int i = j-1;
		    while(i > -1){
			   L.moveTo(i);
			   String s2 = token[i]; //s2 = string at token i
			   if(temp.compareTo(s2) < 0){L.insertAfter(i);}
			   else if(temp.compareTo(s2) == 0){ L.insertAfter(i);}
			   else if(temp.compareTo(s2) > 0){L.insertBefore(i);}
			   continue;
			}
		 }
	  }
	  */
}
}
}
   
   
   