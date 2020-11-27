// uquest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

string show_quest(mixed q);

int main(object me, string arg)
{
        string msg;
        mapping uq;
        
        if (! me->query("ultra_quest"))
                 return notify_fail("��Ŀǰû����ȡ�κ���ʦ����\n");
                 
        uq = me->query("ultra_quest");
        
        msg = HIC "\n--------------------------------------------\n" NOR;        
        if (! me->query("ultra_quest/quest"))
        {
        	msg +=    sprintf("�����������%-20d\n", uq["finish"]);
        	msg +=    sprintf("��ǰ֮����%-20s\n", "������");
        	msg +=    sprintf("�ṩ�����ߣ�%-20s\n", uq["next_npc"]);
        	msg +=    sprintf("��������أ�%-20s\n", uq["npc_place"]);
        	msg += HIC "--------------------------------------------\n" NOR;
        	
        	write(msg);
        	return 1;
        }

        msg +=    sprintf("�����������%-20d\n", uq["finish"]);
        msg +=    sprintf("��ǰ֮����%-20s\n", show_quest(uq));
        msg +=    sprintf("�ṩ�����ߣ�%-20s\n", uq["next_npc"]);
        msg +=    sprintf("��������أ�%-20s\n", uq["npc_place"]);
        msg += HIC "--------------------------------------------\n" NOR;
        
        write(msg);                                               
       
        return 1;
}

string show_quest(mixed q)
{
	if (! mapp(q))return "error!";
	
	switch(q["quest"]["type"])
	{
		case "kill":
		      return "��" HIY + q["quest"]["obj"] + NOR + "����ͷ��" + 
		             HIY + q["next_npc"] + NOR + "��";
                
                case "give":
                      return "��" + HIY + q["next_npc"] + NOR + "�Ѱ����͵�" + 
                             HIY + q["quest"]["obj"] + NOR + "����";
                      
                case "send":
                      return "��" + HIY + q["next_npc"] + NOR + "�����͵�" + 
                             HIY + q["quest"]["obj"] + NOR + "����";

                case "find":
                      return "��" HIY + q["next_npc"] + NOR + "��" + HIY + 
                             q["quest"]["obj"] + NOR + "��";
                      
                case "going":
                      return "����" + HIY + q["next_npc"] + NOR + "��" + HIY + 
                             q["quest"]["obj"] + NOR + "��";
                             
                case "guard":
                      return "���ڴ˴�����(guard)" HIY + q["quest"]["obj"] + NOR + "��";
                            
                case "mathematics":
                      return "��" + HIY + q["next_npc"] + NOR + "����(accede)������";
                      
                case "literate":
                      return "��" + HIY + q["next_npc"] + NOR + "��ʫ�Զ�(accede)��";
                      
                case "chess":
                      return "��" + HIY + q["next_npc"] + NOR + "����(accede)һ�֡�";

                case "calligraphy":
                      return "��" + HIY + q["next_npc"] + NOR + "дһ����(accede)��";
                      
                case "drawing":
                      return "��" + HIY + q["next_npc"] + NOR + "��һ����(accede)��";
                      
                case "medical":
                      return "��" + HIY + q["next_npc"] + NOR + "ҽ��(accede)��ʹ��";
                
                default:
                      return HIR "error!";

	}
}

int help(object me)
{
        write(@HELP
ָ���ʽ : uquest  ���ָ����Բ�ѯ�㵱ǰ��ʦ�������ϸ�����

HELP );
        return 1;
}
