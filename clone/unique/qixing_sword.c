// Copyright (C) 2003, by Lonely. All rights reserved. 
// This software can not be used, copied, or modified  
// in any form without the written permission from authors. 
// qixing-sword.c ������Ԩ
// for only one object in mud

#include <ansi.h>  
#include <weapon.h>  
inherit SWORD;  
inherit F_UNIQUE;  

void create() 
{
        set_name(HIC "������Ԩ" NOR, ({"qixing longyuan", "longyuan", "sword"}));  
        set_weight(15000);  
        if (clonep())  
                set_default_object(__FILE__);  
        else {  
                set("unit", "��");  
                set("long", sort_msg(HIC "��ѽ���˵����ŷұ�Ӻ͸ɽ�����ʦ����������ŷұ��"
                                     "�͸ɽ�Ϊ���˽����俪��ɽ���ų�ɽ��Ϫˮ����������¯�Գ�" 
                                     "�������ǻ��е��߸����У����������ǡ�������֮�󣬸��ӽ�" 
                                     "����ͬ�Ǹ�ɽ��������Ԩ��Ʈ�������·��о������ԡ���" 
                                     "������Ԩ�����˽�����ļ��չ�Ȼ��տ��������������������" 
                                     "��֪������ʵ��������ͨ���̣������ˡ���˵��������鳼��" 
                                     "�����������ģ�����������һ·׷�ϣ���һ��Ĳ���·���ӵ�" 
                                     "����֮����ֻ���Ƶ���ˮ���������ꡣǰ���ˮ������׷����" 
                                     "���ڽ������֮ʱ�������㷢��������һ��С������ʻ������" 
                                     "���������������ϴ����������ϴ���С��Ѹ������«������" 
                                     "��������Ӱ������׷���㬶�ȥ�����̽��������ص����ߣ�Ϊ" 
                                     "������ȡ����ʳ����һ�٣�������ǧ����л����������������" 
                                     "��Ц���Լ��˼����Σ��������ã�ֻ�ƣ��������ˡ����ɣ���" 
                                     "�����л���У����˼��������й�����ת���ۻأ����������" 
                                     "�洫�����ı�����������Ԩ�������˼�ֵǧ��ı�����������" 
                                     "������л��������������ǧ��Ҫй¶�Լ������٣������˽�" 
                                     "��������Ԩ���������쳤̾����������˵���������ֻ��Ϊ��" 
                                     "�ǹ�������������ͼ������������Ȼ����̰�����ţ���ֻ��" 
                                     "�Դ˽�ʾ�߽ࡣ˵�꣬�ὣ���ء������㱯��Ī�������¼���" 
                                     "����Խ�����������Ԩ��һ�ѳ��Ÿ߽�֮����\n" NOR));
                set("value", 100000);  
                set("material", "steel"); 
                set("no_sell", "�ҵ��졭�㡭��֪������ɶô������Ҳ����������");  
                set("unique", 1);  
                set("rigidity", 500);  
                set("replica_ob", "/clone/weapon/changjian"); 
                set("no_put",1);  
                set("no_steal",1); 
                set("wield_msg",HIC"$N[��]��һ�����һ��������Ԩ��\n"NOR);  
                set("unwield_msg",HIC"$N�����е�������Ԩ���뽣�ʡ�\n"NOR);  
                } 
                init_sword(800);  
                setup(); 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        victim->receive_damage("jing", me->query("str") * 2, me); 
        victim->receive_wound("jing", me->query("str") * 2, me); 
        return HIC "������Ԩ����ͻȻð��һ�ɴ�ˮ������$n" 
               HIC "��$nֻ��Ӳ��ͷƤ�ֵ���\n" NOR; 
} 
