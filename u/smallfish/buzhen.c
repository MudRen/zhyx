// Code of ShenZhou
// buzhen.c

#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

int exert(object me, object target)
{
        object *ob, env;
        string msg, desc;
        int i, qmwx, k = 0;
        mapping exit;

        if (me->is_busy()
        || me->query_temp("pending/exercising")
        || me->query_temp("exit_blocked"))
                return notify_fail("��������æ���ء�\n");

        env = environment(me);
        exit = env->query("exits");

        if( !env )
                return notify_fail("����ʲô�ط�Ҳ���ǣ�\n");

        if( !env->query("outdoors") )
                return notify_fail("���ڿռ�̫С����ʩչ������\n");

        if (env->query("th_buzhen"))
                return notify_fail("�����Ѳ��������󷨡�\n");

        if( me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("�����õ��ڹ��롸�����󷨡��ķ���㣣�\n");

        if( me->query_skill("bibo-shengong", 1) < 80 )
                return notify_fail("����ڹ���Ϊ���δ������δ���������󷨡���\n");

        if( me->query("jingli") < me->query("max_jingli"))
		return notify_fail("��ľ���������������ʩչ�������󷨡���\n");

        if( me->query("jing") < me->query("max_jing"))
                return notify_fail("��ľ�������������ʩչ�������󷨡���\n");
        
	if( me->query_skill("qimen-wuxing", 1) < 80 )
                return notify_fail("�������������Ϊ��������δ���������󷨡���\n");

        me->set("jing", me->query("max_jing")/2);
        me->set("jingli", me->query("max_jingli")/2);

        msg = HIG"$N����Ʈ�裬���۷����ʱ�̳�����ɰʯ�ҷɣ�����ɷʱ���ˣ�\n";
        msg += GRN"��һ�̣�$N�������Σ����ֶ�����������Ӽž�������͸��һ����ɱ֮����\n"NOR;

        desc = env->query("long")+HIB"���¾����ǳ����죬��ɫ���������ڿ����У�͸��ɭɭ������\n"NOR;

        env->set("org_desc", env->query("long"));
        env->set("org_exits", env->query("exits"));
        env->set("org_cost", env->query("cost"));

        qmwx = (int)me->query_skill("qimen-wuxing",1);

        env->set("long", desc);
        env->set("th_buzhen", 1);
	env->set("th_zhen_owner",me->query("id"));
        env->set("th_pozhen", qmwx*2);

        if( qmwx < 120 ) {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env), 
                        "west" : file_name(env),
                        "north" : file_name(env),
                ]));
        } else if ( qmwx < 150 ) {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env),
                        "west" : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                ]));
        } else if ( qmwx < 180 ) {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env),
                        "west" : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                        "enter" : file_name(env),
                        "out" : file_name(env),
			"up" : file_name(env),
			"down" : file_name(env),
                ]));
        } else {
                env->set("exits", ([
                        "east" : file_name(env),
                        "south" : file_name(env),
                        "west" : file_name(env),
                        "north" : file_name(env),
                        "northwest" : file_name(env),
                        "northeast" : file_name(env),
                        "southeast" : file_name(env),
                        "southwest" : file_name(env),
                        "enter" : file_name(env),
                        "out" : file_name(env),
			"up" : file_name(env),
			"down" : file_name(env),
                        "eastup" : file_name(env),
                        "southup" : file_name(env),
                        "westup" : file_name(env),
                        "northup" : file_name(env),
                        "eastdown" : file_name(env),
                        "southdown" : file_name(env),
                        "westdown" : file_name(env),
                        "northdown" : file_name(env),
                ]));
        }

        call_out("remove_effect", qmwx/2, env);

        message_vision(msg, me);

        return 1;
}

void remove_effect(object env)
{
        if (!env) return;
        if (!env->query("th_buzhen")) return;

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
}
