import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.TreeMap;

import org.json.simple.parser.ParseException;


public class Q4Reducer {
	
	//assumptions - ids are sorted, hashtag is sorted, can have duplicates 
	public static void main(String[] args) throws IOException, ParseException {
		BufferedReader r = new BufferedReader
				(new InputStreamReader(System.in, "UTF-8"));
		final OutputStreamWriter w = new OutputStreamWriter(System.out, "UTF-8");
		//BufferedReader r = new BufferedReader(new FileReader("q4test1.txt"));
		
		ArrayList<Q4Object> q4list = new ArrayList<Q4Object>();
		HashMap<String, Q4Object> idlist = new HashMap<String, Q4Object>();
		HashSet<String> idss = new HashSet<String>();
		String line;
		String prevloctime = "";
		while ((line = r.readLine()) != null) {
			if (line.length() > 0) {
				String[] ids = line.split("\t\t", 5); //ids0 = loctime, ids1 = id, ids2 = tag ids3 = index
				if (ids[0].equals(prevloctime) && idss.contains(ids[1]+ids[2])) {
					//System.out.println("here");
				}
				else if (ids[0].equals(prevloctime)) {
					if (idlist.containsKey(ids[2]))  //same hashtag
						idlist.get(ids[2]).addLine(ids[1], ids[3]);
					else {
						Q4Object temp = new Q4Object(ids[2], ids[1], ids[3]);
						q4list.add(temp);
						idlist.put(ids[2], temp);
					}
				}
				else {	//new location_time	
					if (!prevloctime.equals("")) {
						Collections.sort(q4list);
						int c = 1;
						for (Q4Object q: q4list) {
							q.sortids();
							w.write(prevloctime + "\t\t" + c + "\t\t" + q.tag + "\t\t" + q.catids + "\t\t");
							w.write("\n");
							w.flush();
							c++;
						}
						idlist.clear();
						q4list.clear();
						idss.clear();
					}
					prevloctime = ids[0];
					Q4Object temp = new Q4Object(ids[2], ids[1], ids[3]);
					q4list.add(temp);
					idlist.put(ids[2], temp);
				}
				idss.add(ids[1]+ids[2]);
			}
		}
		Collections.sort(q4list);
		int c = 1;
		for (Q4Object q: q4list) {
			w.write(prevloctime + "\t\t" + c + "\t\t" + q.tag + "\t\t" + q.catids + "\t\t");
			w.write("\n");
			w.flush();
			c++;
		}
	}
}

class Q4Object implements Comparable<Q4Object>{
	public String tag;
	public String minid;
	public String index;
	public int count;
	public String catids;
	public ArrayList<String> ids;
	
    public Q4Object(String t, String m, String i) {
        tag = t;
        minid = m;
        index = i;
        count = 1;
        catids = "";
        ids = new ArrayList<String>();
        ids.add(m);
    }
    
    public void sortids() {
    	Collections.sort(ids);
    	int j = 0;
    	for (String i: ids) 
    		if (j == 0) {
    			catids += (i.replaceFirst("^0+(?!$)", ""));
    			j++;
    		}
    		else
    			catids += ("," + i.replaceFirst("^0+(?!$)", ""));
    }
    
    public void addLine(String id, String ind) {
    	if (id.compareTo(minid) < 0) {
    		minid = id;
    		index = ind;
    	}
    	count++;
    	ids.add(id);
    }
    
	@Override
	public int compareTo(Q4Object b) {
		if (count < b.count)
            return 1; 
        else if (count > b.count)
            return -1;
        else {
        	if (minid.compareTo(b.minid) < 0)
        		return -1;
        	else if (minid.compareTo(b.minid) > 0)
        		return 1;
        	else {
        		if (index.compareTo(b.index) < 0) 
        			return -1;
        		else if (index.compareTo(b.index) > 0) 
        			return 1;
        		else 
        			return 0;
        	}
        }
	}
}

