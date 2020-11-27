// hup.c ������Ԫ

#include <ansi.h>

#define HUP "��" HIR "������Ԫ" NOR "��"

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill,lv;
        string msg;
        mapping my;
        int rp;
        int neili_cost;

        if (userp(me) && ! me->query("can_perform/xiantian-gong/hup"))
                return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 200)
                return notify_fail("�����칦�����������ʩչ" HUP "��\n");

        if ((int)me->query("max_neili") < 1000) 
                return notify_fail("���������Ϊ���㣬����ʩչ" HUP "��\n");

        if ((int)me->query("neili") < 200) 
                return notify_fail("�����ڵ���������������ʩչ" HUP "��\n");

        my = me->query_entire_dbase();
        if ((rp = (my["max_qi"] - my["eff_qi"])) < 1)
                return (SKILL_D("force") + "/recover")->exert(me, target);

        if (rp >= my["max_qi"] / 10)
                rp = my["max_qi"] / 10;

        skill = me->query_skill("force");
        msg = HIW "$N" HIW "�����³�һ��������ʱ����ͨ������ɫ�����ı�"
              "��ƽ�͡�\n" NOR;
        message_combatd(msg, me);

        neili_cost = rp + 100;
        if (neili_cost > my["neili"])
        {
                neili_cost = my["neili"];
                rp = neili_cost - 100;
        }
        me->receive_curing("qi", rp);
        me->receive_healing("qi", rp * 3 / 2);
        me->add("neili", -neili_cost);

        me->start_busy(3);

	if ( (lv = me->query_skill("xiantian-gong", 1)) >= 180 &&
        me->query_skill("taoism", 1) > 399 && 
        me->query("family/family_name") == "ȫ���")
        {
                if ((int)me->query_skill("dodge",1) > (int)me->query_skill("force",1) &&
		(int)me->query_skill("parry",1) > (int)me->query_skill("force",1)) 
	        {
		if (me->can_improve_skill("force"))
			me->improve_skill("force", lv * 10);
 	        else
	
		me->improve_skill("force", 0);
	        }
	        }
	        

		if (me->query_skill("xiantian-gong", 1) >= 180 && 
                me->query_skill("taoism", 1) > 399 &&
                me->query("family/family_name") == "ȫ���")
        {
                if ((int)me->query_skill("dodge",1) > (int)me->query_skill("force",1) &&
		(int)me->query_skill("parry",1) > (int)me->query_skill("force",1)) 
	        {
		if (me->can_improve_skill("xiantian-gong"))
			me->improve_skill("xiantian-gong", lv * 10);
 	        else
	
		me->improve_skill("force", 0);
	        }
        }

        return 1;
}
