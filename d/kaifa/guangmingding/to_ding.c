#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"����������"NOR);
        set("long",  "\n"
"���������̹��������ţ��ɴ���ȥ����ͨ��"HIY"���̹�������\n"NOR 
 );
        set("exits",([
           "out" : "/d/wizard/skybook",
        ]));
        set("objects",([
        ]));
        setup();

}

void init()
{       mapping mine;
       object me;
        me = this_player();
        if ( me->query("skybook/tulong/tulongdao") > 0
        &&    me->query("skybook/tulong/winguangming") < 1)
        {
         message_sort(HIR"�ۿ����������Ѿ����Ϲ�������������ǧ���������������ڴ�\n"NOR
                        HIR"ʱ����Ը���ʱ�˿����"HIW"(wanjiu)"HIR"������Σ��֮����\n"NOR, me);
        add_action("do_wanjiu", "wanjiu");
        }
}
int do_wanjiu()
{
    object me = this_player(), where = environment(me);

            if ( where->query_temp("temp/guangmingding", 1))
    {
       message_vision("������ɱ�ù���أ��㻹�ǵȵȰɡ�\n",me);
       return 1;
    }
        message_vision(HIC "\n$N" HIC "����һԾ�������˹��������壬\n"
                       "ֻ�����̵����������أ���������\n"
                       "һ����""$N""����һ������Χ��������"
                       "\n\n" NOR, me);
          where->set_temp("temp/guangmingding", 1);
        me->move(__DIR__"ding");

        me->start_busy(3); 

        return 1;
}

