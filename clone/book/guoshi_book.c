// guoshi_book.c  �����ķ�
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG"�����ķ�"NOR, ({ "guoshi_book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("no_sell",1);
                set("long",
                        "ѧ�����ķ���\n");
                set("value", 100000);
                set("material", "paper");
                set("skill", ([
                        "name":         "guoshi-xinfa",       // name of the skill
                        "exp_required": 100000,                 // minimum combat experience required
                                                                // to learn this skill.
                        "jing_cost" :   30,
                        "difficulty":   30,                     // the base int to learn this skill
                                                                // modify is gin_cost's (difficulty - int)*5%
                        "max_skill":    179,                    // the maximum level you can learn
                        "min_skill":    10                       // the maximum level you can learn
                                                                // from this object.
                ]) );
        }
}
