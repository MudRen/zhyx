// ����Ů����

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "����Ů����" NOR, ({ "statue of liberty", "statue"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "����һ���������Ƶ�Ů���������������һ��ʥ����\n"
                                "���־���һ����棬���������˿�����õ����ɡ���\n"
                                "��ĵײ��е��ţ��ƺ�����(enter statue)��\n"NOR);
                set("unit", "��");                
                set("no_sell",1);
                set("weight", 10000);
                set("no_get",1);                
             }
        setup();
}

void init()
{
    add_action("do_enter", "enter"); 
    
}

int do_enter(string arg)
{
   object me = this_player();
   
   if ( ! arg || ( arg != "statue" && 
        arg != "statue of liberty" ) )
   return notify_fail("��Ҫ��ȥ���\n");

   message_vision("$N��Ů����ĵײ����˽�ȥ��\n\n" , me);

   me->move(__DIR__"floor1");
   return 1;
}





