// by yuchang
inherit ROOM; 
#include <ansi.h> 
#include <room.h>

void create()
{ 
      set("short", "�ؽ�®�ܵ�");
      set("long",
"����ͨ������ɽׯ�Ĳؽ�®���ܵ����������ʮ�ְ�����\n"
"����Ҳʮ�ֳ�ʪ������һ��ë����Ȼ�ĸо���\n");
      set("exits",([
            "north" : __DIR__"cjl2",
            "south" : __DIR__"square",
      ]));     
      setup();
}

int valid_leave(object me, string dir)
{     
        object ob;
    
        if ( ! me->query_temp("reborn_start/ao1") 
            && dir == "north" )   
        {
           if ( objectp(present("ao cangtian", environment(me))) )
              return -1; 
           ob = new(__DIR__"npc/aocangtian");   
           ob->move(environment(me));
           tell_room(environment(me),
                     CYN "\nͻȻֻ��һ����Ӱ��֪��������˳�����"
                     "ԭ���ǰ���ɽׯ��ʥ�����졣\n\n"NOR);          
           return -1;              
        }
       return 1;

}

