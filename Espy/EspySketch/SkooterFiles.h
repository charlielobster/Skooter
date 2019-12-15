#ifndef _SKOOTER_FILES_H_
#define _SKOOTER_FILES_H_

class SkooterFiles
{
public:
	static String asList;
	static String asTags;

	static void appendTag()
	{
		int len = asList.lastIndexOf(',');
		String fileName = (len > 0 ? asList.substring(len + 1) : asList);
		asTags += ("<a href=\"/" + fileName + "\">/" + fileName + "</a><br>");
	}
};

String SkooterFiles::asList = "";
String SkooterFiles::asTags = "";

#endif
