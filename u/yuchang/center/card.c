#include <ansi.h>
  inherit "/clone/fam/gift/gift";

void create()
{
        set_name(HIY "�л�Ӣ�ۻ�Ա��" NOR, ({ "huiyuan card", "card", "huiyuan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�ž��µĿ�Ƭ,���л�Ӣ�ۻ�Աӵ��,�����ſ�Ƭ"
                                  "�������ɳ���\n���л�Ӣ�ۻ�Ա�������ġ����ҿ���"
                                "�õ���صķ���\n" NOR);
                set("base_unit", "��");
                set("base_value", 10);
                set("base_weight", 50);
        }
        setup();
}


