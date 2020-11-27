// heal.c

#include <ansi.h>

mapping eff_heal = ([
	"kurong-changong"	: 5,	
	"taixuan-gong"		: 5,
	"taiji-shengong"	: 4,	
	"yijinjing"		: 4,	
	"jiuyang-shengong"	: 4,	
	"xiantian-gong"		: 4,	
	"linji-zhuang"		: 4,	
	"bahuang-gong"		: 3,
	"lengyue-shengong"	: 3,
	"shonghuo-xuanming"	: 3,
	"hunyuan-yiqi"		: 3,	
	"zixia-shengong"	: 3,
	"bibao-shengong"	: 3,
	"yunv-xinfa"		: 3,
	"xiaowuxiang"		: 3,
	"huntian-qigong"	: 3,	
	"longxiang"		: 3,
	"beiming-shengong"	: 3,	
	"zihui-xinfa"		: 3,	
	"hamagong"		: 2,	
	"huagong-dafa"		: 2,	
	"shenlong-xinfa"	: 2,
	"xixing-dafa"		: 2,	
]);

int curing(object);
int halt_curing(object);
void remove_pending(object);

int exert(object me, object target)
{
        string force;

	if (me->is_fighting())
		return notify_fail("ս�����˹����ˣ�������\n");

	if (me->is_busy())
		return notify_fail("����æ������ͷ��������˵��\n");

        force = me->query_skill_mapped("force");
        if (! stringp(force))
                return notify_fail("�ȼ�����������ڹ���\n");

        if ((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("��������Ѫ��ӯ������Ҫ���ˡ�\n");

	if ((int)me->query_skill(force, 1) < 20)
		return notify_fail("���" + to_chinese(force) + "��Ϊ��������\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�������������\n");

	if ((int)me->query("eff_qi") < (int)me->query("max_qi") / 5)
		return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

	message_vision(HIW "$N" HIW "ȫ����ɣ���������ʼ�˹����ˡ�\n"
                       HIY "$N" HIY "�³�һ����Ѫ����ɫ�������ö��ˡ�\n" NOR,
		       me);

	me->set_temp("apply/short", ({ me->name() +"�����ڵ����˹����ˡ�"}));

	me->set_temp("pending/curing", 1);
	me->start_busy((: curing :), (: halt_curing :));
	me->set("jiali", 0);

	return 1;
}

int curing(object me)
{
        int recover_points, lvl, con, eff;
	string force_skill;
	mapping msg;
        
	if( !living(me) || me->is_ghost() || !(force_skill = me->query_skill_mapped("force")) )
	{
		remove_pending(me);
		return 0;
	}

	if( me->query("jing") < 1 || me->query("jingli") < 1 )
	{
		remove_pending(me);
		me->unconcious();
		return 0;
	}
	else if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
	{
		tell_object(me, HIY"���˹����ã��Ծ�����˳�������˾�ȥ����Ԫ�����վ��������\n"NOR);

		message("vision", me->name() +"�˹���ϣ�վ������������ȥ��ɫ�����������ӡ�\n"NOR,	environment(me), me);

		remove_pending(me);
        	return 0;
	}
	else if( (int)me->query("neili") < 50 )
	{
		tell_object(me, "�������˹����ˣ�������Ϣ��̷���������ݻ����ˣ�վ��������\n"NOR);
		message("vision", me->name() +"�˹���ϣ�����վ����������ɫ������������ࡣ\n"NOR,environment(me), me);

		remove_pending(me);
		return 0;
	}

	lvl = me->query_skill("force");	// my enable force level.
	con = me->query("con");		// my original constitution.
	eff = eff_heal[force];		// my force's effect on heal.
	if( !eff ) eff = 1;

	recover_points = con + lvl/5;
	recover_points += recover_points/5*eff;

        if (me->query("breakup"))
                recover_points *= 3;

	me->receive_curing("qi", recover_points);
	me->add("neili", -50);
	return 1; 
}

int halt_curing(object me)
{
	if (me->query("qi") > 50)
		me->receive_damage("qi",50);
	else
		me->set("qi",1);

	if (me->query("neili") > 50)
		me->add("neili", -50);
	else
		me->set("neili",0);

	tell_object(me, "��������Ϣ��Ӳ�����ؽ���Ϣѹ����ȥ������վ��������\n");
	message("vision", me->name() +"����һ���³�һ����Ѫ������վ��������\n", environment(me), me);

       	remove_pending(me); 
	me->start_busy(1+random(3));
	return 1;
}

void remove_pending(object me)
{
	me->delete_temp("pending/curing");
	me->delete_temp("apply/short");
}