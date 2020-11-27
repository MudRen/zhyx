// ת������֮ ħ��
// Create by yuchang

#include <ansi.h>

#include <armor.h> 
inherit HANDS; 

void create()
{
        set_name(HIB "ħ��" NOR, ({ "mo jie", "mojie", "ring" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "ö");
                set("long", HIG "����һö��˵�еĽ�ָ��������ѣĿ�Ĺ⻪����\n"
                                "˵�������˷���Ϊ�˴�ͨ��ؽ��紦���á�����֮\n"
                                "���������(crack)��������硣\n" NOR);
                set("material", "steel");
                set("wear_msg", HIB "$N" HIB "��ħ�������ָ����ʱһ"
                                    "������������\n" NOR);
                set("remove_msg",HIG "$N" HIG"��ħ�����ָ��ȡ������\n" NOR);
                set("value",100000);
                set("no_sell", 1);
                set("armor_prop/finger", 10);               
                set("armor_prop/unarmed", 10);  
                set("armor_prop/claw", 10);  
        }
        setup();
}

void init()
{   
     object me;        
     me = this_player();
        
     if ( !query("owner") &&    
          objectp(present("mo jie", me)))
     set("owner", me->query("id"));

     add_action("do_crack", "crack");  
    
  
}

int do_crack(string arg)
{
        object me;        
        me = this_player();
        
        if(! objectp(present("mo jie", me))) return 0;

        if (query("owner") != me->query("id") )
            return notify_fail("�ⲻ�����ħ�䣬�㲻��ʹ�ã�\n");

        if (me->is_fighting() || me->is_busy() ||
            me->query("doing") )
            return notify_fail("����æ�أ�\n");
                 
        message_sort(HIG"\n$N" HIG "���е�ħ�䷢��ҫ�����⣬"
                     "ɲ�Ǽ������¶��һ���Ѻۣ�ħ�仯��һ������Ĺ�â��$N"
                     HIG"������֮�С�\n\n" NOR, me);
                
        me->move("/d/zhuanshi/sky/sky1");
        return 1;
}

string query_autoload()
{
       if (! query("owner") ) return 0;
       return query("owner");
}

void autoload(string owner)
{
    if ( ! owner)   
     {        
        destruct(this_object());
        return;
     }
     set("owner", owner);
}

