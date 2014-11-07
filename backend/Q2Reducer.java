import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.HashMap;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class Q2Reducer {

	public static void main(String[] args) throws IOException, ParseException {
		
		//choose between reading from stdin and a file
		BufferedReader r = new BufferedReader
						(new InputStreamReader(System.in, "UTF-8"));
		final OutputStreamWriter w = new OutputStreamWriter(System.out, "UTF-8");
		//BufferedReader r = new BufferedReader(new FileReader("q2inter.txt"));
		String line;
		BufferedReader af = new BufferedReader(new FileReader("AFINN.txt"));
		HashMap<String, Integer> afin = new HashMap<String, Integer>();
		HashMap<String, Integer> banned = new HashMap<String, Integer>();
		
		//add sentiment values to a map
		while ((line = af.readLine()) != null) {
			String[] afinn = line.split("\t", 2);
			afin.put(afinn[0], Integer.parseInt(afinn[1]));
		}
		af.close();
		
		//add banned words to map 
		BufferedReader ban = new BufferedReader(new FileReader("banned.txt"));
		while ((line = ban.readLine()) != null) {
			String[] afinn = line.split("\t", 2);
			banned.put(line, 1);
		}
		
		String totalId = "";
		String idTime = "";
		while ((line = r.readLine()) != null) {
			JSONParser parser=new JSONParser();
			String[] tweet = line.split("\t", 2);
			String[] tweet2 = tweet[0].split("  ", 2);
			int sentiment = 0;
			JSONObject obj=(JSONObject) parser.parse(tweet[1]);	
			String text = (String) obj.get("text");
			StringBuilder result = new StringBuilder();
			int prev = 0;
			for (int i = 0; i < text.length(); i++) {
				if (!Character.isLetterOrDigit(text.charAt(i)) && prev != i) {
					String sub = text.substring(prev, i).toLowerCase();
					if (afin.containsKey(sub)) {
						sentiment += afin.get(sub);
					}
					if (banned.containsKey(sub)) {
						int len = sub.length() - 2;
						sub = text.charAt(prev) + new String(new char[len]).replace('\0', '*') + text.charAt(i - 1);
						result.append(sub + text.charAt(i));
					}
					else {
						result.append(text.substring(prev, i + 1));
					}
					prev = i + 1;
				}
			}
			result.append(text.substring(prev, text.length()));
			if (!idTime.equals(tweet2[0])) {
				if (!idTime.equals("")) {
					w.write(idTime + "\t;\t;\t" + totalId +"`?,.^;\n");
					w.flush();
				}
				idTime = tweet2[0];
				totalId = tweet2[1].replaceFirst("^0+(?!$)", "") + ":" + sentiment + ":" + result;
			}
			else 
				totalId += "\n" + tweet2[1].replaceFirst("^0+(?!$)", "") + ":" + sentiment + ":" + result;
			//current print format is separated by tab, may want to use a more unique separator and newline separator		
	    }
		w.write(idTime + "\t;\t;\t" + totalId +"`?,.^;\n");
		w.flush();

	}

}
