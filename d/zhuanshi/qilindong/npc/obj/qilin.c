//Cracked by Yuchang
#include <ansi.h>

inherit ITEM; 
void create()
{
        set_name( RED"�����"NOR, ({ "qilin bi", "qilin", "bi", "arm" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("long", "����һ���ֱۣ��ഫ����������ʱ�ಲ���������룬��۱�����Ѫ�������ɡ�\n");
                set("unit", "��");
                set("value", 150);
                set("no_sell", 1);
        }
        setup();
}


int query_autoload()
{
       return 1;
}

