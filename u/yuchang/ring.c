//Cracked by yuchang
// ring.c ħ���ָ

#define UNIQUE  100000000
#include <armor.h>
#include <ansi.h>


inherit FINGER;
inherit F_AUTOLOAD;

int query_autoload() { return 1; }

void create()
{
        set_name(HIW+BLK"ħ���ָ"NOR, ({ "Magic ring", "ring" }));
        set("weight", 200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", UNIQUE);
                set("material", "platinum");
                //set("no_sell", 1);
              
                set("armor_prop/armor", 2000);
                set("weapon_prop/damage", 1000);

                set("wear_msg", HIW+BLK"ɲ�Ǽ䣬һ�ɵ���֮����������������Χ��ʹ�㲻������...\n"NOR);

                set("unequip_msg", HIW+BLK"����$N����һ�Σ�$n"+ HIW+BLK+"ͻȻ����ʧ��������ǰ��\n"NOR);

                }
        setup();
}       

void init()
{
        object me = this_player();
                
        if( !me->query_temp("ring_worn") ) 
        {
                if( me->query("gender") == "Ů��" )
                        set("long", HIW+BLK "һö�ں����ĺڽ��ָ����ӵ�������ħ����\n��ָ�Ͽ��ż���С�֣����Ը�Сè��\n" NOR);
                else
                        set("long", HIW+BLK "һö�ں����ĺڽ��ָ����ӵ�������ħ����\n��ָ�Ͽ��ż���С�֣����������ӡ�\n" NOR);
                set("no_drop", 1);
                set("no_get", 1);       
                //wield();
                //add_action("disable_remove", "remove");
        } 
        else
        {
                set("long", HIW+BLK "һö�ں����ĺڽ��ָ����ӵ�������ħ����\n" NOR);
                set("no_drop", 0);
                set("no_get", 0);       
                //remove_action("disable_remove", "remove");
        }       
                
        return;
}

int disable_remove(string arg)
{
        if (!id(arg)) 
                return notify_fail("��Ҫ�ѵ�ʲô��\n");
                
        //����ʹ����ɫ
        write(HIW + BLK "ħ�䣬ħ�䣬��������������������Ӱ��һ����Զ�������㣬ֱ��������\n"NOR);
        return 1;
}

int wear()
{
        object me = environment();
        object ob = this_object();
        int ret;
        
        if( ret = ::wear() )
        {

                message_vision(HIW+BLK"ֻ��$N������ָ����ӭ��һ�٣��ںڵĽ�ָ��Ȼ������һ�����ص���Ϣ����֪�����������ж�$N�����˿־壡\n"NOR, me);
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
                                        tell_object(obj[i], HIW"���������֮"+inv[j]->name()+HIW"�������𶯣��Ҷ���˫�ֽ��գ���û�������ɳ���\n"NOR);
                                        continue;  
                                }
                                else
                                {
                                        obj[i]->add("neili", -1000);
                                        
                                        tell_object(obj[i], HIW"���������֮"+inv[j]->name()+HIW"�������𶯣�����ղ�ס����Ȼ���ַɳ���\n"NOR);

                                        tell_room(environment(me), YEL+obj[i]->name()+"һ�����ղ�ס������"+inv[j]->name()+YEL"��Ȼ���ַɳ���\n"NOR, ({ obj[i] }));
                                        
                                        inv[j]->move(environment(me));
                                        
                                        continue;
                                }
                        }
                        else if( obj[i]->is_character() )
                                message_vision(HIY"$n��������֮"+inv[j]->name()+HIY"��Ȼ�Զ�Ծ��������$N��ǰ�ĵ��ϣ�����ָ�죡\n"NOR, me, obj[i]);
                        else message_vision(HIY+inv[j]->name()+HIY"��Ȼ��$n�ɳ�������$N��ǰ�ĵ��ϣ�����ָ�죡\n"NOR, me, obj[i]);
                }
        }
}

