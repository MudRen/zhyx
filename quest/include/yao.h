// ����Ʒ����
// update by sun 

#define QUEST_L "/quest/list/yaolist"

string ask_job()
{
        object me;
        int time, exp;
        mapping quest;
        me = this_player();
        time = random(240);
        exp = me->query("combat_exp");

        if ( me->query("quest/type")=="Ѱ��" )
                return "�Ҳ��ǽ���ȥ�Ҷ�������ô���ܻ����ˣ�\n";

        if ( me->query("quest") )
                return "�㻹��������������ɣ�\n";
        
        if ( me->query("fail_time") && me->query("fail_time") + 300 > time() )
                return "���ϴ�����ʧ���ˣ��Ѿ����˴�����ȥ��������ˡ����һ�������ɡ�\n";

    if (me->query_temp("yao_wait",1))
          return "��ող����һ����������Ϣһ��ɡ�\n";
        if (exp < 100000)
                return RANK_D->query_respect(me) + "�������ڵ�����Ϊ������̫Σ�գ��㻹����ȥ����Լ��ı���ɡ�\n";
        if ( exp > 5000000 )
                return RANK_D->query_respect(me) + "���ֲ������ҿ��벻�𰡡�\n";
        else quest = QUEST_L->query_quest(140);

        me->set("quest/type", "Ѱ��");
        me->set_temp("yao_wait",1);
        me->set("quest/task_time", time() + 480 - time);
        me->set("quest/quest", quest["quest"]);
        me->set("quest/bouns", quest["bouns"] + random(quest["bouns"]));
        command("whisper " + me->query("id") + " " + "������һ�" HIM + me->query("quest/quest") + NOR + WHT"���ң��һ�úô�л��ġ�");
        if ( quest["help"] )
        tell_object(me, sprintf(HIR "��" NOR + WHT"������ʾ"NOR+ HIR "��" NOR +"��" + HIG "�ⶫ��Ҳ�������%s�ҵ���\n" NOR, quest["help"]));
        return me->name() + "��춯��ɣ�����\n";
}

string ask_fail()
{
        object me = this_player();
 
        if ( me->query("quest/type") != "Ѱ��" )
                return "��ʲôʱ����������ˣ�\n";

        me->delete("quest");
        me->set("fail_time", time());
        me->delete_temp("yao_wait",1);
        return "������Ҫ����ô˵������أ�\n";
}

int accept_object(object me, object obj)
{
        int exp, pot, score, weiwang, money, pot_limit;

        if ( this_object()->is_busy() ) {
                command("say ��Ҫ�ż�������æ���أ�\n");
                return 0;
                }

        if ( me->query("quest/type") != "Ѱ��"
        || obj->query("name") != me->query("quest/quest") )
                return 0;

        if ( me->query("quest/task_time") < time() ) {
                command("sigh " + me->query("id"));
                me->delete("quest");
                me->delete_temp("yao_wait",1);
                remove_call_out("dest_obj");
                call_out("dest_obj", 1, obj);
                return 1;
                }

        command("nod " + me->query("id"));
        command("say ������Ľ�����\n");
        exp = me->query("quest/bouns") + random(100);
        pot = exp/2 + random(20);
        pot_limit = me->query_potential_limit() - me->query("potential");
        if (pot > pot_limit) pot = pot_limit;
        if (pot < 1) pot = 0;
        
        score = 1 + random(3);
        weiwang = 1 + random(2);
        money = (50 + random(10))*200;
        tell_object(me, sprintf(YEL"ͨ����ζ��������ˣ�%s��ʵս���飬%s��Ǳ�ܣ�%s�㽭��������%s��������\n"+
        "��Ϊһ�㽱�����������: "NOR+HIR+MONEY_D->money_str(money)+NOR+YEL+"���Ѿ����������ˡ�\n"NOR,
                chinese_number(exp), chinese_number(pot), chinese_number(score), chinese_number(weiwang)));
        
//        command("tell " + me->query("id")+YEL"��Ϊһ�㽱�����������: "HIR+MONEY_D->money_str(money)+YEL+"���Ѿ����������ˡ�\n"NOR);

        me->add("combat_exp", exp);
        me->add("potential", pot);      
        me->add("score", score);
	me->add("weiwang", weiwang);
	me->add("balance",money);
        me->delete("quest");
        me->delete("fail_time");        
//      message_vision("$N����Ľ�$n�Ž��������������档\n", this_object(), obj);
         this_object()->start_busy(1);
        remove_call_out("dest_obj");
        call_out("dest_obj", 1, obj);
        call_out("dest_yaowait",30);
        return 1;
}

int dest_yaowait()
{
        object me = this_player();
        me->delete_temp("yao_wait",1);
        command("tell " + me->query("id") + " ��Ϣ����û�У����Լ����������ˡ�");
}
void dest_obj(object obj)
{
        destruct(obj);
}

