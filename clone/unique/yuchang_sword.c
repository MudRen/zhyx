// Copyright (C) 2003, by Xlz. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// yuchang-sword.c �㳦��
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create()  
{  
        set_name(HIY "�㳦��" NOR, ({"yuchang sword", "yuchang", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {  
        set("unit", "��");  
                        set("long", sort_msg(CYN "" 
                                     ""
                                     ""
                                     ""
                                     ""
                                     "\n" NOR)); 
        set("value", 100000);  
        set("material", "steel"); 
        set("no_sell", "�ҵ��졭�㡭��֪������ɶô������Ҳ����������");  
        set("unique", 1);  
        set("rigidity", 500);  
        set("replica_ob", "/clone/weapon/changjian"); 
        set("no_put",1);  
        set("no_steal",1);    
        set("wield_msg",CYN"$N[��]��һ�����һ����ԯ�����������ƣ�ɱ���Ľ���\n"NOR);  
        set("unwield_msg",CYN"$N�����е���ԯ������뽣�ʣ�������ɢ��ɱ�����ޡ�\n"NOR);  
     }
     init_sword(650); 
     setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing", me->query("str") * 2, me); 
        victim->receive_wound("jing", me->query("str") * 2, me); 
         return CYN "��ԯ����д��Ŵ̶����ƿ�������һ�������磬��ʱ��$n" 
               CYN "ֻ�е��������ҡ�\n" NOR; 
}
