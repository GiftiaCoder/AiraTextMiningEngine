package poi.aira.core;

import java.util.HashMap;
import java.util.Set;

public class RelationMap extends HashMap<Character, LinkMap>
{
	private static final long serialVersionUID = 1L;
	
	//private int relationNum = 0;
	
	public void addRelation(char from, char to, int serial)
	{
		LinkMap lm = get(from);
		if (lm == null)
		{
			put(from, lm = new LinkMap());
		}
		lm.addNextLink(to, serial);
		
		//++relationNum;
	}
	
	public Set<Integer> getRelation(char from, char to)
	{
		LinkMap lm = get(from);
		if (lm != null)
		{
			return lm.get(to);
		}
		return null;
	}
	
	public int getTotalLinkNum(char from)
	{
		LinkMap lm = get(from);
		if (lm != null)
		{
			return lm.getTotalLinkNum();
		}
		return 0;
	}
	
	public int getLinkNum(char from, char to)
	{
		LinkMap lm = get(from);
		if (lm != null)
		{
			return lm.getLinKNum(to);
		}
		return 0;
	}
	
	public int getAverageLinkNum(char from)
	{
		LinkMap lm = get(from);
		if (lm != null)
		{
			return lm.getAverageLinkNum();
		}
		return 0;
	}
}
