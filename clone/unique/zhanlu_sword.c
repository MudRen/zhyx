// Copyright (C) 2003, by Xlz. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// zhanlu-sword.c տ
// for only one object in mud  

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create()  
{ 
        set_name(HIW "տ��" NOR, ({"zhanlu sword", "zhanlu", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {
                set("unit", "��");  
                set("long", sort_msg(HIW"տ����һ�ѽ�������һֻ�۾���տ��տտȻ����ɫҲ" 
                                     "�����ͨ���ɫ��Ȼ�޼��ĳ����˸е��Ĳ������ķ�������"
                                     "�����Ŀ��ʹ��顣�������ϲ�һֻĿ�����䡢������ĺ�" 
                                     "ɫ���۾���ע���ž���������һ��һ�������е������ڲ�" 
                                     "�������������޵��������������ưܡ����֮Ӣ��̫��֮��" 
                                     "����֮���񣬷�֮������ŷұ�����ɴ˽�ʱ��������������" 
                                     "����Ϊ������Բ���Լ����������룺����һ���޼�ݶ��ֲ�" 
                                     "��˿��ɱ���ı�������ν�����޵У�տ����һ���ʵ�֮����\n" NOR)); 
                set("value", 100000);  
                set("material", "steel"); 
                set("no_sell", "�ҵ��졭�㡭��֪������ɶô������Ҳ����������");  
                set("unique", 1);  
                set("rigidity", 500);  
                set("replica_ob", "/clone/weapon/changjian"); 
                set("no_put",1);  
                set("no_steal",1);
                set("wield_msg",HIW"$N[��]��һ�����һ��տ��û��˿��ɱ����\n"NOR);  
                set("unwield_msg",HIW"$N�����е�տ����뽣�ʣ�����û�з���һ˿������\n"NOR); 
        }
        init_sword(950); 
        setup(); 
}
mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing", me->query("str") * 2, me); 
        victim->receive_wound("jing", me->query("str") * 2, me); 
        return HIW "տ���$N���з�����գ�[��]һ����տ�����ջ�������ص���$N���У�$n" 
               HIW "ֻ�е����ȡ�\n" NOR; 
}
