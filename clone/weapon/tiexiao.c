#include <ansi.h>
#include <weapon.h>

inherit XSWORD;

void create()
{
        set_name("����", ({ "tie xiao","xiao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "֧");
                set("long", HIW "һ֧��������������������˾������������\n" NOR);
                set("value", 800);
                set("no_sell", 1);
                set("material", "stone");
                set("wield_msg", "$N����һ�ӣ������Ѷ���һ֧���\n" NOR);
                set("unwield_msg", "$N��������һת��գ�ۼ�������Ȼ����Ӱ�١�\n" NOR);
                set("stable", 100);
        }
        init_xsword(30);
        setup();
}
