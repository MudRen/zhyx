// sea.c
// Modified by haiyan

#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "��");
        set("long",@LONG
��������ãã��֮�С��㼫ĿԶ����ֻ������һ�ߣ���Χ�����ڵ㶼û�С�
����ֻ�к��˵��Ĵ�����
LONG);   
        set("no_clean_up", 0);
        setup();
}

void init()
{
      add_action("do_swimming", "swimming");
      add_action("do_swimming", "youyong");
}

int do_swimming()
{
    object me = this_player();
    tell_object(me, "������Ӷ�˫�ۣ�����Ŀ�ĵ���ǰ��ȥ��\n");
    me->receive_damage("qi", 20 + random(20));

    if (random(10) < 3)
       tell_object(me, HIC"ͻȻ�㿴��һ�����������������㼱æת��ƴ����ǰ��ȥ��\n"NOR);

    if ((int)me->query("qi") < 0)
    {
       me->set("qi", 0);
       tell_object(me, "���ƣ����������ʧȥ��֪����\n");
       me->unconcious();
       me->move("/d/shenlong/haitan");
       message("vision", "�㷢��һ������ˮ���ܵļһﱻ��ˮ���ϰ��������ɵ��߽�һ����ԭ����" +
                me->name() + "��\n", environment(me), me);
    }       
    return 1;
}

