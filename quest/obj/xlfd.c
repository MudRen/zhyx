#include <ansi.h>
#include <weapon.h>
inherit THROWING;
void create()
{
   set_name(RED"С��ɵ�"NOR,({"xlfd"}));
   set_weight(200);
   if(clonep())
        set_default_object(__FILE__);
   else {
          set("unit","��");
          set("value",1000);
          set("base_unit","��");
          set("base_weight",1);
          set("base_value",1);
          set("material","steel");
          set("long","һ���˼����µ�С��ɵ�! \n");
          set("wield_msg","��֪��ʱ��$N������ͻȻ����һ��$n! \n");        
          set("unwield_msg","$N�ӻ����ͳ�һ��ľ����$n����ؿ���. \n");
        }
   set_amount(1);
   init_throwing(100);
   setup();
}

