#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
void create()
{
        set_name(HIG  "ǧ������" NOR, ({ "old jade" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);   else {
                set("unit", "��");
                set("long", "һ�����˵���ʯ���̵�����ѽ����������һ��С�֣���ɽ�ɣ����ƺ�����������������\n");
                set("max_cure",10);
                set("material", "stone");
        }
        init_hammer(10);
        setup();
}

