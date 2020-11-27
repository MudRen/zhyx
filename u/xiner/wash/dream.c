#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "���ξ���" NOR);
        set("long", CYN @LONG
�������ξ�����о������Ժ����ģ���ʶ�ܲ�������
�Ĵ����ǰ�ããһƬ����ʲô�������С�
LONG NOR );

        set("sleep_room", 1);
        set("dream", 1);
        set("no_fight", 1);
        set("objects", ([
                "/u/xiner/wash/npc/sun": 1,
        ]));
        setup();
}

void init()
{    
    object me = this_player();
    if ( !userp(me) ) return;

    add_action("do_wake", "wake");
    me->set_temp("apply/name", ({ "������" }));
    me->set_temp("apply/short", ({ "������(dream walker)" }));
    me->set_temp("apply/long", ({ "������(dream walker)\n" }));
}

int do_wake()
{
   object room, me = this_player();

   message_vision("$N��Ȼ��ƮƮ�ط���������һ�¾ͷ����ˡ�\n", me);
  
   me->delete_temp("apply/name");
   me->delete_temp("apply/short");
   me->delete_temp("apply/long");
   if ( me->query_temp("dream_place"))
   {     
      me->move(me->query_temp("dream_place")); 
      me->delete_temp("dream_place");
   } else
   me->move("/d/city/kedian");
   message_vision("$N���������˯�ۣ������˹�����\n", me); 
  return 1;
}