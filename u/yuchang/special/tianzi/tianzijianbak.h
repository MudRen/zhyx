#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_ITEMMAKE;


void create()
{
        set_name(HIY "�������ӽ�" NOR, ({ "tianzijian" }));
        set_weight(5000);
        set("special", 1);
        set("unit", "��");        
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");  
        set("no_sell", 1 ); 
        set("value",1000000);
       // set("no_put", 1); 
        set("no_steal", 1); 
      //  set("no_drop", 1); 
      //  set("no_get", 1); 
        set("material", "tian jing");
        set("wield_msg", HIY "�������ӽ�������ʣ�������ҫ����֣�ȴ��������$N" HIY"���С�\n" NOR);
        set("unwield_msg", HIY "$N" HIY "���쳤Х���������ӽ��������죬ɲ�Ǽ��⾡ɢ�����ӽ�����"
                          "û����Ӱ��\n" NOR);
        if (! check_clone()) return;
        restore();
        init_sword(250);
        setup();             
       
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "tianzi-jianfa" ||
            me->query_skill("tianzi-jianfa", 1) < 150)
                return damage_bonus / 2;

        switch (random(8))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIR "ͻȻ��$N���е��������ӽ��ƺ�����һ��������" 
                           HIR "$n" HIR "�ٳ�һ��������ԭ�ض������ã�\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_wound("jing", n / 3, me);
                victim->receive_wound("qi", n / 3, me);
                return HIW "$N" HIW "�����������ӽ�����������������$n" HIW
                       "��ʱֻ����Ѫ��ӿ������֮����\n" NOR;
        }
        return damage_bonus;
}



void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }

