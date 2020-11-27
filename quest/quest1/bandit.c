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
        if (clonep()) keep_heart_beat();
        setup();
}


void init()
{
        object ob, env;
        object killer = this_object();        

        ob = this_player();

        add_action("do_nod", "nod"); 
        add_action("do_nod", "�õ�"); 
        
        if (! this_object()->query("want_kill1") && ! this_object()->query("want_kill2"))
                return;
        if (ob->query("id") == query("want_kill1") || ob->query("id") == query("want_kill2"))
        {
                if (! is_fighting()) 
                {
                        remove_call_out("check_me");
                        call_out("check_me", 0);
                }
        }

        if (ob->query("id") != query("want_kill1") && ob->query("id") != query("want_kill2"))
        {
                add_action("do_kill", "team kill");
                add_action("do_kill", "touxi");   
                add_action("do_kill", "kill");
                add_action("do_kill", "hit");
                add_action("do_kill", "fight");
                add_action("do_kill", "steal");
                add_action("do_kill", "beg");
                add_action("do_kill", "persuade");
                add_action("do_kill", "perform");
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
        object ob = this_object(), obj;
        int amount;
        object me = this_player();

        if (! me->query_temp("lonely/waiting") || ! arg || arg != ob->query("id"))
        {
                return 0;
        }

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
        
        if (me->query_temp("lonely/waiting")) return 0;

        if (! present(query("want_kill1"), environment(me))
        &&  ! present(query("want_kill2"), environment(me)))   
        {
                remove_call_out("escape_me");
                destruct(me);
                return 0;
        }

        if (objectp(ob = present(query("want_kill1"), environment(me)))
        &&  ! environment(me)->query("no_fight")
        &&  interactive(ob) && ! ob->is_fighting(me))
                call_out("do_fkill", 0, ob);  
 
        if (objectp(ob = present(query("want_kill2"), environment(me)))
        &&  ! environment(me)->query("no_fight")
        &&  interactive(ob) && ! ob->is_fighting(me))
                call_out("do_fkill", 0, ob); 

        remove_call_out("check_me");
        call_out("check_me", 2);   

        return 1;
}

int do_fkill(object ob)
{
        if (! query_temp("lonely/waiting") && (ob->query("id") == query("want_killer") || ob->query("id") == query("want_kill2")))
        {
            if (living(this_object()))
                message_sort(HIR "$N��ȵ�������ɽ���ҿ������������ԣ�"+
                               ob->query("name") + "ʶ��Ļ��������ڳ����̹�����������Է���һ����·��\n" NOR,
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
        string temp, what, who;
        
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
        else
        if (sscanf(arg, "%s.%s %s", temp, what, who) == 3 && this_object()->id(who))
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
        int amount = 100 + random(100);
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
        object me, ob = this_object();
        
        
        message_vision(HIC "$N�Һ�һ����������Ѫ�����ڵ������ˡ�\n" NOR, ob);
        
        if (objectp(me = query_last_damage_from()) 
        &&  me->query("id") == ob->query("want_kill1") 
        ||  me->query("id") == ob->query("want_kill2"))
        {
                me->delete_temp("lonely");
                me->add_temp("quest_yunbiao/bandit_killed", 1);
                if (me->query_temp("quest_yunbiao/bandit_killed") > 10)
                        me->set_temp("quest_yunbiao/bandit_killed", 10);
                me->add("experience", random(2));
        }        
        remove_call_out("escape_me");
        remove_call_out("check_me");
        destruct(ob);
        return;
}

