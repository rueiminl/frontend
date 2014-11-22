import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Q5Reducer {
	public static void main(String[] args) throws IOException, ParseException, java.text.ParseException {
		
		BufferedReader r = new BufferedReader
			(new InputStreamReader(System.in, "UTF-8"));
		//BufferedReader r = new BufferedReader(new FileReader("q5inter.txt"));
		
		String line = "";
		boolean printit = false;
		String curruser = "";
		HashSet<String> uniquetweets = new HashSet<String>();
		HashSet<String> uniqueids = new HashSet<String>();
		int score1 = 0;
		int score2 = 0;
		int score3 = 0;
		while ((line = r.readLine()) != null) {
			if (line.length() > 0 ) {
				String[] ids = line.split("\t", 3);
				if (!(uniquetweets.contains(ids[1]) && curruser.equals(ids[0]))) {
					if (curruser.equals(ids[0])) {
						if (ids[2].charAt(0) == 'N') {
							score1 += 1;
						}
						else {
							if (ids[2].substring(2).equals(curruser))
								score1 += 1;
							if (!uniqueids.contains(ids[2].substring(2))) {
								score3 += 10;
								uniqueids.add(ids[2].substring(2));
							}
							score2 += 3;							
						}
					}
					else {
						if(printit)
							System.out.println(curruser + "\t" + score1 + "\t" + score2 + "\t" + score3 + "\t" + (score1 + score2 + score3));
						else
							printit = true;
						curruser = ids[0];
						uniqueids.clear();
						uniquetweets.clear();
						if (ids[2].charAt(0) == 'N') {
							score1 = 1;
							score2 = 0;
							score3 = 0;
						}
						else {
							if (ids[2].substring(2).equals(curruser))
								score1 = 1;
							else 
								score1 = 0;
							if (!uniqueids.contains(ids[2].substring(2))) {
								score3 = 10;
								uniqueids.add(ids[2].substring(2));
							}
							else 
								score3 = 0;
							score2 = 3;
						} 
					}
				}
				uniquetweets.add(ids[1]);
			}
		}
		System.out.println(curruser + "\t" + score1 + "\t" + score2 + "\t" + score3 + "\t" + (score1 + score2 + score3));
	}
	
}
