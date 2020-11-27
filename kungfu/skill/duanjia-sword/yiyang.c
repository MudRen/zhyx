// Code of JHSH
// yiyang.c һ��ָ��ע������

#include <ansi.h>

inherit F_SSERVER;

private int remove_effect(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, damage;

        if (me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail("�����õ��ڹ��ķ����ԣ��޷�����һ��ָ��\n");

        if (me->query_temp("yiyang"))
                return notify_fail("������һ��ָָ�����������ˣ�\n");

        if (me->query_skill("force",1)<100
                || (me->query_skill("kurong-changong",1)<100 &&
                    me->query_skill("duanshi-xinfa",1)<100)
                || me->query_skill("duanjia-sword",1)<100
                || me->query_skill("sun-finger",1)<120)
                return notify_fail("��Ĺ����������޷�����һ��ָָ���������ϣ�\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type")!="sword")
                return notify_fail("��û��ʹ����ȷ���������޷���һ��ָ�������ϡ�\n");

        if (weapon->query_temp("yiyang"))
                return notify_fail("�������Ѿ�ע����һ��ָָ����\n");

        if (me->query("neili") <= 300)
                return notify_fail("�������������һ��ָ����\n");

        if (me->query("jingli") <= 100)
                return notify_fail("��ľ���������һ��ָ����\n");

        if (weapon->query("weapon_prop/damage")>=500)
                return notify_fail("�㷢�������������ľ����ޱȣ��ɶ��칦���޷���ע���������ϣ�\n");

        message("vision", HIY "\n"+me->query("name")+"����"+weapon->query("name")+"��������Ƭ�̡�\n\n" NOR, environment(me), me);
        tell_object(me, HIY "\n��������������һ��ָָ����ע��"+weapon->query("name")+"�ϡ�\n\n" NOR);

        skill = me->query_skill("force");

        me->set_temp("yiyang", 25+skill/10);

        skill = me->query_skill("sun-finger",1) + me->query_skill("kurong-changong",1);
	skill /= 3;
        weapon->set_temp("rig", weapon->query("weapon_prop/damage"));
        weapon->set_temp("yiyang", 1);

        if (weapon->query("weapon_prop/damage") < 100 )
		damage = 300 + skill;
        else if ( weapon->query("weapon_prop/damage") < 300 )
		damage = 200 + skill;
        else if ( weapon->query("weapon_prop/damage") < 500 )
		damage = 100 + skill;

        weapon->add("weapon_prop/damage", damage);
	me->add_temp("apply/damage", damage);
        call_out("checking", 1, me, weapon);
        me->add("neili", -200);
        me->add("jingli", -50);

        return 1;
}

void checking(object me, object weapon)
{
        if (!me) {
		if (!weapon) return;
                weapon->set("weapon_prop/damage", weapon->query_temp("rig"));
                weapon->delete_temp("yiyang");
                weapon->delete_temp("rig");
                return;
        }
        if (me->query_temp("yiyang")) {
	   if (!weapon)
	   {
               	remove_effect(me, weapon);
	        tell_object(me, HIY "\n���һ��ָָ�����˻�����\n\n" NOR);
                return;
	   }
           else if (environment(weapon)!= me || weapon!=me->query_temp("weapon")) {
               	remove_effect(me, weapon);
	        tell_object(me, HIY "\n���һ��ָָ����"+weapon->name()+"�����˻�����\n\n" NOR);
                return;
           }
           else if (weapon->query("weapon_prop") == 0) {
                remove_effect(me, weapon);
                tell_object(me, HIY "\n���"+weapon->name()+"�ѻ٣����ò��ջع�ע�����ϵ�һ��ָָ����\n\n" NOR);
                return;
           }
           else if (me->query_skill_mapped("force") != "kurong-changong" &&
                    me->query_skill_mapped("force") != "duanshi-xinfa") {
                remove_effect(me, weapon);
                tell_object(me, HIY "\n��е���Ϣ�������޷����ֹ�ע��"+weapon->name()+"�ϵ�һ��ָָ����\n\n" NOR);
                return;
           }

           me->add_temp("yiyang", -1);
           call_out("checking", 1, me, weapon);
        }
        else {
           remove_effect(me, weapon);
        tell_object(me, HIY "\n��е���Ϣ���ǣ����ò������˹�����"+weapon->name()+"���ջع�ע��һ��ָָ����\n\n" NOR);
        }
}       

private int remove_effect(object me, object weapon)
{
	if (weapon)
	{
		if (me->query_temp("weapon") &&
        	    me->query_temp("weapon") == weapon)
		    me->add_temp("apply/damage", -weapon->query("weapon_prop/damage") + weapon->query_temp("rig"));
	        weapon->set("weapon_prop/damage", weapon->query_temp("rig"));
        	weapon->delete_temp("yiyang");
	        weapon->delete_temp("rig");
	}
        me->delete_temp("yiyang");
        return 1;
}
