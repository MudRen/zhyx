// Code of JHSH	
// pozhen.c

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        object env,owner;
        string msg;

        env = environment(me);
        if (!env)
                return notify_fail("����ʲô�ط�Ҳ���ǣ�\n");
        if (!env->query("th_buzhen"))
                return notify_fail("���ﲢ�޲��������󷨡�\n");
        
	if( !objectp(owner = find_player(env->query("th_zhen_owner"))) ||
	    environment(owner) != env)
	{
	        env->set("long", env->query("org_desc"));
        	env->set("exits", env->query("org_exits"));
	        env->set("cost", env->query("org_cost"));
        	env->delete("org_desc");
	        env->delete("org_cost");
        	env->delete("org_exits");
	        env->delete("th_buzhen");
        	env->delete("th_pozhen");
		env->delete("th_zhen_owner");
	
        	tell_object(env, CYN"һ���������ڶ�������ɢ��ȥ�����澰����Ȼһ�䡣\n"NOR);
		return 1;
	}

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("�����õ��ڹ��롸�����󷨡��ķ���㣣�\n");

        if( me->query_skill("bibo-shengong", 1) < 80 )
                return notify_fail("����ڹ���Ϊ���δ������δ���������󷨡���\n");

        if( me->query("jingli") < me->query("max_jingli") * 80 / 100)
                return notify_fail("��ľ����������������ƽ⡸�����󷨡���\n");

        if( me->query("jing") < me->query("max_jing") * 80 / 100)
                return notify_fail("��ľ��������������ƽ⡸�����󷨡���\n");

        if( me->query_skill("qimen-wuxing", 1) < 80 )
                return notify_fail("�������������Ϊ��������δ���������󷨡���\n");

        me->set("jing", me->query("max_jing")/2);
        me->set("jingli", me->query("max_jingli")/2);

        if( me->query("id") != env->query("th_zhen_owner") && 
        me->query_skill("qimen-wuxing",1) < env->query("th_pozhen")*3/4) {
                message_vision(CYN"$N���ڵ���ڤ˼���룬ͻȻ��ɫ��䣬������Ѫ��\n"NOR,me);
                me->unconcious();
                return 1;
        }

        msg = HIW"$N��˼Ƭ�̣��󷨵��������˱仯��ȫ����Ȼ���أ�����һ����Ц������һ����\n";
        msg += "�������У�������������ʱ��ɳ��ʯ����һ�̣�����������������ɢ����Ӱ���٣�\n"NOR;
        message_vision(msg, me);
        
        env->set("long", env->query("org_desc"));
        env->set("exits", env->query("org_exits"));
        env->set("cost", env->query("org_cost"));
        env->delete("org_desc");
        env->delete("org_cost");
        env->delete("org_exits");
        env->delete("th_buzhen");
        env->delete("th_pozhen");
        env->delete("th_zhen_owner");

        return 1;
}