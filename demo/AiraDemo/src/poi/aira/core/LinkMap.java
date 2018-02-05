package poi.aira.core;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class LinkMap extends HashMap<Character, Set<Integer>>
{
	private static final long serialVersionUID = 1L;

	private int linkNum = 0;
	
	public void addNextLink(char next, int serial)
	{
		Set<Integer> s = get(next);
		if (s == null)
		{
			put(next, s = new HashSet<>());
		}
		s.add(serial);
		
		++linkNum;
	}
	
	public int getTotalLinkNum()
	{
		return linkNum;
	}
	
	public int getLinKNum(char next)
	{
		Set<Integer> s = get(next);
		return s != null ? s.size() : 0;
	}
	
	public int getAverageLinkNum()
	{
		return getTotalLinkNum() / size();
	}
}
