
//���ϻ�ͯ�� (����3-5������)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "���ϻ�ͯ��" NOR, ({ "huantong dan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "һ����˵�е��ɵ�����˵�Ժ��ܷ��ϻ�ͯ��\n" NOR);
                set("unit", "��");
                set("value", 10);
                set("weight", 10);                
             }
        setup();
}

void init()
	{
		add_action("do_eat","eat");
	}
		

int do_eat( string arg )
{		 
        int num, rdm;
	 object me  = this_player();

        if ( ! arg || (arg != "huantong dan" && arg != "dan") )
          return 0;	
	
        if (me->query("age") < 28 )
        {
           write(HIG"�㻹���ᣬ�ò��ų��ⶫ����\n"NOR);
           return 1;
        }

        message_vision(HIY "$N����ͯ��һ�����¡�\n" NOR, me);

        num = 1 - me->query("reborn_start/huantong");
        if ( num > 1 ) 
        {
            rdm = random(num);
            if ( rdm == 0 ) rdm = 1;
            me->add("mud_age", - rdm * 2 * 260000);
            
            tell_object(me, HIG"��������巢��������ı仯��"
                        "�ƺ�һ�л��ܶ���������\n"NOR
                     HIR"��ͻȻ�е�ͷʹ���ѣ������ε�......\n"NOR, me);       
	     me->unconcious(); 
        } else             
            tell_object(me, HIY"�����������ҩ�ƺ�ûɶ���á�\n"NOR, me);

       me->add("reborn_start/huantong", 1);
       destruct(this_object());
       return 1;
}
		
int query_autoload() { return 1; }

       	