// person used in quest
#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

object jiufen_object = 0;
string jiufen_name = "";
string quest_ob = "";

string *say_msg = ({
"$N����$n��ŭ��˵���Ͻ����ҵ�obj_name�����ң�������㲻������",
"$Nָ��$n�ı��ӶԴ��˵�����������������������ȥ���������ҵ�obj_name�������ڻ��������ң�",
"��������һ����ȴ��һ�Ű�ʸ�$N�����ϸߣ�������$n����ߣ�������ŨŨ�Ļ�ҩζ��",
"$N�����Ķ���$n���ſ�ʼ΢΢�������ƺ���ʱ�����߳�ȥ��",
"$Nҧҧ�������ֲ���㶵���ƺ�Ҫ�ͳ���ʲô������������$n�����Ŀ�⣬ȴ�ֿ��ֳ��˳�����",
"$NԽ˵Խ������obj_name���ҵ�������������µ�Ψһ�����$nƭ�ߺ�����δ�黹���ҡ�",
"$Nҧ���гݵĿ���$n������˵���ǽ�һ�����ڣ����ڹ���һ�����������㻹���ң�",
"$N������м�Ŀ���$n��������һ����ƭ�ӣ�",
"$Nŭ�����ĺ𣺾�����Ū������Ҳ�ø����һ�������ĭ��������$n������",
"$Nһƨ�������ϣ������ƵĶ���$n�ߺߣ����Ѷ��������ң��Ժ��Ҿͳ���ĺ��������ġ�",
"$N�۾��ɵú���¯һ����$n�����ƭ�ӣ��Ҳ�����������ðѪ����Ͳ�֪������~Ϊʲô,��!��!��!!!~~",
"ֻ��$Nһ����������ž....ž....ž��ת�ۼ��Ѿ���$n��ƨ��������ʮ������ӡ��",
"$N��$n�ı����ݺݵĴ���һȭ��Ȼ��$n���ứ����������һ���衣",
"$N����$n�������ļ�Ц������������������̵ģ�������",
"$N����$nһ�������Ķ��⡣",
"$N����$nȥ����",
"$N��$n��ɫ������ֱ��������ɲ�Ҫ��Ѱ��·����",
"$N����$n������Ц���㲻��obj_name�����ң���ͱ����к����ӹ���",
});

string *reply_msg = ({
"$N����$n����ãȻ��˵����˵ʲôobj_name��������ô������Ŷ��",
"$Nָ��$n�ı��ӶԴ��˵���㿴��������������������һ����obj_name����ô��",
"��������һ����ȴ��һ�Ű�ʸ�$N�����ϸߣ�������$n����ߣ�������ŨŨ�Ļ�ҩζ��",
"$N����Ķ���$n�Ľţ�������ͻȻ�߹�����",
"$N�Ļ���ҲԽ��Խ��$n��ڿ�����˵���Һ����ѣ�������һ������obj_name��Ҳֵ����������",
"$NԽ˵Խ������obj_name���������Ҹ��׸�$n�ģ����ڻص�������Ҳ�Ǻ��������",
"$Nҧ���гݵĿ���$n��������̬�ȣ������Ұ�obj_name�����㣿����ȥ�ɣ�",
"$N������м�Ŀ���$n���Ը���������ͷ���Ե������ӣ����ý�ʲô����",
"$Nŭ�����ĺ�$n��������ţ���˵������û��obj_name��������Ҳ��������㣡",
"$N����$nͻȻ������Ц���㼱������а����Ҿ��ǲ����㣬�������ģ������ң�",
"$N�۾��ɵú���¯һ����$n�������С�ӣ��Ҳ�����������ðѪ����Ͳ�֪������~Ϊʲô,��!��!��!!!~~",
"ֻ��$Nһ����������ž....ž....ž��ת�ۼ��Ѿ���$n��ƨ��������ʮ������ӡ��",
"$N��$n�ı����ݺݵĴ���һȭ��Ȼ��$n���ứ����������һ���衣",
"$N����$n��ŭ����������ӣ�ͻȻ����һЦ����������������ĺ���衣",
"$N����$nһ�������Ķ��⡣",
"$N����$nȥ����",
"$N��$n��ɫ������ֱ��������ɲ�Ҫ��Ѱ��·����",
"$N����$n������Ц�����Ұ�obj_name�����㣬���ǹ��������ҿ�������ͷ��",
});

void set_quest_ob(string arg);
void set_jiufen_object(object ob);
int  accept_object(object who, object ob);
int  leave();
int  is_stay_in_room()	{ return 1; }
void heart_beat();
void destruct_me();
string ask_me();

void create()
{
        ::create();
        set("gender",query("gender"));
	set("age", 30 + random(30));
        if (arrayp(query("from")) && sizeof(query("from")))
                set("long",query("from")[random(sizeof(query("form")))] + "\n��˵������뽭��������Ϊ�������˾��ס�\n");
        else
                set("long","��˵������뽭��������Ϊ�������˾���\n");


	set("attitude", "friendly");
       set("chat_chance", 30);
       set("scale", 150);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 50);
	set_temp("born_time", time());
	set("inquiry", ([
 		"����" : (: ask_me :),
 	]) );
      set_heart_beat(10);
}

