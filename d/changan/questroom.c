// ����Ϊ�����������ķ���
// add by chhu
// Modified by haiyan

inherit ROOM;
#include <ansi.h> 
#include <room.h> 

void create()
{
     set("short", "�ͱ�");
     set("long", @LONG   
����λ������ɽ��һ���ͱڣ�Զ��������ӿ����ˮ����
��Χ�������Ĵ��֡�һ��⻬�Ĵ�ʯ(stone)�����ƺ���
������ؿ���Щ�֡�
LONG);  
     set("exits", ([ /* sizeof() == 1 */ 
         "south" : "/d/changan/zhongnan.c",
     ])); 

     set("objects", ([ 
         "/u/yuchang/quest/tianshi" : 1,
     ]));

     setup(); 
}

void init() 
{ 
    add_action("do_look","look"); 
} 

int do_look(string arg) 
{ 
    string msg; 
    if (!arg || arg != "stone")  return 0; 
    msg  = HIC "----------------------------------------------------------\n"NOR; 
    msg += WHT BBLU "                        ׽��������                      \n"NOR; 
    msg += HIC "----------------------------------------------------------\n"NOR; 
    msg += "    �䵱�ɺ�ȫ��̵�����Ϊ��ʿ����Ȼ�ή����ħ�ı��¡�����\n";
    msg += "������ʦ�������񡣽�����ħ��Ҫ�������һ��"HIY"��ֽ"NOR"������"HIM"��ľ\n";
    msg += "��"NOR"����ȡ����ʱ������ʦ�����"HIY"��ֽ"NOR"����"HIM"��ľ��"NOR"����Ҫ�Լ���취\n";
    msg += "�ˡ�:)\n";
    msg += "    �������һ�����Ѷȣ���ħһ�㶼�����������ģ���ֻ��\n";
    msg += "���о����Ĵ��ڣ�������"HIY"��ֽ"NOR"ʹ����������о�����ħ����ʱ��\n";
    msg += "ֻ��ʹ��"HIC"shoufu"NOR"ָ�����kill��������ħһ�㶼�Ƚ�����������\n";
    msg += "�������ֵ�׼�����������󣬽�"HIY"��ֽ"NOR"����������ʦ�����ɵõ�\n";
    msg += "������\n";
    this_player()->start_more(msg); 
    return 1; 
} 

