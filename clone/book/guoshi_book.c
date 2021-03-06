// guoshi_book.c  郭氏心法
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG"郭氏心法"NOR, ({ "guoshi_book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("no_sell",1);
                set("long",
                        "学郭氏心法。\n");
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
