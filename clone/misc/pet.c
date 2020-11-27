#include <ansi.h>
#include <combat.h>
inherit NPC;
void create()
{
	set_name("����", ({ "pet" }) );
	set("race", "Ұ��");
	set("age", 3);
	set("str",5);
	set("cor",5);
	set("int",5);
	set("spi",0);
	set("cps",5);
	set("per",5);
	set("con",5);
	set("dex",5);
	set("dur",5);
	set("fle",5);
	set("tol",5);
	set("long", "һֻСССС���\n");
	set("owner","R");
	set("limbs", ({ "ͷ��", "����", "ǰ��", "�ᱳ", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );
        set("obedience",2);
	set("combat_exp",100);
	set("deathstamp",1);
        setup();
}
string query_save_file()
{
        string id;

        id = query("owner");
        if( !stringp(id) ) return 0;
        return sprintf(DATA_DIR "user/%c/%s/%s", id[0],id, id+".pet");
}

int save()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file+ __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

int restore()
{
        string file;

        if( stringp(file = this_object()->query_save_file()) )
                return restore_object(file);
        return 0;
}

void die()
{	
        int i;
        object owner, *enemy;
	 int jing,qi,exp;
	 set("deathstamp",time());
	 exp = (int) query("combat_exp");
	 jing = (int) query("max_jing");
        qi = (int) query("max_qi");
	 if(!environment()->query("no_death_penalty"))
        set("combat_exp",exp/10 * 9);
 	 set("eff_qi",qi);
 	 set("eff_jing",jing);
        set("qi",qi);
        set("jing",jing);
        if(objectp(owner=query("possessed")))
        {
                enemy = query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        owner->kill_ob(enemy[i]);
                        enemy[i]->kill_ob(owner);
                }
        }

        }

	save();	
	::die();
}

int heal_up()
{
        if(!objectp(this_object()->query("possessed")))
	{
	save();
	message_vision("$Nһ���Ͳ����ˡ�\n",this_object());
        destruct(this_object());
	return 1;
	}
	set_heart_beat(1);
        return ::heal_up() ;
}

void init()
{
	if(this_player() == query("possessed"))
	{
	add_action("do_order","order");
	add_action("do_modify","modify");
	add_action("do_gongji","gongji");
	add_action("do_teach","teach");
	add_action("do_shape","shape");
	}

}
int do_order(string arg)
{
	int obedience;
	object me = this_player();
        if (!arg) return notify_fail("��Ҫ�����ʲô��\n");
        if (me->query("jing") < 50) return notify_fail("��ľ���̫�����ָ�ӳ��\n");
	me->add("jing",-10);
	obedience = query("obedience");
	if(random(100) < obedience )
/*
	command( "emote " + arg);
*/
        command(this_object()->process_input(arg));
	else
	command("emote �ܲ���Ը�غ���һ����");
	return 1;
}
int do_modify(string arg)
{
	string item, msg;
        object me = this_player();
	if(!arg || sscanf(arg,"%s %s",item,msg) != 2)
	return notify_fail("SYNTAX: modify ���� ����\n");
	if(item == "flee")
	{
		set("env/wimpy", atoi(msg));
                write("�ϣ�\n");
		save();
		return 1;
	}

		
                if(CHINESE_D->check_control(msg))
                return notify_fail("���������п��Ʒ���\n");
                if(CHINESE_D->check_space(msg))
                return notify_fail("�������費���ո�\n");
                if(CHINESE_D->check_return(msg))
                return notify_fail("�������費���س�����\n");
        msg = replace_string(msg, "$BLK$", BLK);
        msg = replace_string(msg, "$RED$", RED);
        msg = replace_string(msg, "$GRN$", GRN);
        msg = replace_string(msg, "$YEL$", YEL);
        msg = replace_string(msg, "$BLU$", BLU);
        msg = replace_string(msg, "$MAG$", MAG);
        msg = replace_string(msg, "$CYN$", CYN);
        msg = replace_string(msg, "$WHT$", WHT);
        msg = replace_string(msg, "$HIR$", HIR);
        msg = replace_string(msg, "$HIG$", HIG);
        msg = replace_string(msg, "$HIY$", HIY);
        msg = replace_string(msg, "$HIB$", HIB);
        msg = replace_string(msg, "$HIM$", HIM);
        msg = replace_string(msg, "$HIC$", HIC);
        msg = replace_string(msg, "$HIW$", HIW);
        msg = replace_string(msg, "$NOR$", NOR);
        msg = replace_string(msg, "$S$", BLINK);
	switch(item)
	{
	case "desc":
		if(CHINESE_D->check_length(msg) > 100)
		return notify_fail("����̫����\n"); 
		set("long",msg+ NOR"\n");
		write("�ϣ�\n");
		save();
		return 1;
	case "nickname" :
		if(CHINESE_D->check_length(msg) > 20)
                return notify_fail("����̫����\n");
		set("nickname",msg+NOR);
		write("�ϣ�\n");
		save();
                return 1;
	case "title" :
                if(CHINESE_D->check_length(msg) > 20)
                return notify_fail("����̫����\n");
                set("title",msg+NOR);
                write("�ϣ�\n");
		save();
                return 1;
	case "arrive_msg" :
                if(CHINESE_D->check_length(msg) > 60)
                return notify_fail("����̫����\n");
                set("arrive_msg",msg+NOR);
                write("�ϣ�\n");
		save();
                return 1;
        case "leave_msg" :
                if(CHINESE_D->check_length(msg) > 60)
                return notify_fail("����̫����\n");
                set("leave_msg",msg+NOR);
                write("�ϣ�\n");
		save();
                return 1;

	}
	return notify_fail("��Ҫ�޸�ʲô��\n");

}
int do_gongji(string arg)
{
	object me,obj;
	me = this_player();
        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ׼ս����\n");

        if( !arg )
                return notify_fail("����ɱ˭��\n");

        if(!objectp(obj = present(arg, environment(me))))
                return notify_fail("����û������ˡ�\n");

        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("�����һ�㣬�ǲ����ǻ��\n");
	message_vision(
	sprintf("$N��$nһָ����%s����������ϣ���\n",this_object()->name()),me,obj);
       if (me->query("jing") < 20) return notify_fail("��ľ�����������ʡ�������ɣ�\n");
       me->add("jing",-20);
	if (query("jing") < 10) return notify_fail("��ĳ����Ѿ��۵Ĳ����ˣ��㻹������ЪϢһ��ɣ�\n");
       add("jing",-10);
       if(random(100) > query("obedience") )
       command("emote �ܲ���Ը�غ���һ����");
	else
	kill_ob(obj);
	return 1;
	
}

