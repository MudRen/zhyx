//room: dongkou.c BY Yuchang

#include <ansi.h> 
inherit ROOM;

void init();
int do_zou(string);

void create()
{
  set("short","����");
  set("long",@LONG
ɽ������ͻȻ��ʧ��������ǰ��һ�����ڣ����¿�ȥ�������ƣ����
���޷�����ȵס����ڱ��и�ɽ����hole)���Ա���һ��ʯ��(bei)��
LONG
     );
  set("outdoors", "chengdu");
  set("item_desc",([
      "bei" : "������ߡ����й��ޣ�С�İ���\n" ,
      "hole" : "��������ߣ��㲻����˿���(enter)��ȥ��\n" ,
     ]));
  setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
    object me;
string msg; 
object ob; 
    me = this_player();
foreach (ob in deep_inventory(me)) 
              if (ob->is_character()) 
             { 
                            command("say ������ߣ��������죬�Ͳ�Ҫ�������˽�ȥ�ˣ�"); 
                             return 1; 
                     } 
        if( !arg || arg=="" ) return 0;
        if( arg=="hole" ) 
    {
        message("vision",
            me->name() + "һ�������������˽�ȥ��\n",
            environment(me), ({me}) );
                me->move("/u/yuchang/dong1");
                message("vision",
            me->name() + "�Ӷ������˽�����\n",
                    environment(me), ({me}) );
        return 1;
    }
}   
