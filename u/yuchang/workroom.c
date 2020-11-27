#include <ansi.h>

inherit "/inherit/room/arearoom.c";

void create ()
{
        set ("short",HIR"��ħ"NOR+HIC"��Է"NOR);
        set ("long",

HIY"�����ǣ��˷��ƣ�Ϊ����ѧϰ���޽��Ĺ����ҡ�\n"NOR
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
                "sanben" : "/u/sanben/workroom",
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


void init()
{
        object me = this_player();
        tell_room( environment(me), CYN"���ص���˵������ע�⣬" + me->query("title") + " "
                + me->query("name") + "(" + me->query("id") + ")" + " �����˹����ң�����\n"NOR);

}
int valid_leave(object me, string dir)
{
              if(me->query("id")=="yuchang")
                return ::valid_leave(me, dir);
                 // temp access for future wiz.
                    if(me->query("id") != "yuchang")
                            return notify_fail(CYN"���ص���"HIR"����˵����ҧ���㣡"HIG"ħ���"HIR"��Ҳ���Ҵ������Ǻúô��Űɡ�\n"NOR);
                    if( dir=="out" && !wizardp(me))
     return notify_fail(CYN"���ص���"HIR"����˵����ҧ���㣡"HIG"ħ���"HIR"��Ҳ���Ҵ������Ǻúô��Űɡ�\n"NOR);
         return ::valid_leave(me, dir);
}


