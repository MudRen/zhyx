#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "巨灵神图" NOR, ({ "dali tu", "dali", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "一名天神，手持巨斧，开天辟地的图案");
                set("can_tattoo", ({ "胸口", "后背", }));
                set("tattoo_type", ({ "臂力" }));
                set("tattoo_str", 4);
                set("tattoo_special", "kingkong");
                set("tattoo_spcname", "大力金刚");
        }
}
