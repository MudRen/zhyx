// by yuchang
inherit ROOM;
#include <ansi.h>
#include <room.h>
int do_press(string arg);

void create()
{
      set("short", "�ؽ�®");
      set("long",
                "������ǰ���ɽׯ�Ĳؽ�®��ֻ����ǽ����һ���޴��\n"
                "��ľ��������(shelf)��������һ���޴�Ľ�¯(stove)"
                "����\n��ȼ���������һ���Լ�ɿ����һ�����һ�ѳ��ɫ"
                "�ı�����\n");
      set("exits",([
           "south" : __DIR__"cjl2",
      ]));

      set("item_desc", ([
      "shelf" : "����һֻ�������ľ������������佣�ļ��ӣ�\n"
                "�����ƺ��п����ƿ����ó���(take lingpai)��\n",
      "stove" : HIR"��¯����ȼ���������һ���Լ�ɿ����һ�����һ�ѳ��ɫ\n"
                "�ı�������β�����(get sword)?\n"NOR,
      ])); 

       setup();
}

void init()
{
      add_action("do_get", "get");
      add_action("do_press", "press");
      add_action("do_take", "take"); 
}
/*
int do_press(string arg)
{
    string p;
    object me,obj;
    object ob;
    me = this_player();
    ob = this_object();

    p = this_player()->query("reborn_start/jshj/pswd"); 

    if ( me->query(query("reborn_start/jshj/get")) ); 
       return notify_fail("�㲻���Ѿ��õ�������\n");

    if( ! arg )
       return notify_fail("��Ҫ�����������ɶ��\n");

    if( arg == p )
    {
        message_vision("$Nֻ����һ��¡¡��������Զ������\n", me);
        message_vision("��¯�������˿�����¶��һ������һ�ѱ���������$N��ǰ��\n", me);
        obj = new ("/d/zhuanshi/obj/jiushi");
        obj->move(me);
        return 1;
    }
    else
    {
            message_vision("$Nһ���Ұ���ͻȻʯ��ķ�϶�����һ֧��������\n", me);
            me->unconcious();
            return 1;
    }
}*/

int do_get(string arg)
{
    object me = this_player();   

    if( !arg || arg != "sword" ) 
       return 0;

    if ( ! me->query_temp("reborn_start/jshj/key") )
    {
       message_vision(HIC"$N��ϸһ���ŷ���ԭ����¯��������û��Կ���Ǵ򲻿��ģ�\n" NOR, me);       
       return 1;
    }
    return 0;
}


int do_take(string arg)
{
       object me,obj;
       object ob;
       me = this_player();
       ob = this_object();

       if( !arg || arg != "lingpai" && arg !="ling" && arg != "pai" ) 
           return notify_fail("��Ҫ��ʲô��\n");

       if (me->query("reborn_start/jshj/ling")) 
       {
          write("�㲻���Ѿ���һ����������\n");
          return 1;
       }

       obj = new (__DIR__"npc/obj/ling");      
       obj->move(me);      

       message_vision(HIC"$N���ִӼ�����ȡ��һ����������\n" NOR, me);      
       me->set("reborn_start/jshj/ling",1);
       me->start_busy(2);
       return 1;
}



