#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_ITEMMAKE;


void create()
{
        set_name(HIR "������Ů��" NOR, ({ "xuannvjian" }));
        set_weight(5000);
        set("special", 1);
        set("unit", "��");        
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");  
        set("no_sell", 1 ); 
        set("value",1000000);      
        set("no_steal", 1);      
        set("material", "tian jing");
        set("wield_msg", HIR "������Ů��������ʣ�����һ���ʺ磬ҫ����֣�˲������$N���С�\n" NOR);
        set("unwield_msg", HIG"$N������Ů���������죬ɲ�Ǽ�ϼ�⾡ɢ��������û����Ӱ��\n" NOR);
        if (! check_clone()) return;
        restore();
        init_sword(250);
        setup();             
       
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "xuannv-jian" ||
            me->query_skill("xuannv-jian", 1) < 150)
                return damage_bonus / 2;

        switch (random(8))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIR "ͻȻ��$N���еľ�����Ů���ƺ��û����������ʺ磬" 
                           HIR "$n" HIR "�ٳ�һ��������ԭ�ض������ã�\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_wound("jing", n / 3, me);
                victim->receive_wound("qi", n / 3, me);
                return MAG "$N" MAG "���о�����Ů��������������ϼ֮����$n" HIW
                       "��ʱֻ����Ѫ��ӿ������֮����\n" NOR;
        }
        return damage_bonus;
}



void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }

