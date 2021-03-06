#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIB "上古虎魄" NOR, ({"hu po", "hu", "po"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIB "\n一块蓝色的虎魄，无暇的表面射魄出奇幻的光\n"
                            "泽。其中仿佛蕴藏着无穷的魔力，这便是传说\n"
                            "中的至宝，凶中之凶的——上古虎魄，相传为\n"
                            "上古时代，蚩尤所得异物炼制而成。\n" NOR);
                set("unit", "块");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "hu po");
                set("material_name", HIB "上古虎魄" NOR);
                set("can_make", "all");
                set("power_point", 180);
        }
}
