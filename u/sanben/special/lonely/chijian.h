#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_ITEMMAKE;


void create()
{
        set_name(HIR "�ལ" NOR, ({ "chijian" }));
        set("special", 1);
	 set_weight(15000);
	 set("item_make", 1);
	 set("unit", "��");         
        set("long", "LONG_DESCRIPTION");   
        set("owner_id","ID");  
        set("no_sell", 1 ); 
        set("no_steal", 1);      
        set("value",1);   
        set("point", 560);       
        set("material", "tian jing");
        set("wield_msg", HIR "�ལ����һ��������������죬˲������$N���С�\n" NOR);
        set("unwield_msg", HIG"$N���гལ�������죬ɲ�Ǽ��⾡ɢ���ལ��û����Ӱ��\n" NOR);
        if (! check_clone()) return;
        restore();
        init_sword(apply_damage());
        setup();             
       
}
string long() { return query("long") + item_long(); }




