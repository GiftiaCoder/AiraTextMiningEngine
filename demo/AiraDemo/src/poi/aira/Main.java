package poi.aira;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;

import poi.aira.core.EngineStorage;
import poi.aira.core.EngineStorage.TokenIterator;

public class Main 
{
	public static void main(String[] cmds) throws IOException
	{
		EngineStorage engine = new EngineStorage();
		
		BufferedReader rd = new BufferedReader(new InputStreamReader(new FileInputStream("yahari.txt"), "utf-8"));
		String ln = null;
		while ((ln = rd.readLine()) != null)
		{
			for (int i = 0; i < ln.length(); ++i)
			{
				engine.addNextChar(ln.charAt(i));
			}
		}
		rd.close();
		
		Set<String> tokenSet = new HashSet<>();
		
		StringBuilder text = new StringBuilder("比企谷八幡");
		//TokenIterator it = engine.createTokenIterator(text);
		TokenIterator it = engine.createSelfIterator();
		String token = null;
		while ((token = it.nextToken()) != null)
		{
			tokenSet.add(token);
		}
		
		int i = 0;
		for (String t : tokenSet)
		{
			System.out.printf("[%s],", t);
			if (++i == 16)
			{
				System.out.println();
				i = 0;
			}
		}
	}
}
