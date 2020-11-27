// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// xuanyuan-sword.c ��ԯ���� 
// for only one object in mud 

#include <ansi.h> 
#include <weapon.h> 
inherit SWORD; 
inherit F_UNIQUE; 

void create() 
{ 
        set_name(HIR "��Ӱ" NOR, ({"chengying sword", "chengying", "sword"})); 
        set_weight(15000); 
        if (clonep()) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", sort_msg(HIR "Զ�ŵ�һ����������ɫ�ڰ׽��ʵ�һ˲�䣬һ˫�ֻ�������˫�ֺ���֮��"
                                     "��һ�ؽ�����ֻ�н������������������ǣ��ڱ����ǽ����ȴ����Ͷ��һ��Ʈ"
                                     "���Ľ�Ӱ����Ӱֻ��Ƭ�̣������Ű�������ٶ���ʧ��ֱ���ƻ裬��ɫ��������"
                                     "�ڰ���ͺ�ҹ��������ǣ��Ǹ�Ʈ���Ľ�Ӱ���ٴθ��ֳ����������˫�ֻ���һ"
                                     "�����ŵĻ��ߣ������Ա�һ��ͦ�εĹ��ɣ�������������ġ��ꡱ��һ��������΢"
                                     "΢һ�𣬲����仯��Ȼ���Ժ󲻾ã���ï���ɸǾ���һ���º��ӹ����Ϸ�������"
                                     "���£�ƽչ͹¶��ȦȦ���֣���ʾ�����µ����š���ɫ�����������ֹ������Σ�"
                                     "Զ�ŵ�ĺɫ������£�����֮��һƬ���¡������Ӱ���εĳ��������ڡ����ӡ�"
                                     "���ʡ�֮�б����Ӽ��͵������̳�����������ʱ�����˿������ص���������Ӱ��\n" NOR));
                                     
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "�ҵ��졭�㡭��֪������ɶô������Ҳ����������"); 
                set("unique", 1); 
                set("rigidity", 500); 
                set("replica_ob", "/clone/weapon/changjian");
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[��]��һ�����һ�ѳ�Ӱ���������ƣ�ɱ���Ľ���\n"NOR); 
                set("unwield_msg",HIR"$N�����еĳ�Ӱ�뽣�ʣ�������ɢ��ɱ�����ޡ�\n"NOR); 
        }
        init_sword(500); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing", me->query("str") * 2, me);
        victim->receive_wound("jing", me->query("str") * 2, me);
        return HIM "��Ӱ�д��Ŵ̶����ƿ�������һ�������磬��ʱ��$n"
               HIM "ֻ�е������ŵ���������ס��\n" NOR;
}

