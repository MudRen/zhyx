#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_XIAO;

void create()
{
        set_name(NOR + GRN "������" NOR, ({ "zhu xiao", "zhu", "xiao" }));
        set_weight(600);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "bamboo");
                set("unit", "ֻ");
                set("long", "����һ����ϰ�����õ�������\n");
                set("wield_msg", "$N�ó�һ��$n���������С�\n");
                set("unequip_msg", "$N�������е�$n��\n");
        }
        setup();
}

void init()
{
        add_action("play_xiao", "play");
}

