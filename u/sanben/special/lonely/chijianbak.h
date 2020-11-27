#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_ITEMMAKE;


void create()
{
        set_name(HIR "�ལ" NOR, ({ "chijian" }));
        set("special", 1);
	 set_weight(15000);
	 set("item_make", 1);
	 set("unit", "��");         
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");  
        set("no_sell", 1 ); 
        set("no_steal", 1);      
        set("value",1);   
        set("point", 500);       
        set("material", "tian jing");
        set("wield_msg", HIR "�ལ����һ��������������죬˲������$N���С�\n" NOR);
        set("unwield_msg", HIG"$N���гལ�������죬ɲ�Ǽ��⾡ɢ���ལ��û����Ӱ��\n" NOR);
        if (! check_clone()) return;
        restore();
        init_sword(apply_damage());
        setup();             
       
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "china-aojue" ||
            me->query_skill("china-aojue", 1) < 150)
                return damage_bonus / 2;

        switch (random(8))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIR "ͻȻ��$N���еĳལ�������������⣬" 
                           HIR "$n" HIR "�ٳ�һ��������ԭ�ض������ã�\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_wound("jing", n / 3, me);
                victim->receive_wound("qi", n / 3, me);
                return MAG "$N" MAG "���гལ������������ɷ֮����$n" HIW
                       "��ʱֻ����Ѫ��ӿ������֮����\n" NOR;
        }
        return damage_bonus;
}

string long() { return query("long") + item_long(); }

void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }


