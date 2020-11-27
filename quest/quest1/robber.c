// ���ڣΣУ�
// Updated by Lonely

inherit CLASS_D("generate") + "/chinese";
#include <ansi.h>
#define DIAM_DIR         "/d/item/obj/"

int do_nod(string arg);

void create()
{
        mapping my;
        int lvl;

        ::create();
        set("gender", "����" );
        set("nickname", "�ٷ�");
        set("age", 30 + random(30));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("scale", 150);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 50);
        set_temp("born_time", time());

        lvl = lvl = 2 + random(2);
        NPC_D->init_npc_skill(this_object(), lvl);

        // ��ʼ��NPC������
        my = query_entire_dbase();
        my["max_qi"] = 1000 + lvl * 300 + random(500);
        my["max_jing"] = my["max_qi"] / 2;
        my["max_neili"] = 1000 + lvl * 500 + random(500);
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["neili"] = my["max_neili"] * 2;
}


void check_room()
{
    object me = this_object();
    object env = environment(me);
    
    if (! living(me)) return;
    if (env && (env->query("no_quest") ||
                env->query("no_fight")  ||
                function_exists( "valid_leave", env)))

        "/cmds/std/go.c"->do_back(me);
}

void init()
{
        object ob,env;
        object killer = this_object();        
        string area;
        
        add_action("do_nod", "nod"); 
        add_action("do_nod", "�õ�"); 
        if (! killer->query("area") && ! killer->query("found"))
        {
                env = environment(killer);
                if (objectp(env) && sscanf(file_name(env), "/d/%s/", area) == 1)
                        killer->set("area", area);
        }
        ob = this_player();
        if (! this_object()->query("want_kill"))
                return;
        if (ob->query("id") == query("want_kill"))
        {
                delete("area");
                set("found", 1);
        }


        if (ob->query("id") == query("want_kill"))
        if (! is_fighting()) 
        {
          	remove_call_out("check_me");
          	call_out("check_me", 0);
        }

        if (this_object()->query("want_kill") != ob->query("id"))
        {
                add_action("do_kill", "team kill");
                add_action("do_kill", "touxi");   
                add_action("do_kill", "kill");
                add_action("do_kill", "hit");
                add_action("do_kill", "fight");
                add_action("do_kill", "steal");
                add_action("do_kill", "beg");
                add_action("do_kill", "persuade");
        }

}

void kill_ob(object me)
{
        object ob = this_object();

        if (! ob->query_temp("lonely/waiting"))
                return ::kill_ob(me);
        else
        {
                return;
        }
}

string *SM_LIST = ({ "donghais", "qingjins", "qinghaiy", "meihuay", "shoushans",
                     "gaos", "mubians", "dushany", "kongques", "moy", "huangdis", "lvsongs",
		     "kunluny", "zdhongs", "yangzhiy", "ganlans", "hujings" });

// ��������˻�¸
int do_nod(string arg)
{
        object me = this_player();
        object ob = this_object(), obj;
        int amount;

        if (! me->query_temp("lonely/waiting") || ! arg || arg != ob->query("id"))
                return 0;

        else {
                me->command("nod");
                if (intp(me->query_temp("lonely/waiting")))
                {
                        if (me->query_temp("lonely/diamond"))
                        {
                                message_vision(HIW "ֻ��$N" HIW "��Ц����������������ʶʱ����Ϊ���ܣ�" +
                                        RANK_D->query_respect(me) + "��Ȼ�������ˣ��ٺ٣�������С��ʯ" +
                                        "�͹����ˣ���������\n\n" NOR,
                                        ob, me);
                                obj = new(DIAM_DIR + SM_LIST[random(sizeof(SM_LIST))]);
                                
                                tell_object(me, HIR + ob->name() + "�ݸ�����" + obj->name() +
                                                HIR "�Ժ��³�һ����Ѫ���ﳤ��ȥ��\n" NOR);
                                obj->move(me, 1);
                                me->delete_temp("lonely");
                                remove_call_out("escape_me");
                                remove_call_out("check_me");
                                destruct(ob);
                                return 1;
                        }       
                        amount = me->query_temp("lonely/waiting");

                        message_vision(HIW "ֻ��$N" HIW "��Ц����������������ʶʱ����Ϊ���ܣ�" +
                                RANK_D->query_respect(me) + "��Ȼ�������ˣ��ٺ٣�������" +
                                chinese_number(amount) + "�������͹����ˣ���������\n\n" NOR,
                                ob, me);
                        // ��Ϊ�ǡ�����Ϊ��λ������Ҫ * 100��
                        MONEY_D->pay_player(me, amount * 100);
                        tell_object(me, HIR + ob->name() + "�ݸ�����" + chinese_number(amount) +
                                        "�������Ժ��³�һ����Ѫ���ﳤ��ȥ��\n" NOR );
                        me->delete_temp("lonely");
                        remove_call_out("escape_me");
                        remove_call_out("check_me");
                        destruct(ob);
                        return 1;
                }
                else return  0;
        }
}

int check_me()
{
       	object ob, me = this_object();

       	if (objectp(ob = present(query("want_kill"), environment(me)))
       	&&  ! environment(me)->query("no_fight")
       	&&  interactive(ob) && ! ob->is_fighting(me))
         	call_out("do_fkill",0,ob);

       	if (! present(query("want_kill"), environment(me)))   
       	{
          	remove_call_out("escape_me");
          	destruct(me);
       	}
        remove_call_out("check_me");
        call_out("check_me", 2);   

     	return 1;
}

int do_fkill(object ob)
{
        if (ob->query("id") == query("want_kill") && ! query_temp("lonely/waiting"))
        {
            if (living(this_object()))
       		message_sort(HIR "$N��ȵ�������ɽ���ҿ������������ԣ�" +
			ob->query("name") + "ʶ��Ļ����ͰѺ������������\n" NOR,
			this_object());  

        	this_object()->kill_ob(ob);
                ob->kill_ob(this_object());        
        }
     	return 1;
}

void start_escape(object ob,object me)
{
        call_out("escape_me", 300, ob, me);
}

int do_kill(string arg)
{
        string what, who;
        
        if (! arg) return 0;
        if (this_object()->id(arg))
        {
                write("������ʿ����������Ϊ�\n");
                return 1;
        }
        else
        if (sscanf(arg, "%s from %s", what, who) == 2 && this_object()->id(who))
        {
                write("���ǵ���ȥʩչ��ı��°ɡ�\n");
                return 1;
        }
        return 0;
}


void escape_me(object ob,object me)
{
        message_vision(
		"$N��Ц�˼���������������ã�" + RANK_D->query_self_rude(ob) +
		"�ͷŹ��㣬���������ˡ���˵�գ�һ�������սȦ����֪ȥ��\n", ob);

        destruct(ob);
}

void unconcious()
{
        object me, ob = this_object();
        int amount = 300 + random(300);
        string *condition = ({
                "������������Ҫ��֧", "ͷ�ؽ��ᣬ���Ͼ͵�", 
                "ŻѪ��������ð����", "�˺����ۣ������м�", 
        });

        if (objectp(me = query_last_damage_from()) 
        &&  environment() == environment(me) 
        &&  ! me->query_temp("lonely/waiting"))
        {
                switch (random(15)) 
                {
                        case 1: 
                        {
                                message_vision(HIR "�ۼ�$N" HIR + condition[random(sizeof(condition))]
                                                +"��ͻȻ$N���һ�������˼�����\n����ͨ����$n����������"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name() + "ͻȻ�ӻ����ͳ�һ�Ѱ׻��������ӣ�С��"
                                                "�����������λ" + RANK_D->query_respect(me) + "��\n��"
                                                "������һ�棨nod����Σ���" + chinese_number(amount) +
                                                "�������͹����ˣ���\n" NOR);
                                remove_all_enemy(0); 
                                ob->set("qi", 1);
                                ob->set("jing", 1);
                                ob->set("jingli", 1);
                                ob->set_temp("lonely/waiting", amount);
                                me->set_temp("lonely/waiting", amount);
                                return;
                        }
                        case 2:
                        {
                                message_vision(HIR "�ۼ�$N" HIR + condition[random(sizeof(condition))]
                                                +"��ͻȻ$N���һ�������˼�����\n����ͨ����$n����������"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name() + "ͻȻ�ӻ����ͳ�һ�鱦ʯ��С��"
                                                "�����������λ" + RANK_D->query_respect(me) + "��\n��"
                                                "������һ�棨nod����Σ��ⱦʯ�͹����ˣ���\n" NOR);
                                remove_all_enemy(0); 
                                ob->set("qi", 1);
                                ob->set("jing", 1);
                                ob->set("jingli", 1);
                                ob->set_temp("lonely/waiting", amount);
                                me->set_temp("lonely/waiting", amount);
                                me->set_temp("lonely/diamond", 1);
                                return;
                        }
                        default: 
                        {
                                // ����
                                ::unconcious();
                                return;
                        }
                }
        }
        if (objectp(me)) 
                me->delete_temp("lonely");
        ::unconcious();
}

void die()
{
        int reward_exp, reward_pot;
        object killer, killer1, me;
        
        me = this_object();
        if (objectp(killer = query_last_damage_from()))
                killer1 = find_player(me->query("want_kill"));
        
        message_vision(HIC"$N�Һ�һ����������Ѫ�����ڵ������ˡ�\n"NOR,me);
        
        if (killer1)
        {
                if(killer->query("id") == me->query("want_kill"))
                {
         		reward_exp = (int)me->query("combat_exp") / 5000;

         		if (killer->query("combat_exp") < 2000000)
                   	reward_exp -= reward_exp / 5;
         		if (reward_exp > 600) reward_exp = 600;   
         		reward_exp = reward_exp / 2 + random(reward_exp / 2); 
         		reward_pot = reward_exp / 5; 
         		if (! userp(killer1))
                	{
                   		reward_exp = reward_exp / 10;
                   		reward_pot = reward_exp / 10;
                	}
         		if (reward_pot < 0) reward_pot = 0;

                   	tell_object(killer1,
				HIM "��ϲ���ֳɹ����һ���ٷˣ�\n" NOR + HIW "��ʵս�У�������" +  
				CHINESE_D->chinese_number(reward_exp) + "��ġ�ʵս���须" +
				CHINESE_D->chinese_number(reward_pot) + "��ġ�Ǳ�ܡ���һЩʵս��ᣡ\n" NOR); 
                   	killer1->add("quest_yunbiao/reward_exp", reward_exp);            
                   	killer1->add("quest_yunbiao/reward_potential", reward_pot);
                   	killer1->add("combat_exp", reward_exp);
                   	killer1->add("experience", random(2));
                   	killer1->add("potential", reward_pot);
                   	killer1->add("score", random(25));
                   	killer1->delete_temp("lonely");
                }
        }

        remove_call_out("escape_me");
        remove_call_out("check_me");
        destruct(me);
        return;
}
