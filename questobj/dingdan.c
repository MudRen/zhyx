
inherit ITEM;
#include <ansi.h>
void create()
{
    set_name( HIM"�ͻ�����" NOR, ({ "dingdan" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "��");
            set("material", "paper");
            set("long", "һ����ϸ�Ķ���������������Ժ��Ԥ�������\n");
	}
}