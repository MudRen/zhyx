#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW"���佣"NOR, ({"zhenwu jian", "sword", "zhenwu"}));
        set_weight(15000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ�Ѻ������۵ĹŽ�,��������Ļ������ƺ�������Щ����,�����Ͼ�Ȼ���м���ȱ�ڡ�\n");
                set("value", 100000);
                set("material", "blacksteel");
                set("weapon_prop/dodge", -2);
                set("weapon_prop/parry", 3);
                set("treasure",1);       
                set("wield_neili", 300);
                set("wield_maxneili", 700);
                set("wield_str", 22);        
                set("wield_msg",HIW"$N[��]��һ�����һ�����佣,�����ж�ʱ�������ޱߵ�ɱ����\n"NOR);
                set("unwield_msg",HIW"$N�����еı������뽣�ʡ����ܵ�ɱ��Ҳ������ʧ�ˡ�\n"NOR);
        }
        init_sword(300);
        setup();
}       

