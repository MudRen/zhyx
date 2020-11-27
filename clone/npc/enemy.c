// �������� NPC��

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese"; 

#include <defend.h>

int is_stay_in_room()  { return 1; }

int do_nod(string arg);
void leave_here();
void move_enemy(object enemy, string family);

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("long", "������ǰ������" + query("is_attacking")?query("is_attacking") : "�������"
                + "��һ��" + query("family/family_name")?query("family/family_name") : "δ֪����" +"���ӡ�\n");

        set("combat_exp", 100000 + random(500000));
        set("attitude", "peaceful");
        set("age", 18 + random(30));
        set("str", 20 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("int", 20 + random(20));
        
        set("chat_chance", 5);
        set("chat_msg", ({
                (: leave_here :), 
                (: random_move :), 
                (: random_move :), 
        }));

        set_temp("quest_ob", 1);
        
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_player();

        ::init();

        if( interactive(me) && visible(me) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("do_nod", "nod"); 
}

void greeting(object me)
{
        if (! me || ! present(me, environment())) 
                return;

        if (interactive(me) && 
            me->query_temp("defend_quest/start") && 
            me->query_family() == query("is_attacking") &&
            ! me->query_temp("defend_quest/finish"))
        {
                // �������д�ƺ���Ҫ����������˵���ֻ�������ݣ�
                command("grin");
                message_sort(HIW "ֻ��$N" HIW "��Ц�Ŷ�$n" HIW "�������ٺ٣���֪�����" +
                        RANK_D->query_rude(me) +"����Ȼ�Һ�����" + this_object()->query_family() +"���ԣ���"
                        "��������ѵ��ѵ�㣡��\n", this_object(), me );
                        
                kill_ob(me);
                return;
        }
        message_vision(HIW "$N" HIW "�����ɨ��$n" HIW "һ�ۡ�\n", this_object(), me );
}

void kill_ob(object me)
{
        object ob = this_object();

        if (! me->query_temp("defend_quest") || me->query_temp("defend_quest/finish"))
                return ::kill_ob(me);
        else
        {
                // ����״̬����Ҫ������
                NPC_D->set_from_me(ob, me, 100 + random(20));
                NPC_D->init_npc_skill(ob, NPC_D->check_level(me) + (1 + random(2)));
                ::kill_ob(me);
                return;
        }
}

// ��������˻�¸
int do_nod(string arg)
{
        object me = this_player();
        object ob = this_object();
        int amount;

        if (! me->query_temp("defend_quest/waiting") || 
            me->query_temp("defend_quest/finish") || 
            ! arg || arg != ob->query("id"))
                return 0;

        else 
        {
                me->command("nod");
                if (intp(me->query_temp("defend_quest/waiting")))
                {
                        amount = me->query_temp("defend_quest/waiting");

                        message_sort(HIW "ֻ��$N" HIW "��Ц����������������ʶʱ����Ϊ���ܣ�" +
                                     RANK_D->query_respect(me) + "��Ȼ�������ˣ��ٺ٣�������" +
                                     chinese_number(amount) + "�������͹����ˣ���������\n\n" NOR,
                                     ob, me);

                        MONEY_D->pay_player(me, amount * 100);
                        me->set_temp("defend_quest/accepted", 1);
                        tell_object(me, HIR + ob->name() + "�ݸ�����" + chinese_number(amount) + 
                                        "�������Ժ��³�һ����Ѫ���ﳤ��ȥ��\n" NOR );
                        return 1;
                }
                else return  0;
        }
}

void die()
{
        int percent;
        object me, ob = this_object();
        string *pills, pill;
        int amount = 300 + random(300);
        string *condition = ({
                "������������Ҫ��֧", "ͷ�ؽ��ᣬ���Ͼ͵�", 
                "ŻѪ��������ð����", "�˺����ۣ������м�", 
        });

        if (objectp(me = ob->query_last_damage_from()) 
        &&  environment(ob) == environment(me) 
        &&  me->query_temp("defend_quest/start") 
        &&  ! me->query_temp("defend_quest/finish")
        &&  ! me->query_temp("defend_quest/waiting"))
        {
                switch (random(15)) 
                {
                        case 1: {
                                message_sort(HIR "�ۼ�$N" HIR + condition[random(sizeof(condition))]
                                                +"��ͻȻ$N���һ�������˼�����\n����ͨ����$n����������"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name()+"ͻȻ�ӻ����ͳ�һ�Ѱ׻��������ӣ�С��"
                                                "�����������λ" + RANK_D->query_respect(me) + "��\n��"
                                                "������һ�棨nod����Σ���" + chinese_number(amount) +
                                                "�������͹����ˣ���\n" NOR);
                                ob->clean_up_enemy();
                                ob->remove_all_enemy(0);
                                ob->clear_condition(0);
                                ob->set("jing", 1);
                                ob->set("qi", 1);
                                me->set_temp("defend_quest/waiting", amount);
                                return;
                        }
                        default: {
                                // ����
                                if (me->query("family/family_name") == ob->query("is_attacking"))
                                        me->add_temp("defend_quest/killed", 1);
                                
                                ob->set_temp("die", 1);
                                
                                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                                      "pot" : 3 + random(20),
                                                      "score" : 3 + random(20) ]));
                                return ::die(me);
                        }
                }
                return;
        }
        if (objectp(me) && me->query("family/family_name") == ob->query("is_attacking")) 
        {
                me->add_temp("defend_quest/killed", 1); 

                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                      "pot" : 3 + random(20),
                                      "score" : 3 + random(20) ]));
        }
        return ::die();
}


void leave_here()
{
        object ob = this_object();

        if ( ob->is_fighting() || ob->is_busy() || ob->query("qi") < 40
        || ! ob->query("is_attacking")|| ob->is_unconcious())
                return;
                
        move_enemy(ob, ob->query("is_attacking"));
        return;
}

// ���ߵ��ˣ��� ENEMY �� chat_msg ��Ҳ�к��У�
void move_enemy(object enemy, string family)
{
        string *places = familys[family]["place"];
        string place = places[random(sizeof(places))];
        object room;

        if (objectp(room = environment(enemy)))
        {
                tell_room(room, enemy->name() + "һ����Ͳ����ˡ�\n");
        }
#ifdef DEBUG        
        CHANNEL_D->do_channel(this_object(), "sys",
                sprintf("%s : %O", enemy->short(), place)); 
#endif
        enemy->move(place);
        tell_room(place, "ֻ��һ��" + enemy->query_family() + "���Ӳ�֪ʲôʱ�����˳�����\n");

        return;
}

