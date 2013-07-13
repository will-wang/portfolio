//Nianzu Wang
//Email: nwang6@mail.gatech.edu
//TextAnalyzer.java

   import java.util.*;

	//This class requires an argument , N, to be provided by the user via cmd.exe.
	//It then records and the first N unique words from user input or a txt file
	//and then displays how many times those unique words appear in the entire input.
	//Finally, it displays the longest sentence in input.

    public class TextAnalyzer
   {
       public static void main(String[]	args)
      {
         
		//Creates a new Scanner, scan, and a new StringBuilder, build.
			
    	 Scanner scan = new Scanner(System.in);
         StringBuilder build = new StringBuilder();
      
         //Creates int arrays: N, UniqueCounter, x,and y.
         //Creates String: whole, part,and LongestSentence.
		
         int N = Integer.parseInt(args[0]);
         int UniqueCounter = 0;
         int Sentence, index, word, count ;
         String whole = "";
         String part = "";
         String LongestSentence = "";
			
         //Creates int array NumberUnique, String arrays: UniqueWords, Words, Sentences.
      
         int[] NumberUnique;      
         String[] UniqueWords = new String[N];
         String[] Words;
         String[] Sentences;
			
         //Scans for a word as long as there is a word to scan.
         //Then it converts all each word to lowercase and adds it to the String whole.
         //Finally, it appends the word to the Stringbuilder with a " " added.
      
         while (scan.hasNext())
         {    
			part = scan.next();
            part = part.toLowerCase();
            whole += part;
            whole += " ";
            build.append(part + " ");
         }
         
			//Converts all "end-of-sentence" punctuation to '.'
			//This is done to make parsing each sentence simpler.
			//Since it is not necessary to re-print any text including punctuation,
			//there is no loss.
			
			whole = whole.replace('!','.');
			whole = whole.replace('?','.');
			
			//Splits the whole text between each '.' and adds it to the String array, Sentences.
			//This is to record each sentence for sentence comparison.
						
			Sentences = whole.split("\\.");
			
			//Analyzes each sentence and saves the longest sentence as the String, LongestSentence.
			
			for (Sentence = 0; Sentence < Sentences.length; Sentence++)
				{
					if (Sentences[Sentence].length() > LongestSentence.length())
						LongestSentence = Sentences[Sentence];
				}
			
			//Splits all the words appended from part into individual words, stored in the String array, Words.
			//This is to record each word, without spaces, for word comparison.
						
         Words = (build.toString().split(" "));
			
         //Finds any words in String array Words that have punctuation and replaces it without punctuation.
         //This is done so that punctuation isn't included in comparison.
         
         for (index = 0; index < Words.length; index++)
         {
            if(
            Words[index].substring(Words[index].length()-1).equals(".") ||
            Words[index].substring(Words[index].length()-1).equals(",") ||
            Words[index].substring(Words[index].length()-1).equals("!") ||
            Words[index].substring(Words[index].length()-1).equals("?"))
               Words[index] = Words[index].substring(0, Words[index].length()-1);     
         }
			
		//Counts first N UNIQUE words from String array Words and stores it in String array UniqueWords.
      	
         while (UniqueCounter < UniqueWords.length)
         {
            for (word = 0; word < Words.length; word++)
            {
               for (count = 0; count <= UniqueCounter; count++)
               {
                  if (Words[word].equals(UniqueWords[count]))
                     break;
							
                  if (count == UniqueCounter)
                  {
                     UniqueWords[UniqueCounter] = Words[word];
                     break;
                  }
               }
               if (UniqueWords[UniqueCounter] != null)
                  break;
            }
            UniqueCounter++;
         }
      	
			//Calls the UniqueAdder method, created bellow, to count the number of each unique word
			//and then stores it in the String array, NumberUnique.
			//This sends the two parameters, UniqueWords and Words, into the UniqueAdder method. 
			
			NumberUnique = UniqueAdder(UniqueWords, Words);
			
			//Prints out the word frequencies of each unique word.
			
			System.out.println ("Word frequency: ");
			for (int i = 0; i < NumberUnique.length; i++)
			System.out.println (UniqueWords[i] + ": " + NumberUnique[i]);

			//Prints out the longest sentence.

			System.out.println ("Longest Sentence: " + LongestSentence);

      } //Ends main method.
		
		//Creates the UniqueAdder method.
		//This method takes in the two String array parameters above, UniqueWords and Words.
		//It renames the two parameters to Unique and All.
		//This method counts the number each unique
      
  		public static int[] UniqueAdder(String[] Unique, String[] All)
		{
		
			//Creates new int array, NumberUnique, of length N.
			
			int[] NumberUnique = new int[Unique.length];
			
			//Creates ints x and y.
			
			int x, y;
			
			//Counts how many times each unique word shows up in text.
			//This compares each word to each unique word.
			//If it is the same, it adds one to the corresponding unique word count.
			
			for (x = 0; x < Unique.length; x++)
			{
				for (y = 0; y < All.length; y++)
				{
					if (All[y].equals(Unique[x]))
						NumberUnique[x]++;
				}
			}
			return NumberUnique;
		} //Ends UniqueAdder method.		
   }//Ends TextAnalyzer class.