void set_quest_ob(string arg)
{
       quest_ob = arg;
       return;
}

void set_jiufen_object(object ob)
{
       jiufen_object = ob;
       jiufen_name = ob->name();
       return;
}

int accept_fight(object ob)
{
        command("say ����֮����ûʲô���ף���ɶ���֣�");
        return notify_fail("������������ȡ���˸�" + this_object()->name() + "���Ե���ͷ��\n");
}

int accept_kill(object ob)
{
        command("say ��ô˵����Ҳ���۸��ң�");
        command("cry");
        return notify_fail("ɲ�Ǽ���ֻ�����²����֡�\n"); 
}

int accept_hit(object ob)
{
        command("say ��ô˵����Ҳ���۸��ң�");
        command("cry");
        return 0;
}

int accept_touxi(object ob)
{
        tell_object(ob,"�����͵Ϯ��ͻȻ����" + this_object()->name() + "�������Ͻ���\n"); 
        return 1;
}

int accept_ansuan(object who) 
{
        return notify_fail("����밵�㣬���Ƿ���" + this_object()->name() + "�ǳ�С�Ľ����������޴����֡�\n"); 
} 

void heart_beat()
{
       mapping msg;
       string msg1,msg2;

	if (time() - query_temp("born_time") > 900)
	{
		message_vision("$N�����˰��죬�о�ûʲô��˼��ڨڨ�����ˡ�\n", this_object());
		destruct_me();
		return;
	}

       if (!objectp(jiufen_object) || 
           !living(jiufen_object) ||
           !environment(this_object()) || 
           !environment(jiufen_object) ||
           environment(this_object()) != environment(jiufen_object))
	{
		message_vision("$N����һ�����޺޵�����������ͷ�ڹ꣬���������������ˣ��´�������\n", this_object());
		destruct_me();
		return;
	}

       //����Ѿ���ʼ���ھ��ף���ֹͣ����
       if (query_temp("on_tiaojie")) 
       {
              message_vision("$N����$n����һ����\n",this_object(),jiufen_object);
              message_vision("$n��ŭ�ĵ���$N������ȥ����ǿ������ͷ��ŭ����\n",this_object(),jiufen_object);
              return;
       }

       msg1 = say_msg[random(sizeof(say_msg))];
       msg2 = reply_msg[random(sizeof(reply_msg))];
       msg1 = replace_string(msg1,"obj_name",quest_ob);
       msg2 = replace_string(msg2,"obj_name",quest_ob);
       message_vision(msg1 + "\n",this_object(),jiufen_object);
       message_vision(msg2 + "\n",jiufen_object,this_object());
       return;
}

void destruct_me()
{
       message_vision("$Nת���뿪�ˡ�\n",this_object());
       destruct(this_object());
       return;
}

int accept_object(object who,object ob)
{
       int exp,pot,weiwang,score;
       mapping b;

        if (ob->is_character() || ob->is_item_make())
                // ���������������ı���
                return 0;

       if (!who->query("bang_quest") ||
           who->query("bang_quest/type") != "�������" ||
           who->query("bang_quest/ob") != this_object())
               return notify_fail("��С���������������ʲô�����ң�\n");

       if (ob->query("name") != quest_ob)
       {
               command("angry");
               command("say TNND,���������������Ū�ң���Ҫ����" + quest_ob + "���Ҳ����ͱ������ϴ�");
               return 0;
       }

       exp = who->query("bang_quest/bonus");
       exp += random(exp);
       pot = exp/(2+random(1));
       weiwang = 5 + random(10);
       score = 5 + random(10);

       who->delete("bang_quest");
       who->add_temp("finish_bang_times",1);
       command("wa " + who->query("id"));
       command("leyun" + who->query("id"));
       command("spank " + who->query("id"));
       command("say ��Ȼ��λ" + RANK_D->query_respect(who) + "������壬����Ҳû����˵�ˣ��ֵ�����ȸ���ˣ�������ڣ�");

       b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "�ڰ���" + jiufen_name + HIG "������׵Ĺ����У���������"
           ]);

       QUEST_D->delay_bonus(who, b);

       remove_call_out("destruct_me");
       call_out("destruct_me",0);

       return 1;
}

string ask_me()
{
       object who;
       who = this_player();
       if (!who->query("bang_quest") ||
           who->query("bang_quest/type") != "�������" ||
           who->query("bang_quest/ob") != this_object())
               return "����˭����һ��JJYY�ķ����������ҹ�Զ�㣬����û����£�";
       
       this_object()->set_temp("on_tiaojie",1);
       return "���⣿��ʲô�����⣿Ī���㻹�ܰ��Ұ�" + quest_ob + "�һ�������";
}
