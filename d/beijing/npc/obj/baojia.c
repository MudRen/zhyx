#include <ansi.h>
#include <armor.h>
inherit ARMOR;
void create()
{
        set_name( CYN"��˿"NOR+HIY"����"NOR,  ({ "bao jia", "jia", "armor" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ��������ļף��������ۡ�\n");
                set("no_drop", "�������������뿪�㡣\n");
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_put", "�����������ܷ����Ƕ���\n");
                set("no_steal", "�������������뿪�Ƕ���\n");
                set("no_beg", "�������������뿪�Ƕ���\n");
                set("no_sell", "����������������\n");
                set("value", 100000);
                set("material", "cloth");
                set("armor_prop/armor", 200);
        }
        setup();
}


