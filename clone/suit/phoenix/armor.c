// ����װ��
// update by kasumi
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
void create()
{
        set_name( RED"��ȸ֮��"NOR, ({ "phoenix armor","armor","jia" }) );
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", RED"����һ����ʰ�쵵����¡�"NOR"
����ָ����150~250
����Ч�����ٷ�֮��ʮ�ļ��ʻ�����ֵĹ�����
����װ����"HIR"[��ȸ֮��]"NOR" "RED"��ȸ֮��"NOR" "YEL"��ȸ֮��"NOR" "GRN"��ȸ֮צ"NOR" "HIC"��ȸ֮��"NOR"
��װЧ����"HIG"��ʱ���Ӷ��ټ��������ԡ�"NOR"\n");
                set("value", 100000); 
                set("material", "feather");                              
                set("armor_prop/armor", 150 + random(100));
                set("warm_cloth", 1);  
                set("no_sell", 1 );
                set("no_steal", 1 );              
        }
        setup();
}

int query_autoload()
{
        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;       

        if (random(5)==1 )
        {               
                result = ([ "damage": -damage ]);               
                result += (["msg" : HIM"ֻ����â��ţ�$N����֮����$n���������¾�Ȼ������ë��������ת��������$N�Ĺ�����\n"NOR]);                     
                return result;
        }
}
