
#include <ansi.h>
 
inherit ITEM;

int is_head() { return 1; }

void create()
{
        set_name(HIG "��ͨ�ҽ���" NOR, ({ "common card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "ƾ������ͨ��������������˷�������һ�һ�㽱��������\n"NOR);			
                set("unit", "��");
                set("value", 10);
                set("gft_pt", 1);
                set("weight", 1);
                set("material", "paper");		  		  
             }	         
        setup();
}

void init()
{
     remove_call_out("dest");
     call_out("dest", 600);     

}

void dest()
{
     tell_room(environment(), HIR"����ͻȻ�����ˡ�\n"NOR);
     destruct(this_object());

}


		
