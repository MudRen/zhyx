// tianmo_book.c  ��ħ��
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"��ħ��"NOR, ({ "tianmo jue" , "jue" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("treasure",1);set("unit", "��");
                set("long",
                        "����һ�������Ĳ�ҳ��\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":         "tianmojue",           // name of the skill
                        "exp_required": 10000,                  // minimum combat experience required
                                                                // to learn this skill.
                        "jing_cost" :   30,
                        "difficulty":   30,                     // the base int to learn this skill
                                                                // modify is gin_cost's (difficulty - int)*5%
                        "max_skill":    99,                     // the maximum level you can learn
                        "min_skill":    0                       // the maximum level you can learn
                                                                // from this object.
                ]) );
        }
}
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int plvl, con, improve;
        int neili_lost;

        if (! arg || ! id(arg))
                return 0;

        if (me->is_busy())
        {
                write("��������æ���ء�\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (where->query("no_fight") && me->query("doing") != "scheme")
        {
                write("���޷������ﾲ�������ж���\n");
                return 1;
        }

        if ((int)me->query("jing") < 60)
        {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }


        me->receive_damage("jing", random(30) + 30);
        me->add("shen", -200);
        me->improve_skill("tianmojue", 10 + random(30));
        me->start_busy(random(1) + 1);
        write("���ж�����ħ�����������ĵá�\n");
        return 1;
}


