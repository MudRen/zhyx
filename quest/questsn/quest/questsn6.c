#include <ansi.h>
#define QUESTSN_D(x)      ("/quest/questsn/quest/questsn" + x)

mapping query_quest() 
{
        mapping questsn;
        if (random(50) > 35)
        	questsn = QUESTSN_D("7Ѱ")->query_questsn();
        else if (random(2) == 1)
                questsn = QUESTSN_D("6Ѱ")->query_questsn();
        else
	questsn = QUESTSN_D("6ɱ")->query_questsn();
        if (questsn["type"] == "Ѱ") 
        {
                if (random(5) == 3)
                {
                        questsn["type"] = "��";
                        questsn["name"] = "��ִ";
                }
        } 
        return questsn;
}
