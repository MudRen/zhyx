#include <ansi.h> 
inherit ITEM;
void create() 
{ 
    set_name( YEL "���" NOR, ({ "zhu bang" }) ); 
    set_weight(20); 
    if( clonep() ) 
          destruct(this_object()); 
    else { 
          set("unit", "��"); 
          set("material", "bamboo"); 
          set("long", "һ������ȥ�ܲ����۵����������ۼ��߰ߣ�����ȥȴ�⻬������\n"); 
 set("owner", "ԽŮ"); 
    } 
    setup(); 
}

