// yuchang
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������һ��ˮ���С����߼�����ʲôҲ������, 
��ģģ�����ĸо����Ա߶��Ǿ���,��ˮ�����̹�,
ʹ��е���ƭ�ĸо�,������(ti)�˵ĸо�!
LONG);
        set("exits", ([
                "up" : __DIR__"yuanzi",
        ]));       
        setup();
}

void init()
{
        add_action("do_ti", "ti");
        add_action("do_an", "an");
}

int do_ti(string arg)
{
    object me;
    me = this_player();

    if (!arg || arg != "wall") return notify_fail("����Ҫ��(wall)��\n");
           
    write("������һ�ţ��о�����������ʲô����,�������԰�(an wall)����!\n");
    me->set_temp("tiwall", 1);
    return 1;
}

int do_an(string arg)
{
    object me;
    object room; 
    me = this_player();

    if (! me->query_temp("tiwall", 1)) return 0;

    if( !arg || arg != "wall" ) return notify_fail("����Ҫ��(wall)��\n");
  
       message_vision(HIG"\n$N���߼�����ʯ��������ȥ,�����ˡ����������죬\n"
                      "�������ھ��׵�խ���ռ���ⴥ����\n"NOR, me); 

       message_vision(HIY"\n��赻���������ȥ��¶��������һ��ͨ������ڡ�\n"
                      "$N��������˽�ȥ��\n\n"NOR, me);
            
     me->move(__DIR__"tongdao1");
     message("vision", HBRED"�����ش��š�" + me->query("name") + 
                "�ɹ������������!\n"NOR, users());

     me->delete_temp("tiwall");
     return 1;        
}
    