// Updated by Lonely
// buddhism.c

#include <ansi.h>

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
        int lvl;
        
        lvl = (int)me->query_skill("buddhism", 1);

        if (me->query("class") == "bonze" && (int)me->query("guilty") > 0)
                return notify_fail("���ŷ�ɮ�����䣬����֮��̫�أ��޷����������ķ���\n");
                
        if ((me->query("class") != "bonze" && me->query("family/family_name") != "���ϻ���")
        &&  lvl > 39) 
                return notify_fail("��δ����ţ���Ե���ϣ�û���徻��Ϊ�������ģ��޷������޳��������\n");

        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("�����ķ�ֻ�ܿ�ѧ(learn)����ߡ�\n");
}

void skill_improved(object me)
{
        if ((int)me->query_skill("buddhism", 1) == 120 && ! me->query("sl/int"))
        {
                me->add("int", 1);
                me->set("sl/int", 1);
                tell_object(me, HIM "\n��������ķ�ѧ�����ɣ���������������\n" NOR);
        }
}

