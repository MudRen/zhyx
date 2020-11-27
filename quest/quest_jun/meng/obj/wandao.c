// gangdao.c
#include <ansi.h>
#include <weapon.h>
inherit BLADE;
void create()
{
        set_name(HIW"�䵶"NOR, ({ "wan dao","blade" }));
        set_weight(12000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�����λεĸֵ����ǹٱ��ĳ���������\n");
                set("value", 1000);
                set("rigidity",200);
                set("no_get",1);
                set("no_put",1);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
        }
        init_blade(400);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       object weapon=this_object();
       int dam;

       if( weapon->query("equipped"))
       {
        dam = me->query_temp("jun_quest/group") 
              * weapon->query("weapon_prop/damage")/10;
        dam = dam/4+random(dam/3);

        if( dam < 40 )
          message_vision(
          BLINK+HIM"$N�������⵽��������ʧ�˲��־��ӣ�\n"NOR,victim);
        else if( dam < 80 )
          message_vision(
              BLINK+HIM"$N�������⵽��������ʧ���أ���\n"NOR,victim);
        else if( dam < 120 )
          message_vision(
          BLINK+HIM"$N���о��⵽�������ʧ��������\n"NOR,victim);
        else  
          message_vision(
          BLINK+HIM"$N��ȫ�������˵о���������������ڵ�Ϧ����\n"NOR,victim);  

        victim->receive_damage("qi",dam,me);
        victim->receive_wound("qi",dam,me); 
       }
       return 0;
}

void owner_is_killed() { destruct(this_object()); }  

