#include <ansi.h>

inherit ROOM;

void create ()
{
          set ("short",HIR"��"NOR+HIC"�ĸ�"NOR);
        set ("long",

  HIY"�����ǣ���ɽ��ѩ��Ϊ����ѧϰ���޽��Ĺ����ҡ�\n"NOR
HIY"��Ŀ�����µĻ��ݳ����������ķ��䡣\n"NOR
"\n\n"



HIG"...��..����.....��..���...��...��.....��........����\n"NOR
HIG"��..��..�����ɽˮ��....����..����....��.....��......\n"NOR
HIG"...����..��..��..........����.��..��¶Ϊ����Ϊ��...��...\n"NOR
HIG"...��..��...�������ҹ�δ�.��.�...��..��..��..��...��\n"NOR
HIG"��.......��.��...��...��.��....��������Ҽ�.����......\n"NOR
HIG"...��..����.....��..���...��...��.....��........����\n"NOR

"\n\n"
);
       set("item_desc" , ([
"down": "�������������ƣ�ʲôҲ���������\n",
]));
set("exits", 
        ([
                "out" : "/u/yuchang/tianzun",
                "down" : "/d/city/guangchang",
                ]));


        set("no_death", 1);
        set("no_fight", 1);
        set("no_kill", 1);
        set("no_time", 1);
        set("sleep_room", 1);

        set("no_clean_up", 0);
        set("start_room", 1);
        setup();
        call_other("/clone/board/yuchang_b", "???"); 

}

