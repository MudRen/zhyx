//update by xiner
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( HIG"������"NOR, ({ "donghuang zhong","zhong" }) );
	set_weight(1500);
	if( clonep() )
	set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIW"һ����ͭ���ӣ��ഫΪ����̫һ�ı��������Ͽ��������Ϲ����֣�ɢ���Ż�ɫ�ĺ��⡣���м�ǿ�ķ���������\n" NOR);
		set("value",10);
		set("material", "tian jing");
		set("armor_prop/armor", 500 + random(100));
		set("armor_prop/dodge", 200 + random(100));
                set("armor_prop/parry", 200 + random(100));
		set("warm_cloth", 1);
		set("no_sell", 1 );
		set("no_steal", 1 );
	}
	setup();
}

int query_autoload()
{
	return 1;
}

owner_is_killed()
{
	if (random(30)!=1)
	{
		message_vision(HIG"�������飬�������������ȥ��Ѱ��������ע�������ˡ�\n" NOR,this_player());
    destruct(this_object()); 
    return 1;
  }
  
  message_vision(HIG"��ϲ��!����Եõ��Ϲ���������ӡ�\n" NOR,this_player());
  
	
}



 mixed valid_damage(object ob, object me, int damage, object weapon) 
     { 
             mapping result; 
             int ap, dp; 
             int cost,level,backdamage; 
      
                     level=(int)me->query_skill("martial-cognize", 1); 
                     if (level<100) backdamage=0; 
                     else if (level<299) backdamage=(int)damage/20 ; 
                     else if (level<499) backdamage=(int)damage/15 ; 
                       else backdamage=damage; 
     
             if ((int)me->query("neili") < 500)  
                     return; 
     
             cost = damage / 2; 
            if (cost > 1000) cost = 1000; 
      
             
             
             ap = ob->query_skill("force",1);
             dp = me->query_skill("force",1);

     
          if (ap * 2 / 5 + random(ap) < dp) 
             { 
                             if (random(4) == 1 ) 
                             { 
                     me->add("neili", -cost);                                 
                                     result = ([ "damage": -damage ]);        
                                     ob->receive_wound("qi", backdamage, me); 
                     
                             result += (["msg" : HIY "$n" HIY "Ĭ�����������黤������������$N" + HIY "��һ�У����$N��$n���������𣬡��ۡ���һ���³�һ����Ѫ��\n"NOR]);                         
                     return result; 
                             } 
                         else 
                             { 
                                     me->add("neili", -cost); 
                     result = ([ "damage": -damage ]);                
                             result += (["msg" : HIY "���������ӷ��������⣬��$n���Ż�ס,�������µĽ�����$N��һ�У�ȴû���ܵ�" 
                                                 "����˺���\n" NOR]);                        
                     return result; 
                             } 
      
             } 
     } 
      
