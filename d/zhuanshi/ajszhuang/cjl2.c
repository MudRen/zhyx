// by yuchang
inherit ROOM; 
#include <ansi.h> 
#include <room.h>

void create()
{ 
      set("short", "�ؽ�®�ܵ�");
      set("long",
"�����ǰ���ɽׯ�ؽ�®���ܵ��ڲ�����������ʮ�ְ�����\n"
"����Ҳ��ʮ�ֵĳ�ʪ��ʵ������ɭ�ޱȡ�\n");
      set("exits",([
            "north" : __DIR__"cjl3",
            "south" : __DIR__"cjl",
      ]));     
      setup();
}

int valid_leave(object me, string dir)
{     
        object ob;
    
        if ( ! me->query_temp("reborn_start/ao2") 
            && dir == "north" )   
        {
           if ( objectp(present("ao xiaotian", environment(me))) )
              return -1; 
           ob = new(__DIR__"npc/aoxiaotian");   
           ob->move(environment(me));
           tell_room(environment(me),
                     CYN "\nͻȻֻ��һ����Ӱ��֪��������˳�����"
                     "ԭ���ǰ���ɽׯ��ʥ��Х�졣\n\n"NOR);          
           return -1;              
        }
       return 1;

}