int do_teach(string arg)
{
	object me;
	int gin_cost,amount;
        int myskill, itskill;
	me = this_player();
	if(!myskill = me->query_skill(arg,1))
	return notify_fail("���������󻹲����أ�\n");
	if(arg != "unarmed" && arg != "move" && arg != "dodge")
	return notify_fail("��ѧ��������ܵģ�\n");
	itskill = query_skill(arg,1);
	if(myskill <= itskill)
	return notify_fail(name()+"�Գ�Ц��Ŀ�������㡣\n");
	if((int)me->query("potential")-(int)me->query("learned_points") < 1)
	return notify_fail("���Ǳ�ܲ�����\n");
	gin_cost = 100/ (int) query_int();
	if((int)me->query("jing") < gin_cost)
	return notify_fail("����Ȼ̫����û�а취�̣�\n");
	me->receive_damage("jing",gin_cost);
	me->add("potential",-1);
	amount = (int)me->query_int() * (int) query_int();
	message_vision(sprintf("$N�����䷳�ؽ�$n��%s����\n",to_chinese(arg)),me,this_object());
        if(random(100) > query("obedience") )
        command("emote �ܲ���Ը�غ���һ����");
	else 
	{
        improve_skill(arg,amount);
	message_vision(sprintf("$N�ƺ����ѧ����һЩ��%s����\n",to_chinese(arg)),this_object());
	}
	return 1;

}
string status_color(int current, int max)
{
        int percent;

        if( max>0 ) percent = current * 100 / max;
        else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}
int do_shape(string arg)
{	mapping my;
	string shape;
	int at_pt,pa_pt,do_pt;
	my = query_entire_dbase();
	printf("����%s%3d/ %3d %s(%3d%%)"NOR"  ����%s%3d/ %3d %s(%3d%%)\n"+NOR,
                status_color(my["jing"], my["eff_jing"]), my["jing"],my["eff_jing"],
                status_color(my["eff_jing"], my["max_jing"]),     my["eff_jing"] * 100 / my["max_jing"],
                status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
                status_color(my["eff_qi"], my["max_qi"]),     my["eff_qi"] * 100 / my["max_qi"]
	);		
	printf("���ˣ� %s\n",my["owner"]);
	printf("���飺 %d\t\tɱ���� %d\n",
	my["combat_exp"],my["bellicosity"]
	);
        printf("�ǻۣ� %d\t\t���ʣ� %d\n",
        query_int(), query_con()
        );
        printf("��̬�� %d\t\t������ %d\n",
        query_per(), query_str()
        );
        printf("�ٶȣ� %d\n",
        query_dex()
        );
        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
        printf("�������� %d\t\t\t\t�������� %d\n\n",
        at_pt+1, pa_pt/2+do_pt/2+1
        );
	return 1;
}
void unconcious()
{
die();
}

int accept_object(object me, object ob)
{
	if (me->query("id") == this_object()->query("owner")) return 1;
	return 0;
}
