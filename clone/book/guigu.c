// guigu.c �������

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT "�������" NOR, ({ "guigu book", "book", "shu" }));
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "��˵�ǵ����������������顣\n");
                set("value", 100);
                set("no_sell", "��...��ֵʲôǮ��\n");
                set("material", "silk");
                set("skill", ([
                        "name": "mathematics", // name of the skill
                        "jing_cost":   480,    // jing cost every time study this
                        "difficulty":  108,    // the base int to learn this skill
                        "max_skill":   450,    // the maximum level you can learn to
                        "min_skill":   349,    // minimun level required
                ]));
        }
}
