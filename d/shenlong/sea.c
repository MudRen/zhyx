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
      add_action("do_swimming", "swim");
      add_action("do_swimming", "youyong");
}

int do_swimming()
{
    object me = this_player();
    int t = (int)me->query("max_qi");

    tell_object(me, "������Ӷ�˫�ۣ�����Ŀ�ĵ���ǰ��ȥ��\n");
    me->receive_damage("qi", t/10 + random(t/5));

    if (random(3) == 1)
       tell_object(me, HIC"ͻȻ�㿴��һ�����������������㼱æת��ƴ����ǰ��ȥ��\n"NOR);

    if (random(10) < 5)
    {
       tell_object(me, "���ۼ�������Խ��Խ�������ɾ���һ��\n"); 
       if (random(10) < 6)
       {
          me->move("/d/shenlong/haitan");
          tell_object(me, "�������ε����ߣ�����ʪ����������������\n"); 
          message("vision", "�㷢��һ������ˮ���ܵļһﱻ��ˮ���ϰ��������ɵ��߽�һ����ԭ����" +
                   me->name() + "��\n", environment(me), me);
       }
    }
    else
    {
       if ((int)me->query("qi") < 0)
       {
           me->set("qi", 0);
           tell_object(me, "���ƣ����������ʧȥ��֪����\n");
           me->unconcious();
           me->move("/d/shenlong/haitan");
           message("vision", "�㷢��һ������ˮ���ܵļһﱻ��ˮ���ϰ��������ɵ��߽�һ����" +
                   "ԭ����" + me->name() + "��\n", environment(me), me);
       }
    }
    return 1;
}

