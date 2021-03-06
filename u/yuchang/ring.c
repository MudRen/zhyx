//Cracked by yuchang
// ring.c 魔鬼戒指

#define UNIQUE  100000000
#include <armor.h>
#include <ansi.h>


inherit FINGER;
inherit F_AUTOLOAD;

int query_autoload() { return 1; }

void create()
{
        set_name(HIW+BLK"魔鬼戒指"NOR, ({ "Magic ring", "ring" }));
        set("weight", 200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", UNIQUE);
                set("material", "platinum");
                //set("no_sell", 1);
              
                set("armor_prop/armor", 2000);
                set("weapon_prop/damage", 1000);

                set("wear_msg", HIW+BLK"刹那间，一股的氤氲之气，弥漫在众人周围。使你不寒而栗...\n"NOR);

                set("unequip_msg", HIW+BLK"但见$N左手一晃，$n"+ HIW+BLK+"突然间消失在众人面前！\n"NOR);

                }
        setup();
}       

void init()
{
        object me = this_player();
                
        if( !me->query_temp("ring_worn") ) 
        {
                if( me->query("gender") == "女性" )
                        set("long", HIW+BLK "一枚黑乎乎的黑金戒指，它拥有无穷的魔力。\n戒指上刻着几个小字：「性感小猫」\n" NOR);
                else
                        set("long", HIW+BLK "一枚黑乎乎的黑金戒指，它拥有无穷的魔力。\n戒指上刻着几个小字：「花花公子」\n" NOR);
                set("no_drop", 1);
                set("no_get", 1);       
                //wield();
                //add_action("disable_remove", "remove");
        } 
        else
        {
                set("long", HIW+BLK "一枚黑乎乎的黑金戒指，它拥有无穷的魔力。\n" NOR);
                set("no_drop", 0);
                set("no_get", 0);       
                //remove_action("disable_remove", "remove");
        }       
                
        return;
}

int disable_remove(string arg)
{
        if (!id(arg)) 
                return notify_fail("你要脱掉什么？\n");
                
        //这里使用蓝色
        write(HIW + BLK "魔戒，魔戒，让你永不超升，它会象影子一样永远跟随着你，直到你死。\n"NOR);
        return 1;
}

int wear()
{
        object me = environment();
        object ob = this_object();
        int ret;
        
        if( ret = ::wear() )
        {

                message_vision(HIW+BLK"只见$N将怀中指环王迎风一举，乌黑的戒指自然带出来一股神秘的气息，不知不觉间你心中对$N充满了恐惧！\n"NOR, me);
                me->add("neili",20000);
                call_out("special_effect", 1, me);
                return ret;
        }
}

int special_effect(object me)
{
        mapping weapon_prop;
        object *obj, *inv, weapon;
        int i, j;

        obj = all_inventory(environment(me));
        for( i=0; i < sizeof(obj); i++ )
        {
                if( obj[i]==me ) continue;
                inv = all_inventory(obj[i]);
                for( j=0; j < sizeof(inv); j++ )
                {
                        if( !mapp(weapon_prop = inv[j]->query("weapon_prop")) ) continue;        
                        if( inv[j]->query("skill_type")!="sword" ) continue;
                        if( inv[j]->query("equipped") )
                        {
                                if(obj[i]->query("neili") > 5000)
                                {
                                        obj[i]->add("neili", -2000);
                                        tell_object(obj[i], HIW"你觉得手中之"+inv[j]->name()+HIW"在猛烈震动，幸而你双手紧握，才没有让它飞出！\n"NOR);
                                        continue;  
                                }
                                else
                                {
                                        obj[i]->add("neili", -1000);
                                        
                                        tell_object(obj[i], HIW"你觉得手中之"+inv[j]->name()+HIW"在猛烈震动，你把握不住，竟然脱手飞出！\n"NOR);

                                        tell_room(environment(me), YEL+obj[i]->name()+"一个把握不住，手中"+inv[j]->name()+YEL"竟然脱手飞出！\n"NOR, ({ obj[i] }));
                                        
                                        inv[j]->move(environment(me));
                                        
                                        continue;
                                }
                        }
                        else if( obj[i]->is_character() )
                                message_vision(HIY"$n身上所带之"+inv[j]->name()+HIY"忽然自动跃出，插在$N身前的地上，剑尖指天！\n"NOR, me, obj[i]);
                        else message_vision(HIY+inv[j]->name()+HIY"忽然自$n飞出，插在$N身前的地上，剑尖指天！\n"NOR, me, obj[i]);
                }
        }
}

