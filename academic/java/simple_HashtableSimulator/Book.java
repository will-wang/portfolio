
/**
 * @author Robert
 *
 */
public class Book {
	/**
	 * Codes for the different hash algorithms we will use
	 */
	public enum Hashtype {
		DEFAULT, ADLER32, SDBM, INTEGER, SIMPLEADD, USER;
	}
	/**
	 * Book data for the experiment
	 */
    String title;
    String isbn;
    String author;
    String callno;
    String control;
    
    /**
     * The hashtype for all books
     */
    public static Hashtype hashtype;
    
    /**
     * Constructor
     * @param t the title
     * @param a the author
     * @param i the ISBN
     * @param call the call number
     * @param cont the control number
     */
    public Book(String t, String a, String i, String call, String cont) {
    	title = t;
    	isbn = i;
    	author = a;
    	callno = call;
    	control = cont;
    }
    
    /**
     * Books are equal if their ISBN is equal
     * normally, but since we use different keys
     * we have to do this kludgy thing
     */
    public boolean equals(Object o) {
    	Book b = (Book)o;
    	switch(hashtype) {
    	case DEFAULT:
    		return isbn.equals(b.isbn);
    	case ADLER32:
    		return author.equals(b.author);
    	case SDBM:
    		return callno.equals(b.callno);
    	case USER:
    		return isbn.equals(b.isbn);
    	case INTEGER:
    		return control.equals(b.control);
    	case SIMPLEADD:
    		return title.equals(b.title);
    	}
		return isbn.equals(b.isbn);  	
    }
    
    /**
     * return the hashcode for this book based upon the
     * type we want to use.  DO NOT change the type of 
     * code once you start inserting or you won't be 
     * able to find anything.
     */
    public int hashCode() {
    	//use the correct hashcode for this book
    	switch(hashtype) {
    	case DEFAULT:
    		return isbn.hashCode();
    	case ADLER32:
    		return hashAuthor();
    	case SDBM:
    		return hashCall();
    	case USER:
    		return hashISBN();
    	case INTEGER:
    		return hashControl();
    	case SIMPLEADD:
    		return hashTitle();
    	}
    	//if unknown, just return our standard hash code
    	return isbn.hashCode();
    }
    
    /**
     * COnvert the control number to an integer
     * @return
     */
    public int hashControl() {
    	int cont = Integer.parseInt(control);
		return cont;
    }
    
    /**
     * Fill this in with your own hash function.  Try something
     * creative
     * 
     * @return
     */
    public int hashISBN() {
	 	int hash = 0;
		int code = 1313;
		int lngth = isbn.length();		
		for (int i = 0; i < lngth; i++) {
			hash = (hash * code) + (lngth * isbn.charAt(i));
		}
		hash = hash % lngth;
    	return hash;
    }
    
    /**
     * Fill this in to return the sum of the chars in the title
     * @return
     */
    public int hashTitle() {
    	int sum = 0;
		int tmpInt;
		for (int i = 0; i < title.length(); i++) {
			tmpInt = (int) title.charAt(i);
			sum += tmpInt;		
		}
		return sum;
    }
    
    /**
     * Fill this in with the ADLER32 algorithm
     * @return
     */
    public int hashAuthor() {
    	int Alder;
		int A = 1;
		int B = 0;
		int tmpInt;
		int length = author.length();
		
		for (int i = 0; i < length; i++) {
			tmpInt = (int) author.charAt(i);
			A += tmpInt;
		}
		A = (A % 65535);
		
		int[] lngth = new int[length];
		int[] chars = new int[length];
		int counter = 0;
		for (int x = length; x > 0; x--) {
			lngth[counter] = x;
			chars[counter] = (int) author.charAt(counter);
			counter ++;			
		}
		for (int i = 0; i <= length; i++) {
			B += (lngth[i] * chars[i]);
		}
		B = (B % 65535);
		
		Alder = A + (B << 16);
		return Alder;
    }
    
    /**
     * Fill this in with the SDBM algorithm
     * @return
     */
    public int hashCall() {
	 	int hash = 0;
      for (int i = 0; i < callno.length() ; i++) {
           hash = callno.charAt(i) + (hash << 6) + (hash << 16) - hash;
      }
      return hash;
    }
    
    public String toString() {
    	return "Book Title: " + title + "  Author: " + author + "  ISBN: " + isbn + 
    	       "  Call Number: " + callno + "  Control Number: " + control;
    }
}
