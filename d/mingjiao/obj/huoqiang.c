// Code of JHSH
#include <ansi.h>
inherit ITEM;


void create()
{
        set_name("���Ͳ", ({ "huo qiang", "qiang", "gun" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ�����Ͳ����ɫ����͸�ϣ������ڽ�������
����������ɡ���߻�����һ�����䡣\n"
);
                set("unit", "��");
		set("bullet", 5);
        }

}

void init()
{
	add_action("do_load","load");
	add_action("do_aim","aim");
	add_action("do_fire","shoot");
}

int do_load()
{
	object me=this_player();

	if (me->query_skill_mapped("throwing") != "wuxing-jueji")
		return notify_fail("��û�м������о�����Ϊ����������ʹ�þ�������Ͳ��\n");

	if (me->query_skill("wuxing-jueji",1) < 120)
		return notify_fail("�����о���̫���˵㣬����ʹ�þ�������Ͳ��\n");

	if( me->is_busy() )
		return notify_fail("����æ���ء�\n");

	if (query_temp("loaded"))
		return notify_fail("ʯ���Ѿ�װ���ˡ�\n");

	if (query("bullet") <= 0)
		return notify_fail("ʯ���Ѿ��þ��ˡ�\n");

	message_vision("$N�����Ͳ������һЩʯ�͡�\n",me);
	set_temp("loaded",1);
	me->start_busy(3+random(3));
	
	return 1;
}

int do_aim(string target)
{
	object ob;
	object me=this_player();

	if (me->query_skill_mapped("throwing") != "wuxing-jueji")
		return notify_fail("��û�м������о�����Ϊ����������ʹ�þ�������Ͳ��\n");

	if (me->query_skill("wuxing-jueji",1) < 120)
		return notify_fail("�����о���̫���˵㣬����ʹ�þ�������Ͳ��\n");

	if( me->is_busy() )
		return notify_fail("����æ���ء�\n");

	if( !target)
		return notify_fail("������˭��\n");

	if(!objectp(ob = present(target, environment(me))))
		return notify_fail("����û������ˡ�\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܹ������ˡ�\n");

	if( !ob->is_character() || ob->is_corpse() )
		return notify_fail("�����һ�㣬�ǲ����ǻ��\n");

	if( !query_temp("loaded"))
		return notify_fail("�㻹ûװʯ���ء�\n");

	message_vision(HIW"$N�����Ͳ��׼��$n��\n"NOR,me,ob);

	set_temp("aimed",target);
	me->start_busy(3+random(3));
	
	return 1;
}

int do_fire()
{
	string target;
	object ob;
	object me=this_player();

	if (me->query_skill_mapped("throwing") != "wuxing-jueji")
		return notify_fail("��û�м������о�����Ϊ����������ʹ�þ�������Ͳ��\n");

	if (me->query_skill("wuxing-jueji",1) < 120)
		return notify_fail("�����о���̫���˵㣬����ʹ�þ�������Ͳ��\n");

	if( me->is_busy() )
		return notify_fail("����æ���ء�\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܹ������ˡ�\n");

	if (!(target=query_temp("aimed")) )
		return notify_fail("������׼���ٿ���\n");

	if (!objectp(ob = present(target,environment(me))))
		return notify_fail("���Ŀ���Ѿ��뿪�ˡ�\n");

	if( !ob->is_character() || ob->is_corpse() )
		return notify_fail("���Ŀ���Ѿ����ˡ�\n");

	message_vision(HIY"$N�ٺ�һ����Ц���۶����أ�һ��������$nֱ���ȥ��\n"NOR,me,ob);
	
	add("bullet",-1);
	remove_call_out("shoot_target");
	call_out("shoot_target",1,me,target);
	me->start_busy(5);

	return 1;
}

int shoot_target(object me, string target)
{
	object ob;
	string *limbs;
	int damage;

	if (!objectp(ob = present(target,environment(me))))
		return notify_fail("һ��Ũ�̹�ȥ������ʲôҲû���š�\n");

	if( !ob->is_character() || ob->is_corpse() )
		return notify_fail(target+"�Ѿ����ˡ�\n");

	if (me->query("combat_exp") < random(ob->query("combat_exp")*2) )
	{
		message_vision(HIY"$Nֻ��һ���������������æʹһ��Ұ¿������Ǳ���ֵĶ��˿�ȥ��\n"NOR,ob);
	}
	else
	{
		limbs=ob->query("limbs");
		message_vision(HIR"һ���ս�����ζ������ֻ��$N��"+
				limbs[random(sizeof(limbs))]+"�ѱ��������У�"+
				"��̼�Ƥ�����ã���ɽ�̿ģ����"+
				"$N��ʱ��������б�����\n"NOR,ob);
		damage=me->query("max_qi")+ob->query("max_qi");
		damage=random(damage/2);
		ob->receive_wound("qi",random(damage/2),me);
		ob->receive_damage("qi",damage,me);
	}

	ob->kill_ob(me);
	me->start_busy(random(5));
	
	delete_temp("aimed");
	delete_temp("loaded");

	return 1;
}