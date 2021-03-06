#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_ITEMMAKE;


void create()
{
        set_name(HIY "真命天子剑" NOR, ({ "tianzijian" }));
        set_weight(5000);
        set("special", 1);
        set("unit", "把");        
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");  
        set("no_sell", 1 ); 
        set("value",1000000);
       // set("no_put", 1); 
        set("no_steal", 1); 
      //  set("no_drop", 1); 
      //  set("no_get", 1); 
        set("material", "tian jing");
        set("wield_msg", HIY "真命天子剑划破天际，阵阵金光耀眼万分，却早已落入$N" HIY"手中。\n" NOR);
        set("unwield_msg", HIY "$N" HIY "仰天长啸，真命天子剑叮呤做响，刹那间金光尽散，天子剑早已"
                          "没了踪影。\n" NOR);
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
                return HIR "突然间$N手中的真命天子剑似乎化作一条金龙，" 
                           HIR "$n" HIR "顿吃一惊，呆在原地动弹不得！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_wound("jing", n / 3, me);
                victim->receive_wound("qi", n / 3, me);
                return HIW "$N" HIW "手中真命天子剑激荡出阵阵龙吟，$n" HIW
                       "顿时只觉气血上涌，难受之极！\n" NOR;
        }
        return damage_bonus;
}



void owner_is_killed()
{
        destruct(this_object());
} 
int query_autoload() { return 1; }

