#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һ����ƽ����ͨ�������������ܶ������߰����ͭƤ���飬����
�Ѽ����Ŀ�ʯ����������Ժ�����ɸ���������
LONG
        );

        set("exits", ([
                "north" : __DIR__"zhudao",
        ]));
        set("no_fight",1);
        set("no_beg",1);
        set("no_steal",1);
        setup();                   
}
void init()
{
        add_action("do_zhuclub","zhuclub");
        add_action("do_quit","quit");
        add_action("do_quit","exit");
        add_action("do_quit","exercise");
        add_action("do_quit","dazuo");
        add_action("do_quit","exert");
        add_action("do_quit","learn");
        add_action("do_quit","yun");
        add_action("do_quit","xue");
        add_action("do_quit","respirate");
        add_action("do_quit","tuna");
        add_action("do_quit","fight");
        add_action("do_quit","hit");
        add_action("do_quit","kill");
        add_action("do_quit","perform");
        add_action("do_quit","persuade");
        add_action("do_quit","quanjia");
        add_action("do_quit","practice");
        add_action("do_quit","lian"); 
        add_action("do_quit","study");
        add_action("do_quit","du");
        add_action("do_quit","teach");
        add_action("do_quit","jiao");
}
int do_zhuclub()
{
        object me,ob;
        me=this_player();

        if (!(ob = present("tong kuang", this_player())) &&
            !(ob = present("tie kuang", this_player())) &&
            !(ob = present("ying kuang", this_player())) &&
            !(ob = present("jing kuang", this_player())) &&
            !(ob = present("xuantie kuang", this_player()))&&
            !(ob = present("han tie", this_player())) )
            return notify_fail("������û�п�ʯ�����������\n");

        if ( (int)me->query("jing")<100)
            return notify_fail("��ľ������㣬�޷�������\n"); 

        if( me->is_busy())
            return notify_fail("�����ں�æ������������\n");

        if ( (int)me->query("qi")<100)
                return notify_fail("����������㣬�޷�������\n");

        if ( (int)me->query("neili")<150)
                return notify_fail("����������㣬�޷�������\n");

        message_vision(HIY"$N�Ƚ���ʯ�Ž�¯�������ɿ�״״��\n"NOR,me);
        message_vision(HIY"����$N���ó�һ���󴸿�ʼ������\n"NOR,me);
        message_vision(HIY"��һ�����һ���ܺõĳ���������$N����ǰ��\n"NOR,me);
        me->add("combat_exp",50+random(20));
        me->add("potential",25+random(5));
        me->add("jing",-50);
        me->add("qi",-80);
        me->add("neili",-100);
        me->start_busy(6);

        if(present("tong kuang", me))
        {
        new(__DIR__"weapon/club/club1")->move(environment(me));
        me->add("work/zhuclub", 1);
        destruct(ob);
        return 1;     
        } else
        if(present("tie kuang", me) && me->query("work/zhuclub")>100)
        {
        new(__DIR__"weapon/club/club2")->move(environment(me));
        me->add("work/zhuclub", 1);
        destruct(ob);
        return 1;     
        }else
        if(present("ying kuang", me) && me->query("work/zhuclub")>200)
        {
        new(__DIR__"weapon/club/club3")->move(environment(me));
        me->add("work/zhuclub", 1);
        destruct(ob);
        return 1;     
        }else
        if(present("jing kuang", me) && me->query("work/zhuclub")>300)
        {
        new(__DIR__"weapon/club/club4")->move(environment(me));
        me->add("work/zhuclub", 1);
        destruct(ob);
        return 1;     
        }else
        if(present("xuantie kuang", me) && me->query("work/zhuclub")>400)
        {
        new(__DIR__"weapon/club/club5")->move(environment(me));
        me->add("work/zhuclub", 1);
        destruct(ob);
        return 1;     
        }else
        if(present("han tie", me) && me->query("work/zhuclub")>500)
        {
        new(__DIR__"weapon/club/club6")->move(environment(me));
        me->add("work/zhuclub", 1);
        destruct(ob);
        return 1;     
        }else
        {
        write("����������켼��̫���ˣ�����ı������������ã�\n");
        destruct(ob);
        return 1;     
        }

}

int do_quit()
{
        write("�㻹�Ǻúõ���������ɣ�\n");
        return 1;
}

